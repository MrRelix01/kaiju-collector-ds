#include <nds.h>
#include <stdio.h>
#include <string.h>

#include "battle.h"
#include "console_context.h"
#include "ui_buttons.h"

static int clamp_hp(int hp) {
    if (hp < 0) {
        return 0;
    }
    if (hp > 100) {
        return 100;
    }
    return hp;
}

void battle_init(BattleState *state) {
    state->player_hp = 100;
    state->enemy_hp = 100;
    state->enemy_counter_pending = false;
    state->enemy_counter_delay_frames = 0;
    state->menu = BATTLE_MENU_COMMANDS;
    snprintf(state->message, sizeof(state->message), "Choose an action.");
}

bool battle_is_over(const BattleState *state) {
    return state->player_hp <= 0 || state->enemy_hp <= 0;
}

void battle_handle_attack(BattleState *state) {
    if (battle_is_over(state)) {
        return;
    }

    state->enemy_hp = clamp_hp(state->enemy_hp - 10);
    snprintf(state->message, sizeof(state->message), "Pebblit used Stone Bash!");

    if (state->enemy_hp == 0) {
        state->enemy_counter_pending = false;
        state->menu = BATTLE_MENU_END;
        snprintf(state->message, sizeof(state->message), "Emberjaw was defeated!");
        return;
    }

    state->enemy_counter_pending = true;
    state->enemy_counter_delay_frames = 45;
    state->menu = BATTLE_MENU_COMMANDS;
}

void battle_update(BattleState *state) {
    if (!state->enemy_counter_pending || battle_is_over(state)) {
        return;
    }

    if (state->enemy_counter_delay_frames > 0) {
        state->enemy_counter_delay_frames -= 1;
        return;
    }

    state->player_hp = clamp_hp(state->player_hp - 8);
    state->enemy_counter_pending = false;
    snprintf(state->message, sizeof(state->message), "Emberjaw used Cinder Bite!");

    if (state->player_hp == 0) {
        state->menu = BATTLE_MENU_END;
        snprintf(state->message, sizeof(state->message), "Pebblit can no longer battle!");
    }
}

void battle_handle_scan(BattleState *state) {
    if (battle_is_over(state)) {
        return;
    }

    state->menu = BATTLE_MENU_SCAN;
    snprintf(state->message, sizeof(state->message), "EMBERJAW Type: Flame Beast");
}

void battle_handle_pack(BattleState *state) {
    if (battle_is_over(state)) {
        return;
    }

    state->menu = BATTLE_MENU_PACK;
    snprintf(state->message, sizeof(state->message), "Your pack is empty.");
}

void battle_handle_kaiju(BattleState *state) {
    if (battle_is_over(state)) {
        return;
    }

    state->menu = BATTLE_MENU_KAIJU;
    snprintf(state->message, sizeof(state->message), "Pebblit is ready.");
}

void battle_handle_back(BattleState *state) {
    if (battle_is_over(state)) {
        return;
    }

    state->menu = BATTLE_MENU_COMMANDS;
    snprintf(state->message, sizeof(state->message), "Choose an action.");
}

void battle_handle_continue(BattleState *state) {
    battle_init(state);
}

void battle_draw_top(const BattleState *state) {
    consoleSelect(&top_console);
    consoleClear();

    iprintf("\x1b[1;10HBATTLE PROTOTYPE");
    iprintf("\x1b[3;1HPebblit");
    iprintf("\x1b[3;21HEmberjaw");

    iprintf("\x1b[4;1HHP: %3d", state->player_hp);
    iprintf("\x1b[4;21HHP: %3d", state->enemy_hp);

    iprintf("\x1b[8;2H __");
    iprintf("\x1b[9;1H/oo\\");
    iprintf("\x1b[10;1H\\__/\\");
    iprintf("\x1b[11;2H||");

    iprintf("\x1b[8;23H/^^\\");
    iprintf("\x1b[9;22H<\\__/>");
    iprintf("\x1b[10;23H/  \\");
    iprintf("\x1b[11;24H||");

    iprintf("\x1b[15;1H%s", state->message);

    if (state->enemy_counter_pending && !battle_is_over(state)) {
        iprintf("\x1b[18;1HEmberjaw is preparing...");
    }
}

void battle_draw_bottom(const BattleState *state) {
    consoleSelect(&bottom_console);
    consoleClear();

    if (battle_is_over(state)) {
        iprintf("\x1b[6;6H%s", state->message);
        ui_draw_continue_button();
        iprintf("\x1b[23;1HA: Confirm  B: Restart");
        return;
    }

    switch (state->menu) {
        case BATTLE_MENU_SCAN:
            iprintf("\x1b[2;2HEMBERJAW");
            iprintf("\x1b[4;2HType: Flame Beast");
            iprintf("\x1b[5;2HTemperament: Aggressive");
            iprintf("\x1b[6;2HSize: Lesser");
            ui_draw_back_button();
            break;
        case BATTLE_MENU_PACK:
            iprintf("\x1b[4;2HYour pack is empty.");
            ui_draw_back_button();
            break;
        case BATTLE_MENU_KAIJU:
            iprintf("\x1b[4;2HPebblit is ready.");
            ui_draw_back_button();
            break;
        case BATTLE_MENU_END:
            ui_draw_continue_button();
            break;
        case BATTLE_MENU_COMMANDS:
        default:
            ui_draw_command_buttons();
            break;
    }

    iprintf("\x1b[23;1HA: Confirm  B: Back");
}
