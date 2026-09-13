# Kaiju Collector DS - Architecture

## Overview

This document describes the architecture of Kaiju Collector DS and reserved space for future subsystems.

The game is structured in modular layers to support incremental expansion from a simple battle prototype into a full creature-collection RPG.

## Current Modules (Prototype Phase)

### Core Systems

**main.c**
- Entry point
- Main event loop
- Screen management and state transitions
- Power management

**screens/**
- `title_screen.c` - Initial title/splash screen
- `battle_screen.c` - Active battle interface

**battle/combat.c**
- Battle state machine
- Turn order and action processing
- HP tracking and damage calculation
- Win/loss conditions

### UI Layer

**ui/buttons.c**
- Touchscreen button detection and handling
- Button rendering (ATTACK, SCAN, PACK, KAIJU)
- State management for menus

**ui/text.c**
- Text rendering to both screens
- Font management
- Message display system

### Game Data

**creatures/creatures.c**
- Creature definitions (Pebblit, Emberjaw)
- Base stats (HP, attack power)
- Type information
- Move sets (currently: Stone Bash, Cinder Bite)

**graphics/sprites.c**
- Screen rendering routines
- Placeholder creature graphics
- UI drawing

## Reserved Modules (Future Implementation)

### World System

**world/** (To be created)
- Map/terrain data structures
- Camera and viewport management
- Collision detection
- Environmental objects
- NPC placement and interaction

### Player System

**player/** (To be created)
- Player character state
- Party roster management
- Position and movement
- Interaction with world

### Kaiju System (Expanded)

**kaiju/** (To be created)
- Full creature database (100+ species)
- Individual creature instances
- Experience and leveling
- Stat growth
- Move learning
- Ability effects

### Battle System (Expanded)

**battles/** (To be created)
- Full battle AI
- Type advantage calculations
- Status effects (burn, poison, paralysis, etc.)
- Energy/AP system
- Battle animations

### Capture System

**capture/** (To be created)
- Capture mechanics
- Capture rates
- Ball types
- Success/failure handling

### Evolution System

**evolution/** (To be created)
- Evolution chains
- Evolution conditions
- Stat adjustments on evolution
- Animation and notification

### AI System

**ai/** (To be created)
- Enemy trainer AI
- Wild kaiju behavior
- NPC dialogue trees
- Quest logic

### Inventory System

**inventory/** (To be created)
- Item management
- Equipment handling
- Consumable tracking
- Bag organization

### Quest System

**quests/** (To be created)
- Quest definitions
- Quest state tracking
- Objective management
- Rewards

### Save System

**save/** (To be created)
- Save/load mechanics
- Player progress persistence
- Creature roster saves
- World state preservation

### Audio System

**audio/** (To be created)
- Music playback
- Sound effects
- Audio driver abstraction

### UI System (Expanded)

**ui/** (To be expanded)
- Menu systems
- HUD elements
- Transitions and animations
- Dialog boxes

## Memory Model

### Current Usage

- **VRAM:** Title and battle screen graphics, sprites
- **Main RAM:** Game state, creature data, button states
- **ARM7 RAM:** Sound/timing (minimal in prototype)

### Future Considerations

- Streaming large world maps in/out of VRAM
- Creature sprite caching
- Audio buffer management
- Save data in SRAM

## Data Flow

```
main.c (event loop)
  ├── Input processing (buttons, touchscreen)
  ├── State transitions (title → battle → menu)
  ├── Update logic (battle state machine)
  └── Rendering (screens to both displays)

Title Screen Flow:
  title_screen.c → (input) → battle_screen.c

Battle Screen Flow:
  Input (touchscreen buttons)
    ↓
  ui/buttons.c (button detection)
    ↓
  combat.c (action processing)
    ↓
  creatures.c (stat lookup)
    ↓
  Damage calculation & HP update
    ↓
  Enemy counterattack
    ↓
  Check win/loss conditions
    ↓
  graphics/sprites.c (render state)
    ↓
  Display on screens
```

## Build Process

1. **Source compilation:** C source → object files (devkitARM)
2. **Linking:** Object files → ELF binary
3. **Conversion:** ELF → NDS ROM (ndstool)
4. **Artifact:** `kaiju_collector_ds.nds` ready for hardware/emulator

**Build system:** GNU Make with devkitPro toolchain integration

## Development Guidelines

### Adding New Features

1. Create feature module under appropriate subsystem folder
2. Define public interface in `.h` file
3. Implement in corresponding `.c` file
4. Update `main.c` to integrate into event loop if needed
5. Add artifact handling to Makefile if new asset types are used
6. Test on emulator (DeSmuME, melonDS) before hardware

### Performance Targets

- **Frame rate:** Stable 60 FPS (or 30 FPS if 3D is added)
- **RAM usage:** Well under 4MB limit
- **VRAM usage:** Efficient sprite/tilemap caching
- **Load time:** < 2 seconds per screen transition

### Code Style

- Consistent indentation (4 spaces)
- Clear variable naming
- Function documentation in headers
- Modular functions (< 200 lines each)
- Minimize global state where possible

## Emulator Testing

All development should be tested on:
- **DeSmuME** (reference emulator)
- **melonDS** (modern high-accuracy)
- **Delta** (iOS, target platform for documentation)

## Next Major Milestone

Once prototype is stable:
1. Expand creatures module to 50+ species
2. Implement world system with basic tile map
3. Create encounter system
4. Add capture mechanics
5. Begin RPG progression framework

Current phase focuses on establishing the build pipeline, dual-screen rendering, input handling, and combat foundation.
