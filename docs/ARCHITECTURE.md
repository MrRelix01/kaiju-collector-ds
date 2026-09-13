# Kaiju Collector DS Architecture

## Current prototype architecture

The prototype uses a small modular ARM9 codebase focused on DS-native rendering and input:

- `source/main.c` - app loop, DS setup, input routing, screen state transitions
- `source/screens/title_screen.c` - title screen rendering for top and bottom screens
- `source/battle/combat.c` - battle state, combat loop, messages, HP, draw routines
- `source/ui/touch_buttons.c` - touchscreen hitboxes and button rendering helpers

Rendering uses `libnds` console output on both screens with explicit `PrintConsole` instances (`top_console` and `bottom_console`) selected via `consoleSelect`, keeping memory and asset usage low.
Input uses touchscreen as primary control with physical A/B support for confirm/back behavior.

## Reserved future modules

The following systems are reserved for future iterations:

- World
- Player
- Kaiju
- Battles
- Capture
- Evolution
- AI
- Inventory
- Quests
- Save System
- Audio
- UI

These modules should be added as separate directories and integrated through narrow interfaces from the main loop.
