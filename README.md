# One HP Life

**HP/Stamina/FP locked to 1.** One mistake and you're dead. Made for people who hate themselves.

## Features
- All 3 stats permanently maxed at 1
- Overrides estus, talismans, buffs, vigor
- Works after death/NG+/level up
- 20ms enforcement loop
- Shadow of the Erdtree compatible

## Requirements
- elden ring 1.16+
- mod engine 2 (or elden mod loader)
- EAC disabled (offline only)
- windows x64

## Installation
- Download Mod Engine 2
- Place the DLL of your choosing in your mod directory. Should look like "...\Mod Engine 2\mod\1-Stat-Everything.dll"
- Open "config_eldenring.toml". inside "external_dlls = []" add "mod/NAME_OF_DLL.dll". Example: "external_dlls = [ "mod/1-Health.dll" ]"

## Technical
- AOB scan → worldChrMan → 0x10EF8 → 0x190 → player
- HP:      0x138/0x144  
- FP:      0x148/0x150
- Stamina: 0x154/0x15C

## Troubleshooting
- crash? wrong game version
- delete dll to disable

## Building
- visual studio 2022
- x64 release
- link psapi.lib

MIT License - modify/distribute freely
(no warranty - use at own risk)

**try not to die to the tree sentinel**
