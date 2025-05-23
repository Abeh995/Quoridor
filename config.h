#ifndef QUORIDOR_CONFIG_H
#define QUORIDOR_CONFIG_H

#include "types.h"
#include "input.h"
#include "ui.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

bool handle_input_names(Game_Config *config, Game_State *state);
void adjust_setting(Game_Config *config, int setting, bool increase_value);
void allocate_boards_memory(Game_Config *config, Game_State *state);
void free_boards_memory(Game_Config *config, Game_State *state);
void cleanup(Game_Config *config, Game_State *state);
bool configure_players(Game_Config *config, Game_State *state);
bool handle_main_menu(Game_Config *config, Game_State *state);
bool game_setup_menu(Game_Config *config, Game_State *state);
void setup_boards_layout(Game_Config *config, Game_State *state);
void setup_wall_grid_layout(Game_Config * config, Game_State * state);
bool configure_new_game(Game_Config *config, Game_State *state);

#endif //QUORIDOR_CONFIG_H
