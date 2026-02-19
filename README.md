<div align="center">


# Fragile Tarnished

### A lightweight C++ DLL mod for Elden Ring that implements a very hard challenge mode.

[![GitHub release](https://img.shields.io/github/v/release/RegularLunar/Fragile-Tarnished?style=for-the-badge&color=7c3aed&label=Latest)](https://github.com/RegularLunar/Fragile-Tarnished/releases)
[![Downloads](https://img.shields.io/github/downloads/RegularLunar/Fragile-Tarnished/total?style=for-the-badge&color=0ea5e9&label=Downloads)](https://github.com/RegularLunar/Fragile-Tarnished/releases)
[![Stars](https://img.shields.io/github/stars/RegularLunar/Fragile-Tarnished?style=for-the-badge&color=f59e0b)](https://github.com/RegularLunar/Fragile-Tarnished)
[![License](https://img.shields.io/github/license/RegularLunar/Fragile-Tarnished?style=for-the-badge&color=10b981)](LICENSE)
[![Last Commit](https://img.shields.io/github/last-commit/RegularLunar/Fragile-Tarnished?style=for-the-badge&color=6366f1)](https://github.com/RegularLunar/Fragile-Tarnished/commits)

</div>

<div align="center">

## ⚡ Key Features

</div>

<table>
<tr>
<td width="50%" valign="top">

### ⚙️ Core

- Pattern Scanning - on inject, it waits 10 seconds then scans the game's memory for a specific byte signature to locate the `WorldChrMan`. Sig: `48 8B 05 ? ? ? ? 48 85 C0 74 0F 48 39 88`
- Pointer Chain Walk - it follows a chain of pointers (`WorldChrMan` → `0x10EF8` → `0x0` → `0x190` → `0x0`) to reach the player character's stat block.
- Stat Forcing Loop - every 20ms, it reads the player's current and max HP, MP (FP), and Stamina, and forces all of them to 1. So the player is permanently at 1 HP / 1 FP / 1 Stamina with a max of 1.

</tr>
</table>

<div align="center">
   
##   ⚠️ WARNING

</div>

### Do not use this mod while playing online.
### Elden Ring uses Easy Anti-Cheat (EAC). 
### Using mods while connected to FromSoftware's servers will result in a ban. 
### Always play in Offline Mode with EAC disabled.

<div align="center">

## 🚀 Getting Started

</div>

### Download

Via Mod Engine 2 (Recommended)
1. Ensure you have [Mod Engine 2](https://github.com/soulsmods/ModEngine2) set up.
2. Copy `FragileTarnished.dll` into your Mod Engine `mods` folder.
3. Add the following line to your configuration `config_eldenring.toml`:
   ```toml
   external_dlls = [ "mod/FragileTarnished.dll" ]
   ```
   
---

### Building from Source

**Prerequisites:** CMake 3.x+, a C++ compiler (GCC / Clang / MSVC)

```bash
git clone https://github.com/RegularLunar/Fragile-Tarnished.git
cd Fragile-Tarnished
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

---

### Help and Support

[Open an issue](https://github.com/RegularLunar/Fragile-Tarnished/issues) for support.

<div align="center">

## 🙏 Acknowledgements

</div>

- **[The Grand Archives](https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA)** - Signatures, Pointers, etc

---

<sub>Made with ❤️ by [RegularLunar](https://github.com/RegularLunar)</sub>
