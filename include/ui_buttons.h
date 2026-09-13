#ifndef UI_BUTTONS_H
#define UI_BUTTONS_H

typedef enum {
    TOUCH_ACTION_NONE = 0,
    TOUCH_ACTION_ATTACK,
    TOUCH_ACTION_SCAN,
    TOUCH_ACTION_PACK,
    TOUCH_ACTION_KAIJU,
    TOUCH_ACTION_BACK,
    TOUCH_ACTION_CONTINUE
} TouchAction;

TouchAction ui_touch_action_for_commands(int x, int y);
TouchAction ui_touch_action_for_back(int x, int y);
TouchAction ui_touch_action_for_continue(int x, int y);

void ui_draw_command_buttons(void);
void ui_draw_back_button(void);
void ui_draw_continue_button(void);

#endif
