#ifndef BATTLE_H
#define BATTLE_H

#include <stdbool.h>

typedef enum {
    BATTLE_MENU_COMMANDS = 0,
    BATTLE_MENU_SCAN,
    BATTLE_MENU_PACK,
    BATTLE_MENU_KAIJU,
    BATTLE_MENU_END
} BattleMenu;

typedef struct {
    int player_hp;
    int enemy_hp;
    bool enemy_counter_pending;
    int enemy_counter_delay_frames;
    BattleMenu menu;
    char message[96];
} BattleState;

void battle_init(BattleState *state);
void battle_update(BattleState *state);
void battle_handle_attack(BattleState *state);
void battle_handle_scan(BattleState *state);
void battle_handle_pack(BattleState *state);
void battle_handle_kaiju(BattleState *state);
void battle_handle_back(BattleState *state);
void battle_handle_continue(BattleState *state);
bool battle_is_over(const BattleState *state);

void battle_draw_top(const BattleState *state);
void battle_draw_bottom(const BattleState *state);

#endif
