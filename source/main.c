#include <nds.h>
#include <stdio.h>

static PrintConsole topConsole;
static PrintConsole bottomConsole;

static void init_displays(void) {
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);

    consoleInit(&topConsole, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    consoleInit(&bottomConsole, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 1, false, true);

    BG_PALETTE[0] = RGB15(0, 0, 20);
    BG_PALETTE_SUB[0] = RGB15(0, 0, 0);
}

static void draw_static_text(void) {
    consoleSelect(&topConsole);
    consoleClear();
    iprintf("\x1b[2;7HTOP SCREEN TEST");
    iprintf("\x1b[5;5HSOLID BACKGROUND OK");

    consoleSelect(&bottomConsole);
    consoleClear();
    iprintf("\x1b[4;6HKAIJU COLLECTOR");
    iprintf("\x1b[7;5HBOOT TEST PASSED");
    iprintf("\x1b[10;4HTouch screen or press A");
    iprintf("\x1b[22;1HTouch: waiting");
    iprintf("\x1b[23;1HKey: waiting");
}

static void update_input_status(void) {
    const int down = keysDown();
    const int held = keysHeld();

    if (held & KEY_TOUCH) {
        touchPosition touch;
        touchRead(&touch);
        consoleSelect(&bottomConsole);
        iprintf("\x1b[18;1HTOUCH DETECTED          ");
        iprintf("\x1b[19;1HX:%3d Y:%3d           ", touch.px, touch.py);
    }

    if (down & KEY_A) {
        consoleSelect(&bottomConsole);
        iprintf("\x1b[21;1HA DETECTED             ");
        iprintf("\x1b[23;1HKey: A                 ");
    } else if (down & KEY_B) {
        consoleSelect(&bottomConsole);
        iprintf("\x1b[21;1HB DETECTED             ");
        iprintf("\x1b[23;1HKey: B                 ");
    } else if (down & KEY_START) {
        consoleSelect(&bottomConsole);
        iprintf("\x1b[21;1HSTART DETECTED         ");
        iprintf("\x1b[23;1HKey: START             ");
    }
}

int main(void) {
    init_displays();
    draw_static_text();

    while (pmMainLoop()) {
        scanKeys();
        update_input_status();
        swiWaitForVBlank();
    }

    return 0;
}
