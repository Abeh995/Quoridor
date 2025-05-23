#include "logic.h"

bool is_wall_banned(Game_State * state, int y, int x){
    // just check wall state
    return state->board.wall_grid[y][x] != READY_TO_PLACE_WALL;

}

bool is_empty_cell(Game_State * state, int y, int x){
    // just check destination to be empty
    return state->board.ui_board[y][x] == EMPTY_CELL;
}


bool validate_move(Game_Config *config, Game_State *state, Turn_State *turn_state, int key){

    int turn = state->turn % config->player_count;
    int cursor_y = state->players[turn].y;
    int cursor_x = state->players[turn].x;
    Game_State * temp_state = state;
    bool wall_banned = false;


    switch (key) {

        case UP:

            if(is_wall_banned(state, cursor_y - 1, cursor_x))
                return false;

            for(int i = 1; !wall_banned ; i += 2){
                if( is_wall_banned(state, cursor_y - i, cursor_x ) ){
                    wall_banned = true;
                    temp_state->players[turn].y = cursor_y - i + 1;
                    temp_state->players[turn].x = cursor_x;
                }
                else if( is_empty_cell(state, cursor_y - i - 1, cursor_x) ){
                    //move is valid
                    turn_state->is_move_valid = true;
                    turn_state->move_hover_y = cursor_y - i - 1;
                    turn_state->move_hover_x = cursor_x;
                    return true;
                }
            }

            if(validate_move(config, temp_state, turn_state, LEFT)){
                if(validate_move(config, temp_state, turn_state, RIGHT)){
                    key = handle_user_input();
                    validate_move(config, temp_state, turn_state, key);
                }
                else
                    return true;
            }
            else if(validate_move(config, temp_state, turn_state, RIGHT))
                return true;
            return false;

        case DOWN:

            if(is_wall_banned(state, cursor_y + 1, cursor_x))
                return false;

            for(int i = 1; !wall_banned ; i += 2){
                if( is_wall_banned(state, cursor_y + i, cursor_x ) ){
                    wall_banned = true;
                    temp_state->players[turn].y = cursor_y + i - 1;
                    temp_state->players[turn].x = cursor_x;
                }
                else if( is_empty_cell(state, cursor_y + i + 1, cursor_x) ){
                    //move is valid
                    turn_state->is_move_valid = true;
                    turn_state->move_hover_y = cursor_y + i + 1;
                    turn_state->move_hover_x = cursor_x;
                    return true;
                }
            }

            if(validate_move(config, temp_state, turn_state, LEFT)){
                if(validate_move(config, temp_state, turn_state, RIGHT)){
                    key = handle_user_input();
                    validate_move(config, temp_state, turn_state, key);
                }
                else
                    return true;
            }
            else if(validate_move(config, temp_state, turn_state, RIGHT))
                return true;
            return false;

        case LEFT:

            if(is_wall_banned(state, cursor_y, cursor_x - 1))
                return false;

            for(int i = 1; !wall_banned ; i += 2){
                if( is_wall_banned(state, cursor_y, cursor_x - i) ){
                    wall_banned = true;
                    temp_state->players[turn].y = cursor_y;
                    temp_state->players[turn].x = cursor_x - i + 1;
                }
                else if( is_empty_cell(state, cursor_y, cursor_x - i - 1) ){
                    //move is valid
                    turn_state->is_move_valid = true;
                    turn_state->move_hover_y = cursor_y;
                    turn_state->move_hover_x = cursor_x - i - 1;
                    return true;
                }
            }

            if(validate_move(config, temp_state, turn_state, UP)){
                if(validate_move(config, temp_state, turn_state, DOWN)){
                    key = handle_user_input();
                    validate_move(config, temp_state, turn_state, key);
                }
                else
                    return true;
            }
            else if(validate_move(config, temp_state, turn_state, DOWN))
                return true;
            return false;

        case RIGHT:

            if(is_wall_banned(state, cursor_y, cursor_x + 1))
                return false;

            for(int i = 1; !wall_banned ; i += 2){
                if( is_wall_banned(state, cursor_y, cursor_x + i) ){
                    wall_banned = true;
                    temp_state->players[turn].y = cursor_y;
                    temp_state->players[turn].x = cursor_x + i - 1;
                }
                else if( is_empty_cell(state, cursor_y, cursor_x + i + 1) ){
                    //move is valid
                    turn_state->is_move_valid = true;
                    turn_state->move_hover_y = cursor_y;
                    turn_state->move_hover_x = cursor_x + i + 1;
                    return true;
                }
            }

            if(validate_move(config, temp_state, turn_state, UP)){
                if(validate_move(config, temp_state, turn_state, DOWN)){
                    key = handle_user_input();
                    validate_move(config, temp_state, turn_state, key);
                }
                else
                    return true;
            }
            else if(validate_move(config, temp_state, turn_state, DOWN))
                return true;
            return false;

    }

    return false;

}

void move_pawn(Game_Config *config, Game_State *state, Turn_State *turn_state){

    int turn = state->turn % config->player_count;

    int old_y = state->players[turn].y;
    int old_x = state->players[turn].x;
    int new_y = turn_state->move_hover_y;
    int new_x = turn_state->move_hover_x;
    state->board.ui_board[new_y][new_x] = state->board.ui_board[old_y][old_x];
    state->board.ui_board[old_y][old_x] = EMPTY_CELL;

    state->players[turn].y = new_y;
    state->players[turn].x = new_x;

}

void copy_wall_grid(Game_State * state){

    int size = state->board.size;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            state->board.temp_wall_grid[i][j] = state->board.wall_grid[i][j];
        }
    }

}

void copy_place_wall(Game_State * state, Turn_State * turn_state){

    int x = turn_state->wall_hover_x;
    int y = turn_state->wall_hover_y;

    if(turn_state->wall_type == HORIZONTAL){
        state->board.temp_wall_grid[y][x - 1] = PLAYERS_PLACED_WALL;
        state->board.temp_wall_grid[y][x] = PLAYERS_PLACED_WALL;
        state->board.temp_wall_grid[y][x + 1] = PLAYERS_PLACED_WALL;
    }
    else{
        state->board.temp_wall_grid[y - 1][x] = PLAYERS_PLACED_WALL;
        state->board.temp_wall_grid[y][x] = PLAYERS_PLACED_WALL;
        state->board.temp_wall_grid[y + 1][x] = PLAYERS_PLACED_WALL;
    }

}

void setup_temp_wall_grid(Game_Config * config, Game_State * state){ // not complete yet

    copy_wall_grid(state);
//    copy_place_wall(state, turn_state);

}

bool is_out_of_board(Game_State * state, int dx, int dy){

    if(state->board.temp_wall_grid[dy][dx] == BORDER_WALL)
        return true;
    return false;

}

bool check_up_side(Game_State * state, int dx, int dy){

    state->board.temp_wall_grid[dy][dx] = UP_CHECKED;
    if(state->board.temp_wall_grid[dy - 1][dx] == READY_TO_PLACE_WALL){
        return true;
    }
    return false;

}

bool check_down_side(Game_State * state, int dx, int dy){

    state->board.temp_wall_grid[dy][dx] = DOWN_CHECKED;
    if(state->board.temp_wall_grid[dy + 1][dx] == READY_TO_PLACE_WALL){
        return true;
    }
    return false;

}

bool check_left_side(Game_State * state, int dx, int dy){

    state->board.temp_wall_grid[dy][dx] = LEFT_CHECKED;
    if(state->board.temp_wall_grid[dy][dx - 1] == READY_TO_PLACE_WALL){
        return true;
    }
    return false;

}

bool check_right_side(Game_State * state, int dx, int dy){

    state->board.temp_wall_grid[dy][dx] = RIGHT_CHECKED;
    if(state->board.temp_wall_grid[dy][dx + 1] == READY_TO_PLACE_WALL){
        return true;
    }
    return false;

}

void paint(Game_State * state, int dx, int dy){

    if (is_out_of_board(state, dx, dy))
        return;

    if(state->board.temp_wall_grid[dy][dx] == NO_CHECKED)
        if(check_up_side(state, dx, dy))
            paint(state, dx, dy - 2);

    if(state->board.temp_wall_grid[dy][dx] == UP_CHECKED)
        if(check_down_side(state, dx, dy))
            paint(state, dx, dy + 2);

    if(state->board.temp_wall_grid[dy][dx] == DOWN_CHECKED)
        if(check_left_side(state, dx, dy))
            paint(state, dx - 2, dy);

    if(state->board.temp_wall_grid[dy][dx] == LEFT_CHECKED)
        if(check_right_side(state, dx, dy))
            paint(state, dx + 2, dy);

    if(state->board.temp_wall_grid[dy][dx] == RIGHT_CHECKED)
        return;
}

bool can_playerX_reach_goal_line(Game_State * state, int dx, int dy, int playerNUM){

    int size = state->board.size;

    paint(state, dx, dy);

    switch (playerNUM) {

        case PLAYER_1:

            for(int i = 1; i < size; i += 2){
                if (state->board.temp_wall_grid[LAST_CELL(size)][i] == RIGHT_CHECKED)
                    return true;
            }
            return false;

        case PLAYER_2:

            for(int i = 1; i < size; i += 2){
                if (state->board.temp_wall_grid[FIRST_CELL][i] == RIGHT_CHECKED)
                    return true;
            }
            return false;

        case PLAYER_3:

            for(int i = 1; i < size; i += 2){
                if (state->board.temp_wall_grid[i][LAST_CELL(size)] == RIGHT_CHECKED)
                    return true;
            }
            return false;

        case PLAYER_4:

            for(int i = 1; i < size; i += 2){
                if (state->board.temp_wall_grid[FIRST_CELL][i] == RIGHT_CHECKED)
                    return true;
            }
            return false;

    }

}

bool validate_players_target_way(Game_Config * config, Game_State * state, Turn_State *turn_state){

    int dy, dx;
    bool new_wall_is_valid = true;

    for(int i = 0; i < config->player_count; i++){

        setup_temp_wall_grid(config, state);

        dy = state->players[i].y;
        dx = state->players[i].x;

        switch (i) {

            case PLAYER_1:

                if( !can_playerX_reach_goal_line(state, dx, dy, PLAYER_1) )
                    new_wall_is_valid = false;
                break;

            case PLAYER_2:

                if( !can_playerX_reach_goal_line(state, dx, dy, PLAYER_2) )
                    new_wall_is_valid = false;
                break;

            case PLAYER_3:

                if( !can_playerX_reach_goal_line(state, dx, dy, PLAYER_3) )
                    new_wall_is_valid = false;
                break;

            case PLAYER_4:

                if( !can_playerX_reach_goal_line(state, dx, dy, PLAYER_4) )
                    new_wall_is_valid = false;
                break;

        }
    }

    if (new_wall_is_valid)
        return true;
    return false;

}

bool horizontal_is_valid(Game_State *state, int cursor_y, int cursor_x){

    return state->board.wall_grid[cursor_y][cursor_x - 1] == READY_TO_PLACE_WALL
           && state->board.wall_grid[cursor_y][cursor_x + 1] == READY_TO_PLACE_WALL;

}

bool vertical_is_valid(Game_State *state, int cursor_y, int cursor_x){

    return state->board.wall_grid[cursor_y - 1][cursor_x] == READY_TO_PLACE_WALL
           && state->board.wall_grid[cursor_y + 1][cursor_x] == READY_TO_PLACE_WALL;

}

bool is_empty_wall_cell(Game_State *state, int cursor_y, int cursor_x){

    return state->board.wall_grid[cursor_y][cursor_x] == READY_TO_PLACE_WALL;

}

void set_primary_wall_cursor(Game_Config *config, Game_State *state, Turn_State *turn_state){

    int size = ACTUAL_BOARD_SIZE(config->board_size);

    // finding first empty wall_cell to set primary
    for(int i = 2; i < size; i += 2){
        for(int j = 2; j < size; j += 2){
            if(is_empty_wall_cell(state, i, j)){
                if(horizontal_is_valid(state, i, j)){
                    // EMPTY WALL_CELL TO PLACE HORIZONTAL WALL
                    turn_state->wall_type = HORIZONTAL;
                    turn_state->wall_hover_y = i;
                    turn_state->wall_hover_x = j;
                    return;
                }
                else if(vertical_is_valid(state, i, j)){
                    // EMPTY WALL_CELL TO PLACE VERTICAL WALL
                    turn_state->wall_type = VERTICAL;
                    turn_state->wall_hover_y = i;
                    turn_state->wall_hover_x = j;
                    return;
                }
            }
        }
    }

}


bool cursor_is_in_range(Game_State *state, int cursor_y, int cursor_x){

    return state->board.wall_grid[cursor_y][cursor_x] != INVALID_VALUE;

}

void set_wall_cursor(Game_Config *config, Game_State *state, Turn_State *turn_state, int key){

    int turn = state->turn % config->player_count;

    if( state->players[turn].walls_left <= 0){
        //any warning
        return;
    }

    if(turn_state->wall_hover_x == INVALID_VALUE
    || turn_state->wall_hover_y == INVALID_VALUE){
        set_primary_wall_cursor(config, state, turn_state);
        return;
    }

    int crs_x = turn_state->wall_hover_x;
    int crs_y = turn_state->wall_hover_y;

    switch (key) {

        case NUM_5:  // switch wall type

            if(turn_state->wall_type == HORIZONTAL){
                if(vertical_is_valid(state, crs_y, crs_x))
                    turn_state->wall_type = VERTICAL;
            }
            else{
                if(horizontal_is_valid(state, crs_y, crs_x))
                    turn_state->wall_type = HORIZONTAL;
            }
            return;

        case NUM_8: // move-up wall cursor

            while (cursor_is_in_range(state, crs_y, crs_x)){
                crs_y -= 2;

                if(is_empty_wall_cell(state, crs_y, crs_x)){
                    if(turn_state->wall_type == HORIZONTAL){
                        if(horizontal_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_hover_y = crs_y;
                            return;
                        }
                        else if(vertical_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_type = VERTICAL;
                            turn_state->wall_hover_y = crs_y;
                            return;
                        }
                    }
                    else{ // Wall type is Vertical
                        if(vertical_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_hover_y = crs_y;
                            return;
                        }
                        else if(horizontal_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_type = HORIZONTAL;
                            turn_state->wall_hover_y = crs_y;
                            return;
                        }
                    }
                }
                else{
                    // any warning !
                }
            }
            break;

        case NUM_2: // move-down wall cursor

            while (cursor_is_in_range(state, crs_y, crs_x)){
                crs_y += 2;

                if(is_empty_wall_cell(state, crs_y, crs_x)){
                    if(turn_state->wall_type == HORIZONTAL){
                        if(horizontal_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_hover_y = crs_y;
                            return;
                        }
                        else if(vertical_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_type = VERTICAL;
                            turn_state->wall_hover_y = crs_y;
                            return;
                        }
                    }
                    else{ // current Wall type is Vertical
                        if(vertical_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_hover_y = crs_y;
                            return;
                        }
                        else if(horizontal_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_type = HORIZONTAL;
                            turn_state->wall_hover_y = crs_y;
                            return;
                        }
                    }
                }
                else{
                    // any warning !
                }
            }
            break;

        case NUM_4: // move-left wall cursor

            while (cursor_is_in_range(state, crs_y, crs_x)){
                crs_x -= 2;

                if(is_empty_wall_cell(state, crs_y, crs_x)){
                    if(turn_state->wall_type == HORIZONTAL){
                        if(horizontal_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_hover_x = crs_x;
                            return;
                        }
                        else if(vertical_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_type = VERTICAL;
                            turn_state->wall_hover_x = crs_x;
                            return;
                        }
                    }
                    else{ // current Wall type is Vertical
                        if(vertical_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_hover_x = crs_x;
                            return;
                        }
                        else if(horizontal_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_type = HORIZONTAL;
                            turn_state->wall_hover_x = crs_x;
                            return;
                        }
                    }
                }
                else{
                    // any warning !
                }
            }
            break;

        case NUM_6: // move-right wall cursor

            while (cursor_is_in_range(state, crs_y, crs_x)){
                crs_x += 2;

                if(is_empty_wall_cell(state, crs_y, crs_x)){
                    if(turn_state->wall_type == HORIZONTAL){
                        if(horizontal_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_hover_x = crs_x;
                            return;
                        }
                        else if(vertical_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_type = VERTICAL;
                            turn_state->wall_hover_x = crs_x;
                            return;
                        }
                    }
                    else{ // current Wall type is Vertical
                        if(vertical_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_hover_x = crs_x;
                            return;
                        }
                        else if(horizontal_is_valid(state, crs_y, crs_x)){
                            turn_state->wall_type = HORIZONTAL;
                            turn_state->wall_hover_x = crs_x;
                            return;
                        }
                    }
                }
                else{
                    // any warning !
                }
            }
            break;
    }

}

void place_wall(Game_Config *config, Game_State *state, Turn_State *turn_state){

    int turn = state->turn % config->player_count;
    int x = turn_state->wall_hover_x;
    int y = turn_state->wall_hover_y;

    if(turn_state->wall_type == HORIZONTAL){
        state->board.wall_grid[y][x - 1] = PLAYERS_PLACED_WALL;
        state->board.wall_grid[y][x] = PLAYERS_PLACED_WALL;
        state->board.wall_grid[y][x + 1] = PLAYERS_PLACED_WALL;

        state->board.ui_board[y][x - 1] = '*';
        state->board.ui_board[y][x] = '*';
        state->board.ui_board[y][x + 1] = '*';
    }
    else{
        state->board.wall_grid[y - 1][x] = PLAYERS_PLACED_WALL;
        state->board.wall_grid[y][x] = PLAYERS_PLACED_WALL;
        state->board.wall_grid[y + 1][x] = PLAYERS_PLACED_WALL;

        state->board.ui_board[y - 1][x] = '*';
        state->board.ui_board[y][x] = '*';
        state->board.ui_board[y + 1][x] = '*';
    }

    state->players[turn].walls_left --;

}
