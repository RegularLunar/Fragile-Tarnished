# Fragile Tarnished

A lightweight C++ DLL mod for **Elden Ring** that implements a very hard challenge mode. The player has 1 HP, FP, & SP

[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![CMake](https://img.shields.io/badge/CMake-Build-green.svg)](https://cmake.org/)

## Warning
**Do not use this mod while playing online.** Elden Ring uses Easy Anti-Cheat (EAC). Using mods while connected to FromSoftware's servers will result in a ban. Always play in **Offline Mode** with EAC disabled.

## Features
- **All 3 stats permanently maxed at 1**
- **Customizeable** *(compile with commented out stats for different results)*

## Prerequisites
To build this project, you will need:
- **Visual Studio 2022** (with "Desktop development with C++" workload)
- **CMake 3.20** or higher
- **Windows SDK** (10.0.xxxxx)

## Building from Source
1. Clone the repository:
   ```powershell
   git clone https://github.com/RegularLunar/Fragile-Tarnished.git
   cd Fragile-Tarnished
   ```
2. Configure the project:
   ```powershell
   cmake -B build -S . -A x64
   ```
3. Build the DLL:
   ```powershell
   cmake --build build --config Release
   ```
The compiled `FragileTarnished.dll` will be located in the `build/Release` folder.

## Installation
### Via Mod Engine 2 (Recommended)
1. Ensure you have [Mod Engine 2](https://github.com/soulsmods/ModEngine2) set up.
2. Copy `FragileTarnished.dll` into your Mod Engine `mods` folder.
3. Add the following line to your configuration `config_eldenring.toml`:
   ```toml
   external_dlls = [ "mod/FragileTarnished.dll" ]
   ```

## Technical Details
- Signature Scanning (AOB)
   Unlike simple trainers that use hardcoded memory addresses (which break every time the game updates), this mod uses Pattern Scanning. It searches the game's memory for a specific "signature" (Array of Bytes) to locate WorldChrMan.
   Pattern: `48 8B 05 ? ? ? ? 48 85 C0 74 0F 48 39 88`

- RIP-Relative Addressing: 
   The mod automatically calculates the absolute address of the character manager by resolving the 32-bit relative offset found in the instruction.

- Pointer Chain Traversal
   The mod navigates through the game's internal class hierarchy to reach the Local Player's stat block. It follows a deep pointer chain to ensure it is always targeting the correct player instance:
   `WorldChrMan → 0x10EF8 → 0x0 → 0x190 → 0x0 → Stat Offsets`
   
- Stat Forcing Logic
   Once the player's stat block is located, the mod monitors and overrides three core attributes:
   HP (Health): Current and Base Max HP are locked to 1.
   MP (Mana): Current and Base Max MP are locked to 1.
   SP (Stamina): Current and Base Max Stamina are locked to 1.

## Credits
- Created by **RegularLunar**
- Signatures, Pointers, etc by **[TGA](https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA)**
---
<div align="center">
  
  ![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/regularlunar/Fragile-Tarnished/total?style=for-the-badge&logo=githubsponsors&logoSize=20&color=%23916cd9)
  
</div>
