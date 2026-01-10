#include <Windows.h>
#include <Psapi.h>
#include <cstdint>

uintptr_t worldChrManAddress = 0;
const char* CHR_PATTERN = "\x48\x8B\x05\x00\x00\x00\x00\x48\x85\xC0\x74\x0F\x48\x39\x88";
const char* CHR_MASK = "xxx????xxxxxxxx";

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

bool InitializeWorldChrMan() {
    uintptr_t patternAddr = FindPattern(CHR_PATTERN, CHR_MASK);
    if (!patternAddr) return false;

    int32_t relativeOffset = *reinterpret_cast<int32_t*>(patternAddr + 3);
    worldChrManAddress = patternAddr + relativeOffset + 7;
    return true;
}
void ForceStatToOne(int* current, int* base) {
    if (current && base && *current > 0) {
        if (*base != 1) *base = 1;
        if (*current != 1) *current = 1;
    }
}
DWORD WINAPI MainThread(LPVOID lpParam) {
    Sleep(10000);

    if (!InitializeWorldChrMan()) return 0;

    while (true) {
        __try {
            uintptr_t worldChrMan = *reinterpret_cast<uintptr_t*>(worldChrManAddress);

            if (worldChrMan) {
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
        }

        Sleep(20);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, nullptr, 0, nullptr);
        if (hThread) CloseHandle(hThread);
    }
    return TRUE;
}