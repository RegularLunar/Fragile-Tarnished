# Fragile Tarnished
> A lightweight C++ DLL mod for Elden Ring that implements a very hard challenge mode.

![Release](https://img.shields.io/github/v/release/RegularLunar/Fragile-Tarnished?style=for-the-badge&color=916cd9) 
![License](https://img.shields.io/github/license/RegularLunar/Fragile-Tarnished?style=for-the-badge&color=10b981) 
![Stars](https://img.shields.io/github/stars/RegularLunar/Fragile-Tarnished?style=for-the-badge&color=f59e0b) 
![Downloads](https://img.shields.io/github/downloads/RegularLunar/Fragile-Tarnished/total?style=for-the-badge&color=0ea5e9&label=Downloads) 
![Last Commit](https://img.shields.io/github/last-commit/RegularLunar/Fragile-Tarnished?style=for-the-badge&color=6366f1)

---

### Features
- Pattern Scanning
- 1 HP
- 1 Mana
- 1 Stamina

> [!NOTE]
> You have to recompile the DLL to choose specifics. (e.g only 1 stamina). Currently its setup to set all 3 stats to 1. See [Line 90](https://github.com/RegularLunar/Fragile-Tarnished/blob/3bc1df36be6303921cbf687e32a7161e7530ff01/dllmain.cpp#L90)

---

### Building From Source

- **Visual Studio 2022**,- **CMake 3.16** or higher
- **Windows SDK**

```bash
git clone https://github.com/RegularLunar/Fragile-Tarnished.git
cd Fragile-Tarnished
cmake -B build -S . -A x64
cmake --build build --config Release
```

---

### Support
Issues and PRs are welcome. For major changes, please open an [issue](https://github.com/RegularLunar/Fragile-Tarnished/issues) first.

### Acknowledgements / Credits
- **[The Grand Archives](https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA)** - Signatures, Pointers, etc

---

<sub>Made with 💜 by [RegularLunar](https://github.com/RegularLunar)</sub>
