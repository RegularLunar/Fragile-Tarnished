#include <Windows.h>
#include <Psapi.h>
#include <cstdint>
#include <vector>
#include "Pattern.h"

namespace Offsets {
    constexpr uintptr_t WorldChrMan_PlayerCtrl = 0x10EF8;
    constexpr uintptr_t PlayerCtrl_ChrIns = 0x0;
    constexpr uintptr_t ChrIns_ModuleContainer = 0x190;
    constexpr uintptr_t ModuleContainer_StatMod = 0x0;
    constexpr uintptr_t StatMod_CurrentHP = 0x138;
    constexpr uintptr_t StatMod_BaseMaxHP = 0x144;
    constexpr uintptr_t StatMod_CurrentMP = 0x148;
    constexpr uintptr_t StatMod_BaseMaxMP = 0x150;
    constexpr uintptr_t StatMod_CurrentSP = 0x154;
    constexpr uintptr_t StatMod_BaseMaxSP = 0x15C;
}

uintptr_t worldChrManAddress = 0;
const char* WorldChrManPattern = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 0F 48 39 88";

template <typename T>
bool SafeRead(uintptr_t address, T& outValue) {
    return ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), &outValue, sizeof(T), nullptr) != 0;
}

template <typename T>
bool SafeWrite(uintptr_t address, const T& value) {
    return WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(address), &value, sizeof(T), nullptr) != 0;
}

uintptr_t ResolveChain(uintptr_t baseAddress, const std::vector<uintptr_t>& offsets) {
    uintptr_t ptr = baseAddress;
    for (size_t i = 0; i < offsets.size(); ++i) {
        if (!SafeRead(ptr, ptr)) return 0;
        ptr += offsets[i];
    }
    if (!SafeRead(ptr, ptr)) return 0;
    return ptr;
}

bool InitializeWorldChrMan() {
    HMODULE hModule = GetModuleHandle(nullptr);
    DWORD64 patternAddr = Pattern::ScanPatternInExecutableSection(hModule, WorldChrManPattern);
    if (!patternAddr) return false;

    int32_t relativeOffset = *reinterpret_cast<int32_t*>(patternAddr + 3);
    uintptr_t resolvedAddress = static_cast<uintptr_t>(patternAddr) + relativeOffset + 7;

    MODULEINFO modInfo = { 0 };
    K32GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
    uintptr_t moduleBase = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
    uintptr_t moduleEnd = moduleBase + modInfo.SizeOfImage;

    if (resolvedAddress < moduleBase || resolvedAddress >= moduleEnd) return false;

    worldChrManAddress = resolvedAddress;
    return true;
}

void ForceStatToOne(uintptr_t statModBase, uintptr_t currentOffset, uintptr_t maxOffset) {
    int currentVal = 0;

    if (SafeRead(statModBase + currentOffset, currentVal) && currentVal > 0) {
        int maxVal = 0;
        SafeRead(statModBase + maxOffset, maxVal);

        if (maxVal != 1) {
            SafeWrite(statModBase + maxOffset, 1);
        }
        if (currentVal != 1) {
            SafeWrite(statModBase + currentOffset, 1);
        }
    }
}

DWORD WINAPI MainThread(LPVOID lpParam) {
    while (!InitializeWorldChrMan()) {
        Sleep(500);
    }

    std::vector<uintptr_t> statModOffsets = {
        Offsets::WorldChrMan_PlayerCtrl,
        Offsets::PlayerCtrl_ChrIns,
        Offsets::ChrIns_ModuleContainer,
        Offsets::ModuleContainer_StatMod
    };

    while (true) {
        uintptr_t statMod = ResolveChain(worldChrManAddress, statModOffsets);

        if (statMod != 0) {
			// Comment out the stat that you DONT want to be forced to 1.
            ForceStatToOne(statMod, Offsets::StatMod_CurrentHP, Offsets::StatMod_BaseMaxHP); // Health
			ForceStatToOne(statMod, Offsets::StatMod_CurrentMP, Offsets::StatMod_BaseMaxMP); // Mana
			ForceStatToOne(statMod, Offsets::StatMod_CurrentSP, Offsets::StatMod_BaseMaxSP); // Stamina
        }

        Sleep(100);
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
