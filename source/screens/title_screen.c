#include <nds.h>
#include <stdio.h>

#include "console_context.h"
#include "title_screen.h"

void title_screen_draw_top(void) {
    consoleSelect(&top_console);
    consoleClear();

    iprintf("\x1b[4;7HKAIJU COLLECTOR");
    iprintf("\x1b[6;10HDS Prototype");
    iprintf("\x1b[10;12H/\\");
    iprintf("\x1b[11;10H/####\\");
    iprintf("\x1b[12;9H/######\\");
    iprintf("\x1b[13;9H|######|");
    iprintf("\x1b[14;10H\\####/");
    iprintf("\x1b[15;11H\\__/");
    iprintf("\x1b[19;4HOriginal prototype silhouette");
}

void title_screen_draw_bottom(void) {
    consoleSelect(&bottom_console);
    consoleClear();

    iprintf("\x1b[8;8HTouch to Begin");
    iprintf("\x1b[12;8Hor press A");
}
