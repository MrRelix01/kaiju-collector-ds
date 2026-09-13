#include <nds.h>
#include <stdio.h>

#include "ui_buttons.h"

static bool in_rect(int x, int y, int left, int top, int right, int bottom) {
    return x >= left && x <= right && y >= top && y <= bottom;
}

TouchAction ui_touch_action_for_commands(int x, int y) {
    if (in_rect(x, y, 8, 8, 120, 88)) {
        return TOUCH_ACTION_ATTACK;
    }
    if (in_rect(x, y, 136, 8, 248, 88)) {
        return TOUCH_ACTION_SCAN;
    }
    if (in_rect(x, y, 8, 104, 120, 184)) {
        return TOUCH_ACTION_PACK;
    }
    if (in_rect(x, y, 136, 104, 248, 184)) {
        return TOUCH_ACTION_KAIJU;
    }

    return TOUCH_ACTION_NONE;
}

TouchAction ui_touch_action_for_back(int x, int y) {
    if (in_rect(x, y, 164, 148, 252, 188)) {
        return TOUCH_ACTION_BACK;
    }

    return TOUCH_ACTION_NONE;
}

TouchAction ui_touch_action_for_continue(int x, int y) {
    if (in_rect(x, y, 64, 112, 192, 176)) {
        return TOUCH_ACTION_CONTINUE;
    }

    return TOUCH_ACTION_NONE;
}

void ui_draw_command_buttons(void) {
    iprintf("\x1b[2;2H+------------+  +------------+");
    iprintf("\x1b[3;2H|            |  |            |");
    iprintf("\x1b[4;2H|   ATTACK   |  |    SCAN    |");
    iprintf("\x1b[5;2H|            |  |            |");
    iprintf("\x1b[6;2H+------------+  +------------+");

    iprintf("\x1b[12;2H+------------+  +------------+");
    iprintf("\x1b[13;2H|            |  |            |");
    iprintf("\x1b[14;2H|    PACK    |  |   KAIJU    |");
    iprintf("\x1b[15;2H|            |  |            |");
    iprintf("\x1b[16;2H+------------+  +------------+");
}

void ui_draw_back_button(void) {
    iprintf("\x1b[18;21H+---------+");
    iprintf("\x1b[19;21H|  BACK   |");
    iprintf("\x1b[20;21H+---------+");
}

void ui_draw_continue_button(void) {
    iprintf("\x1b[13;9H+---------------+");
    iprintf("\x1b[14;9H|   CONTINUE    |");
    iprintf("\x1b[15;9H+---------------+");
}
