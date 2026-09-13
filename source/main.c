#include <nds.h>

#include "app_state.h"
#include "battle.h"
#include "console_context.h"
#include "title_screen.h"
#include "ui_buttons.h"

PrintConsole top_console;
PrintConsole bottom_console;

int main(void) {
    ScreenState current_screen = SCREEN_TITLE;
    BattleState battle_state;

    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);

    consoleInit(&top_console, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    consoleInit(&bottom_console, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 1, false, true);

    irqEnable(IRQ_VBLANK);

    title_screen_draw_top();
    title_screen_draw_bottom();

    while (1) {
        scanKeys();

        const int down = keysDown();
        touchPosition touch;
        touchRead(&touch);

        if (current_screen == SCREEN_TITLE) {
            if ((down & KEY_A) || (down & KEY_TOUCH)) {
                battle_init(&battle_state);
                battle_draw_top(&battle_state);
                battle_draw_bottom(&battle_state);
                current_screen = SCREEN_BATTLE;
            }
        } else {
            if (down & KEY_A) {
                if (battle_is_over(&battle_state)) {
                    battle_handle_continue(&battle_state);
                } else if (battle_state.menu == BATTLE_MENU_COMMANDS) {
                    battle_handle_attack(&battle_state);
                } else {
                    battle_handle_back(&battle_state);
                }
            }

            if (down & KEY_B) {
                if (battle_state.menu != BATTLE_MENU_COMMANDS) {
                    battle_handle_back(&battle_state);
                } else if (battle_is_over(&battle_state)) {
                    battle_handle_continue(&battle_state);
                }
            }

            if (down & KEY_TOUCH) {
                TouchAction action = TOUCH_ACTION_NONE;

                if (battle_is_over(&battle_state)) {
                    action = ui_touch_action_for_continue(touch.px, touch.py);
                } else if (battle_state.menu == BATTLE_MENU_COMMANDS) {
                    action = ui_touch_action_for_commands(touch.px, touch.py);
                } else {
                    action = ui_touch_action_for_back(touch.px, touch.py);
                }

                switch (action) {
                    case TOUCH_ACTION_ATTACK:
                        battle_handle_attack(&battle_state);
                        break;
                    case TOUCH_ACTION_SCAN:
                        battle_handle_scan(&battle_state);
                        break;
                    case TOUCH_ACTION_PACK:
                        battle_handle_pack(&battle_state);
                        break;
                    case TOUCH_ACTION_KAIJU:
                        battle_handle_kaiju(&battle_state);
                        break;
                    case TOUCH_ACTION_BACK:
                        battle_handle_back(&battle_state);
                        break;
                    case TOUCH_ACTION_CONTINUE:
                        battle_handle_continue(&battle_state);
                        break;
                    case TOUCH_ACTION_NONE:
                    default:
                        break;
                }
            }

            battle_update(&battle_state);
            battle_draw_top(&battle_state);
            battle_draw_bottom(&battle_state);
        }

        swiWaitForVBlank();
    }
}
