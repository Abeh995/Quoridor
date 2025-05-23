#include "config.h"

bool handle_input_names(Game_Config *config, Game_State *state) {

    int current_selection = PLAYER_1;
    int name_len = 0;

    while(1) {

        clear();
        print_name_box(config, state, current_selection);

        if(_kbhit()) {
            int key = _getch();

            if(key == 0xE0 || key == 0x00) {
                key = _getch();
                switch(key) {
                    case UP:
                        if(current_selection > PLAYER_1) current_selection--;
                        else {
                            current_selection = PLAYER_4;
                            while(state->players[current_selection].is_ai || current_selection > config->player_count - 1){
                                current_selection --;
                            }
                        }
                        break;
                    case DOWN:
                        if(current_selection < PLAYER_4) {
                            current_selection++;
                            if(state->players[current_selection].is_ai || current_selection > config->player_count - 1)
                                current_selection = PLAYER_1;
                        }
                        else current_selection = PLAYER_1;
                }
                name_len = strlen(state->players[current_selection].name);
                continue;
            }

            switch(key) {
                case ENTER:
                    clear();
                    return true;
                case ESC:
                    return false;
                case BACKSPACE:
                    if(name_len > 0) {
                        state->players[current_selection].name[--name_len] = '\0';
                    }
                    break;
                default:
                    if(isalpha(key) && name_len < MAX_NAME_LENGTH - 1) {
                        state->players[current_selection].name[name_len++] = key;
                        state->players[current_selection].name[name_len] = '\0';
                    }
            }
        }
        Sleep(30);
    }

}

void adjust_setting(Game_Config *config, int setting, bool increase_value) {

    switch(setting) {
        case MENU_BOARD_SIZE:
            if(increase_value){
                if(config->board_size < MAX_BOARD_SIZE) config->board_size += 2;
                else config->board_size = MIN_BOARD_SIZE;
            }
            else {
                if(config->board_size > MIN_BOARD_SIZE) config->board_size -= 2;
                else config->board_size = MAX_BOARD_SIZE;
            }
            break;
        case MENU_WALLS_PER_PLAYER:
            if(increase_value){
                if(config->walls_per_player < MAX_WALLS_PER_PLAYER) config->walls_per_player ++;
                else config->walls_per_player = MIN_WALLS_PER_PLAYER;
            }
            else{
                if(config->walls_per_player > MIN_WALLS_PER_PLAYER) config->walls_per_player --;
                else config->walls_per_player = MAX_WALLS_PER_PLAYER;
            }
            break;
        case MENU_PLAYERS_COUNT: // Player Count (2 or 4)
            if(config->player_count == TWO_PLAYER_GAME) config->player_count = FOUR_PLAYER_GAME;
            else{
                config->player_count = TWO_PLAYER_GAME;
                if(config->ai_count != MIN_AI_COUNT) config->ai_count = TWO_PLAYER_MAX_AI_COUNT;
            }
            break;
        case MENU_AI_COUNT:
            if(config->player_count == TWO_PLAYER_GAME )
                config->ai_count = !config->ai_count;
            else{ // 4-player
                if(increase_value){
                    if(config->ai_count < FOUR_PLAYER_MAX_AI_COUNT) config->ai_count ++;
                    else config->ai_count = MIN_AI_COUNT;
                }
                else{
                    if(config->ai_count > MIN_AI_COUNT) config->ai_count --;
                    else config->ai_count = FOUR_PLAYER_MAX_AI_COUNT;
                }
            }
            break;
        case MENU_AI_DIFFICULTY:
            if(increase_value){
                if(config->ai_difficulty < MAX_AI_DIFFICULTY) config->ai_difficulty ++;
                else config->ai_difficulty = MIN_AI_DIFFICULTY;
            }
            else{
                if(config->ai_difficulty > MIN_AI_DIFFICULTY) config->ai_difficulty --;
                else config->ai_difficulty = MAX_AI_DIFFICULTY;
            }
    }

}


void allocate_boards_memory(Game_Config *config, Game_State *state){

    int Size = ACTUAL_BOARD_SIZE(config->board_size);

    state->board.ui_board = (unsigned char**) malloc(Size * sizeof(unsigned char*)); // Rows
    for(int i = 0; i < Size; i++){
        state->board.ui_board[i] = (unsigned char*) malloc (Size * sizeof(unsigned char)); // Columns
    }

    state->board.wall_grid = (int **) malloc(Size * sizeof(int*)); // Rows
    for(int i = 0; i < Size; i++){
        state->board.wall_grid[i] = (int*) malloc (Size * sizeof(int)); // Columns
    }

    state->board.temp_wall_grid = (int **) malloc(Size * sizeof(int*)); // Rows
    for(int i = 0; i < Size; i++){
        state->board.temp_wall_grid[i] = (int*) malloc (Size * sizeof(int)); // Columns
    }

}

void free_boards_memory(Game_Config *config, Game_State *state) {

    for (int i = 0; i < ACTUAL_BOARD_SIZE(config->board_size); i++) {
        free(state->board.ui_board[i]);
        free(state->board.wall_grid[i]);
        free(state->board.temp_wall_grid[i]);
    }

    free(state->board.ui_board);
    free(state->board.wall_grid);
    free(state->board.temp_wall_grid);

}

void cleanup(Game_Config *config, Game_State *state){

    free_boards_memory(config, state);

}


bool configure_players(Game_Config *config, Game_State *state){

    strcpy(state->players[PLAYER_1].name, "PLAYER_1");
    strcpy(state->players[PLAYER_2].name, "PLAYER_2");
    strcpy(state->players[PLAYER_3].name, "PLAYER_3");
    strcpy(state->players[PLAYER_4].name, "PLAYER_4");

    for(int i = 0; i < FOUR_PLAYER_GAME; i++){
        state->players[i].y = INVALID_VALUE;
        state->players[i].x = INVALID_VALUE;
        state->players[i].walls_left = INVALID_VALUE;
        state->players[i].blocked_turn_left = INVALID_VALUE;
        state->players[i].move_count = INVALID_VALUE;
        state->players[i].is_ai = false;
    }
    for(int i = 0; i < config->ai_count; i++){
        state->players[config->player_count - i - 1].is_ai = true;
        if(i == 0)
            strcpy(state->players[config->player_count - i - 1].name, "Alex");
        else if(i == 1)
            strcpy(state->players[config->player_count - i - 1].name, "Charlotte");
        else
            strcpy(state->players[config->player_count - i - 1].name, "Jia");

    }

    for(int  i = 0; i < config->player_count; i++){
        state->players[i].walls_left = config->walls_per_player;
        state->players[i].blocked_turn_left = 0;
        state->players[i].move_count = 0;
    }


    int first_cell = 1;
    int last_cell = ACTUAL_BOARD_SIZE(config->board_size) - 2;
    int mid_cell = ACTUAL_BOARD_SIZE(config->board_size) / 2;

    state->players[PLAYER_1].y = first_cell;
    state->players[PLAYER_1].x = mid_cell;

    state->players[PLAYER_2].y = last_cell;
    state->players[PLAYER_2].x = mid_cell;

    if(config->player_count != TWO_PLAYER_GAME){
        state->players[PLAYER_3].y = mid_cell;
        state->players[PLAYER_3].x = first_cell;

        state->players[PLAYER_4].y = mid_cell;
        state->players[PLAYER_4].x = last_cell;

    }

    return handle_input_names(config, state);
}

bool handle_main_menu(Game_Config *config, Game_State *state){

    int current_selection = MENU_NEW_GAME;

    while(1){

        clear();
        print_main_menu(current_selection);

        Keys key = handle_user_input();
        switch (key) {

            case UP:
            case LEFT:
                if (current_selection > MENU_NEW_GAME) current_selection--;
                else current_selection = MENU_QUIT;
                break;

            case DOWN:
            case RIGHT:
                if (current_selection < MENU_QUIT) current_selection++;
                else current_selection = MENU_NEW_GAME;
                break;

            case ENTER:
                switch (current_selection) {

                    case MENU_NEW_GAME:
                        if(game_setup_menu(config, state))
                            return true;
                        break;

                    case MENU_LOAD_GAME:

                        break;

                    case MENU_OPTIONS:

                        break;

                    case MENU_QUIT:
                        //"are you sure to quit?" message
                        return false;

                }

            case ESC:
                //"are you sure to quit?" message
                break;
        }

        Sleep(10);
    }

}

bool game_setup_menu(Game_Config *config, Game_State *state) {

    int current_selection = MENU_BOARD_SIZE;

    while(1) {
        // handle adjusting config
        clear();
        print_setup_menu(config, state, current_selection);
        int key = handle_user_input();
        switch(key) {
            case UP:
                if(current_selection > MENU_BOARD_SIZE) current_selection--;
                else current_selection = MENU_AI_DIFFICULTY;
                break;
            case DOWN:
                if(current_selection < MENU_AI_DIFFICULTY) current_selection++;
                else current_selection = MENU_BOARD_SIZE; // first option;
                break;
            case LEFT: // Left - Decrease value
                adjust_setting(config, current_selection, false);
                break;
            case RIGHT: // Right - Increase value
                adjust_setting(config, current_selection, true);
                break;
            case ENTER:
                if(configure_new_game(config, state))
                    return true;
                break;
            case ESC:
                return false;
        }
        Sleep(10);
    }

}

void setup_wall_grid_layout(Game_Config * config, Game_State * state){

    int size = ACTUAL_BOARD_SIZE(config->board_size);

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            state->board.wall_grid[i][j] = READY_TO_PLACE_WALL;
        }
    }

    for(int i = 0; i < size; i++){
        state->board.wall_grid[0][i] = BORDER_WALL;
        state->board.wall_grid[size - 1][i] = BORDER_WALL;
        state->board.wall_grid[i][0] = BORDER_WALL;
        state->board.wall_grid[i][size - 1] = BORDER_WALL;
    }

}

void setup_boards_layout(Game_Config *config, Game_State *state){ // not complete yet

    setup_ui_board_layout(config, state);
    setup_wall_grid_layout(config, state);

}


bool configure_new_game(Game_Config *config, Game_State *state){

    allocate_boards_memory(config, state);
    setup_boards_layout(config, state);

    state->board.size = ACTUAL_BOARD_SIZE(config->board_size);
    state->turn = 0;
    state->placed_walls_count = 0;
    if(config->magic_box) state->last_magic_box_turn = 0;
    else state->last_magic_box_turn = INVALID_VALUE;
    state->is_the_match_over = false;

    return configure_players(config, state);

}