#include <Windows.h>
#include <Psapi.h>
#include <cstdint>

// Resolved once at startup; address of the pointer to the WorldChrMan singleton.
uintptr_t worldChrManAddress = 0;

// AOB signature for a `mov rax, [rip+disp32]; test rax,rax; je ...; cmp rax,[rax+...]`
// sequence used to locate the WorldChrMan access site. Scans by byte pattern rather
// than fixed address, so it survives ordinary game updates as long as this exact
// instruction sequence is still emitted by the compiler.
const char* CHR_PATTERN = "\x48\x8B\x05\x00\x00\x00\x00\x48\x85\xC0\x74\x0F\x48\x39\x88";
const char* CHR_MASK = "xxx????xxxxxxxx";

// Naive byte-by-byte scan over the main module's image. O(size * patternLen),
// fine here since this only runs once at startup.
uintptr_t FindPattern(const char* pattern, const char* mask) {
    MODULEINFO modInfo = { 0 };
    K32GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &modInfo, sizeof(MODULEINFO));

    uintptr_t base = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
    size_t size = modInfo.SizeOfImage;
    size_t patternLen = strlen(mask);

    for (uintptr_t i = 0; i < size - patternLen; i++) {
        bool found = true;
        for (size_t j = 0; j < patternLen; j++) {
            if (mask[j] != '?' && pattern[j] != *reinterpret_cast<char*>(base + i + j)) {
                found = false;
                break;
            }
        }
        if (found) return base + i;
    }
    return 0;
}

// Resolves worldChrManAddress from the pattern match. The match sits on a
// RIP-relative MOV, so the target is patternAddr + disp32 + instruction length (7).
bool InitializeWorldChrMan() {
    uintptr_t patternAddr = FindPattern(CHR_PATTERN, CHR_MASK);
    if (!patternAddr) return false;

    int32_t relativeOffset = *reinterpret_cast<int32_t*>(patternAddr + 3);
    worldChrManAddress = patternAddr + relativeOffset + 7;
    return true;
}

// Clamps both current and base-max stat to 1, but only while the stat is still
// alive (*current > 0) — avoids resurrecting a value after actual death/zero-out.
void ForceStatToOne(int* current, int* base) {
    if (current && base && *current > 0) {
        if (*base != 1) *base = 1;
        if (*current != 1) *current = 1;
    }
}

DWORD WINAPI MainThread(LPVOID lpParam) {
    // Give the game time to finish loading before we start pattern scanning.
    Sleep(10000);

    if (!InitializeWorldChrMan()) return 0;

    while (true) {
        // SEH guard: pointer chain below walks player-specific runtime structures
        // that don't exist until in-game (menus, loading screens, etc.), so
        // dereferencing garbage/null here is expected and just skipped per tick.
        __try {
            uintptr_t worldChrMan = *reinterpret_cast<uintptr_t*>(worldChrManAddress);

            if (worldChrMan) {
                // Fixed offset chain down to the local player's stat block.
                // Unlike the pattern scan above, these raw hex offsets are
                // version-specific and will need updating when they shift.
                uintptr_t p1 = *reinterpret_cast<uintptr_t*>(worldChrMan + 0x10EF8);
                if (p1) {
                    uintptr_t p2 = *reinterpret_cast<uintptr_t*>(p1 + 0x0);
                    if (p2) {
                        uintptr_t p3 = *reinterpret_cast<uintptr_t*>(p2 + 0x190);
                        if (p3) {
                            uintptr_t p4 = *reinterpret_cast<uintptr_t*>(p3 + 0x0);
                            if (p4) {
                                int* currentHP = reinterpret_cast<int*>(p4 + 0x138);
                                int* baseMaxHP = reinterpret_cast<int*>(p4 + 0x144);
                                int* currentMP = reinterpret_cast<int*>(p4 + 0x148);
                                int* baseMaxMP = reinterpret_cast<int*>(p4 + 0x150);
                                int* currentSP = reinterpret_cast<int*>(p4 + 0x154);
                                int* baseMaxSP = reinterpret_cast<int*>(p4 + 0x15C);

                                // Toggle which stats get force-clamped to 1 by commenting
                                // out the calls below. Each is independent.
                                //   HP -> currentHP / baseMaxHP
                                //   MP -> currentMP / baseMaxMP (mana)
                                //   SP -> currentSP / baseMaxSP (stamina)
                                // e.g. to affect only stamina, comment out the HP and MP lines.
                                ForceStatToOne(currentHP, baseMaxHP);
                                ForceStatToOne(currentMP, baseMaxMP);
                                ForceStatToOne(currentSP, baseMaxSP);
                            }
                        }
                    }
                }
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            // Swallow access violations from stale/invalid pointers; next tick retries.
        }

        Sleep(20);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // No per-thread notifications needed; this DLL doesn't care about other threads.
        DisableThreadLibraryCalls(hModule);
        HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, nullptr, 0, nullptr);
        if (hThread) CloseHandle(hThread); // detach; thread runs for process lifetime
    }
    return TRUE;
}
