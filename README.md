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
> You have to recompile the DLL to choose specifics. (e.g only 1 stamina). Currently its setup to set all 3 stats to 1. See [Line 94](https://github.com/RegularLunar/Fragile-Tarnished/blob/6e2c5584ed48d46ef5cdad94a0c8705ef521420b/src/dllmain.cpp#L94)

> [!CAUTION]
> **Do not use this mod while playing online.** Elden Ring utilizes Easy Anti-Cheat (EAC). Modifying memory while connected to FromSoftware's servers will result in an account ban. Always play in **Offline Mode** with EAC disabled via [Mod Engine](https://github.com/garyttierney/me3) or a similar launcher. **I am not responsible for any harm to your account. You have been warned.**

---

### Building From Source

- **[Visual Studio](https://visualstudio.microsoft.com/) 2022 or higher**
- **[premake5](https://premake.github.io/)**
- **[Windows SDK](https://learn.microsoft.com/en-us/windows/apps/windows-sdk/downloads)**

```bash
git clone https://github.com/RegularLunar/Fragile-Tarnished.git
cd Fragile-Tarnished
premake5 vs2022
```

---

### Support
Issues and PRs are welcome. For major changes, please open an [issue](https://github.com/RegularLunar/Fragile-Tarnished/issues) first.

### Acknowledgements / Credits
- **[The Grand Archives](https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA)** - Signatures, Pointers, etc

---

<sub>Made with 💜 by [RegularLunar](https://github.com/RegularLunar)</sub>
