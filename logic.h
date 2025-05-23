#ifndef QUORIDOR_LOGIC_H
#define QUORIDOR_LOGIC_H

#include "input.h"

bool is_wall_banned(Game_State * state, int y, int x);
bool is_empty_cell(Game_State * state, int y, int x);
bool validate_move(Game_Config *config, Game_State *state, Turn_State *turn_state, int key);
void move_pawn(Game_Config *config, Game_State *state, Turn_State *turn_state);
void setup_temp_wall_grid(Game_Config * config, Game_State * state);
void copy_wall_grid(Game_State * state);
void copy_place_wall(Game_State * state, Turn_State * turn_state);
bool is_out_of_board(Game_State * state, int dx, int dy);
bool check_up_side(Game_State * state, int dx, int dy);
bool check_down_side(Game_State * state, int dx, int dy);
bool check_left_side(Game_State * state, int dx, int dy);
bool check_right_side(Game_State * state, int dx, int dy);
void paint(Game_State * state, int dx, int dy);
bool can_playerX_reach_goal_line(Game_State * state, int dx, int dy, int playerNUM);
bool validate_players_target_way(Game_Config * config, Game_State * state, Turn_State *turn_state);
bool horizontal_is_valid(Game_State *state, int cursor_y, int cursor_x);
bool vertical_is_valid(Game_State *state, int cursor_y, int cursor_x);
bool is_empty_wall_cell(Game_State *state, int cursor_y, int cursor_x);
void set_primary_wall_cursor(Game_Config *config, Game_State *state, Turn_State *turn_state);
bool cursor_is_in_range(Game_State *state, int cursor_y, int cursor_x);
void set_wall_cursor(Game_Config *config, Game_State *state, Turn_State *turn_state, int key);
void place_wall(Game_Config *config, Game_State *state, Turn_State *turn_state);

#endif //QUORIDOR_LOGIC_H
