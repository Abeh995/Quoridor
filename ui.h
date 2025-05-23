#ifndef QUORIDOR_UI_H
#define QUORIDOR_UI_H

#include "types.h"

#include <time.h>
#include <stdio.h>

void clear();
void enable_ansi();
void initialize_ui();
void setup_ui_board_layout(Game_Config *config, Game_State *state);
void print_main_menu(int current_selection);
void print_setup_menu(Game_Config *config, Game_State *state, int current_selection);
void print_name_box(Game_Config *config, Game_State *state, int current_selection);
void print_current_pawn(Game_State *state, Position pawn);
void print_hovered_pawn(Game_State *state, Position pawn);
void print_default_cell(Game_State *state, Position tile);
void print_placed_wall(Game_State *state, Position tile);
void print_secondary_hovered_wall(Game_State *state, Position tile);
void print_main_hovered_wall(Game_State *state, Position tile);
void print_pawn_cell(Game_State *state, Turn_State *turn_state, Position tile, Position current_pawn);
void print_wall_cell(Game_State *state, Turn_State *turn_state, Position tile);
void print_ui_board(Game_Config *config, Game_State *state, Turn_State *turn_state);
void print_state(Game_Config* config, Game_State* state);
void print_game_turn(Game_Config* config, Game_State* state, Turn_State *turn_state);
bool pawn_cell(Position tile);
bool is_move_hover(Position tile, Turn_State *turn_state);
bool current_player_pawn(Game_State *state, Position tile, Position pawn);
bool placed_wall(Game_State *state, Position tile);
bool first_V_wall_cell(Position tile, Turn_State *turn_state);
bool first_H_wall_cell(Position tile, Turn_State *turn_state);
bool third_V_wall_cell(Position tile, Turn_State *turn_state) ;
bool third_H_wall_cell(Position tile, Turn_State *turn_state) ;
bool first_wall_cell_hovered (Position tile, Turn_State *turn_state);
bool third_wall_cell_hovered (Position tile, Turn_State *turn_state) ;
bool main_wall_cell(Position tile, Turn_State *turn_state) ;
bool secondary_wall_hovered(Position tile, Turn_State *turn_state);

#endif //QUORIDOR_UI_H
