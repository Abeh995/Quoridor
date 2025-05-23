#include "ui.h"

#include <windows.h>

void clear(){
    system("cls");
}

// ANSI Escape Codes
void enable_ansi() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void initialize_ui(){

    SetConsoleOutputCP(CP_UTF8);
    enable_ansi();

}

void setup_ui_board_layout(Game_Config *config, Game_State *state){

    // setting up pawn_cells with " "
    for(int i = 0; i < ACTUAL_BOARD_SIZE(config->board_size); i++){
        for(int j = 0; j < ACTUAL_BOARD_SIZE(config->board_size); j++ ){
            state->board.ui_board[i][j] = ' ';
        }
    }

    //setting up horizontal wall_cells
    for(int i = 2; i < ACTUAL_BOARD_SIZE(config->board_size) -1; i += 2){
        for(int j = 1; j < ACTUAL_BOARD_SIZE(config->board_size) -1; j += 2 ){
            state->board.ui_board[i][j] = '-';
        }
    }

    //setting up vertical wall_cells
    for(int i = 1; i < ACTUAL_BOARD_SIZE(config->board_size) -1; i += 2){
        for(int j = 2; j < ACTUAL_BOARD_SIZE(config->board_size) -1; j += 2 ){
            state->board.ui_board[i][j] = '|';
        }
    }

    //setting up main wall_cells
    for(int i = 2; i < ACTUAL_BOARD_SIZE(config->board_size) -1; i += 2){
        for(int j = 2; j < ACTUAL_BOARD_SIZE(config->board_size) -1; j += 2 ){
            state->board.ui_board[i][j] = '+';
        }
    }

    int first_cell = 1;
    int last_cell = ACTUAL_BOARD_SIZE(config->board_size) - 2;
    int mid_cell = ACTUAL_BOARD_SIZE(config->board_size) / 2;

    state->board.ui_board[first_cell][mid_cell] = '1';
    state->board.ui_board[last_cell][mid_cell] = '2';
    if (config->player_count != TWO_PLAYER_GAME){
        state->board.ui_board[mid_cell][first_cell] = '3';
        state->board.ui_board[mid_cell][last_cell] = '4';
    }

}

void print_main_menu(int current_selection) {

    printf("┌───────────────┐\n");
    printf("│   Main Menu   │\n");
    printf("├───────────────┤\n");

    // New Game
    printf("│ ");
    if (current_selection == MENU_NEW_GAME) printf(GREEN "> New Game < " RESET); // •
    else printf("  New Game   ");
    printf(" │\n│               │\n");

    // Load Game
    printf("│ ");
    if (current_selection == MENU_LOAD_GAME) printf(GREEN "> Load Game < " RESET);
    else printf("  Load Game   ");
    printf("│\n│               │\n");

    // Options
    printf("│ ");
    if (current_selection == MENU_OPTIONS) printf(BLUE "> Options < " RESET);
    else printf("  Options   ");
    printf("  │\n│               │\n");

    // Quit
    printf("│ ");
    if (current_selection == MENU_QUIT) printf(RED "> Quit < " RESET);
    else printf("  Quit   ");
    printf("     │\n└───────────────┘\n");

}

void print_setup_menu(Game_Config *config, Game_State *state, int current_selection){

    static int blink_state = 0;
    static clock_t last_blink = 0;

    printf("┌─────────────────────────────┐\n");
    printf("│         Game Setup          │\n");
    printf("├─────────────────────────────┤\n");
    printf("│                             │\n");

    if(current_selection == MENU_BOARD_SIZE) {
        clock_t now = clock();
        if((now - last_blink)*1000.0/CLOCKS_PER_SEC > BLINK_RATE_MS) {
            blink_state = !blink_state;
            last_blink = now;
        }
        printf("│ " OPTION_COLOR "Board Size:     "
               BRACKET_COLOR "%s"
               OPTION_COLOR "%2d"
               BRACKET_COLOR " x "
               OPTION_COLOR "%-2d"
               BRACKET_COLOR "%s"
               RESET " │\n",
               (blink_state ? "< " : "  "),
               config->board_size,
               config->board_size,
               (blink_state ? " >" : "  "));
    } else {
        printf("│ Board Size:       %2d x %-2d   │\n",
               config->board_size,
               config->board_size);
    }
    printf("│                             │\n");

    if(current_selection == MENU_WALLS_PER_PLAYER) {
        clock_t now = clock();
        if((now - last_blink)*1000.0/CLOCKS_PER_SEC > BLINK_RATE_MS) {
            blink_state = !blink_state;
            last_blink = now;
        }
        printf("│ " OPTION_COLOR "Walls/Player:     "
               BRACKET_COLOR "%s"
               OPTION_COLOR "%2d"
               BRACKET_COLOR "%s"
               RESET "    │\n",
               (blink_state ? "< " : "  "),
               config->walls_per_player,
               (blink_state ? " >" : "  "));
    } else {
        printf("│ Walls/Player:       %2d      │\n",
               config->walls_per_player);
    }
    printf("│                             │\n");

    if(current_selection == MENU_PLAYERS_COUNT) {
        clock_t now = clock();
        if((now - last_blink)*1000.0/CLOCKS_PER_SEC > BLINK_RATE_MS) {
            blink_state = !blink_state;
            last_blink = now;
        }
        printf("│ " OPTION_COLOR "Players:           "
               BRACKET_COLOR "%s"
               OPTION_COLOR "%d"
               BRACKET_COLOR "%s"
               RESET "    │\n",
               (blink_state ? "< " : "  "),
               config->player_count,
               (blink_state ? " >" : "  "));
    } else {
        printf("│ Players:             %d      │\n",
               config->player_count);
    }
    printf("│                             │\n");

    if(current_selection == MENU_AI_COUNT) {
        clock_t now = clock();
        if((now - last_blink)*1000.0/CLOCKS_PER_SEC > BLINK_RATE_MS) {
            blink_state = !blink_state;
            last_blink = now;
        }
        printf("│ " OPTION_COLOR "AI Opponents:      "
               BRACKET_COLOR "%s"
               OPTION_COLOR "%d"
               BRACKET_COLOR "%s"
               RESET "    │\n",
               (blink_state ? "< " : "  "),
               config->ai_count,
               (blink_state ? " >" : "  "));
    } else {
        printf("│ AI Opponents:        %d      │\n",
               config->ai_count);
    }
    printf("│                             │\n");

    if(current_selection == MENU_AI_DIFFICULTY) {
        clock_t now = clock();
        if((now - last_blink)*1000.0/CLOCKS_PER_SEC > BLINK_RATE_MS) {
            blink_state = !blink_state;
            last_blink = now;
        }
        printf("│ " OPTION_COLOR "AI Difficulty:     "
               BRACKET_COLOR "%s"
               OPTION_COLOR "%d"
               BRACKET_COLOR "%s"
               RESET "    │\n",
               (blink_state ? "< " : "  "),
               config->ai_difficulty,
               (blink_state ? " >" : "  "));
    } else {
        printf("│ AI Difficulty:       %d      │\n",
               config->ai_difficulty);
    }
    printf("│                             │\n");
    printf("└─────────────────────────────┘\n");

}



void print_name_box(Game_Config *config, Game_State *state, int current_selection) {

    static int blink_state = 0;
    static clock_t last_blink = 0;

    printf("┌──────────────────────────────────────┐\n");
    printf("│        Enter   Player   Names        │\n");
    printf("├──────────────────────────────────────┤\n");
    printf("│                                      │\n");

    // Player 1
    if(current_selection == PLAYER_1) {
        clock_t now = clock();
        if((now - last_blink) * 1000.0 / CLOCKS_PER_SEC > BLINK_RATE_MS) {
            blink_state = !blink_state;
            last_blink = now;
        }

        printf("│ " OPTION_COLOR "Player 1:     ");

        if(blink_state) {
            printf("                    ");
        } else {
            printf("%-20s", state->players[current_selection].name);
        }

        printf(RESET "   │\n");
    } else {
        printf("│ Player 1:     %-20s   │\n", state->players[PLAYER_1].name);
    }
    printf("│                                      │\n");

    // player 2
    if (!state->players[PLAYER_2].is_ai) {
        if(current_selection == PLAYER_2) {
            clock_t now = clock();
            if((now - last_blink) * 1000.0 / CLOCKS_PER_SEC > BLINK_RATE_MS) {
                blink_state = !blink_state;
                last_blink = now;
            }

            printf("│ " OPTION_COLOR "Player 2:     ");

            if(blink_state) {
                printf("                    ");
            } else {
                printf("%-20s", state->players[current_selection].name);
            }

            printf(RESET "   │\n");
        } else {
            printf("│ Player 2:     %-20s   │\n", state->players[PLAYER_2].name);
        }
    } else {
        printf("│ Player 2:     " BRIGHT_CYAN "AI-" RESET "%-17s   │\n", state->players[PLAYER_2].name);
    }
    printf("│                                      │\n");

    // player 3,4
    if (config->player_count == FOUR_PLAYER_GAME) {
        if (!state->players[PLAYER_3].is_ai) {
            if(current_selection == PLAYER_3) {
                clock_t now = clock();
                if((now - last_blink) * 1000.0 / CLOCKS_PER_SEC > BLINK_RATE_MS) {
                    blink_state = !blink_state;
                    last_blink = now;
                }

                printf("│ " OPTION_COLOR "Player 3:     ");

                if(blink_state) {
                    printf("                    ");
                } else {
                    printf("%-20s", state->players[current_selection].name);
                }

                printf(RESET "   │\n");
            } else {
                printf("│ Player 3:     %-20s   │\n", state->players[PLAYER_3].name);
            }
        } else {
            printf("│ Player 3:     " BRIGHT_CYAN "AI-" RESET "%-17s   │\n", state->players[PLAYER_3].name);
        }
        printf("│                                      │\n");

        //player 4
        if ( !state->players[PLAYER_4].is_ai ) {
            if(current_selection == PLAYER_4) {
                clock_t now = clock();
                if((now - last_blink) * 1000.0 / CLOCKS_PER_SEC > BLINK_RATE_MS) {
                    blink_state = !blink_state;
                    last_blink = now;
                }

                printf("│ " OPTION_COLOR "Player 4:     ");

                if(blink_state) {
                    printf("                    ");
                } else {
                    printf("%-20s", state->players[current_selection].name);
                }

                printf(RESET "   │\n");
            } else {
                printf("│ Player 4:     %-20s   │\n", state->players[PLAYER_4].name);
            }
        } else {
            printf("│ Player 4:     " BRIGHT_CYAN "AI-" RESET "%-17s   │\n", state->players[PLAYER_4].name);
        }
        printf("│                                      │\n");
    }

    printf("├──────────────────────────────────────┤\n");
    printf("│ [Enter] START GAME  [Esc] Setup Menu │\n");
    printf("└──────────────────────────────────────┘\n");

}

bool pawn_cell(Position tile){

    return tile.dy % 2 == 1 && tile.dx % 2 == 1;

}

bool is_move_hover(Position tile, Turn_State *turn_state){

    return tile.dy == turn_state->move_hover_y
            && tile.dx == turn_state->move_hover_x;

}

// current player's pawn
bool current_player_pawn(Game_State *state, Position tile, Position pawn){

    return state->board.ui_board[tile.dy][tile.dx]
           == state->board.ui_board[pawn.dy][pawn.dx];

}

bool placed_wall(Game_State *state, Position tile){

    return state->board.ui_board[tile.dy][tile.dx] == DISPLAY_WALL;

}

bool first_V_wall_cell(Position tile, Turn_State *turn_state){

    return tile.dy + 1 == turn_state->wall_hover_y
           && tile.dx == turn_state->wall_hover_x
           && turn_state->wall_type == VERTICAL;

}

bool first_H_wall_cell(Position tile, Turn_State *turn_state){

    return tile.dy == turn_state->wall_hover_y
           && tile.dx + 1 == turn_state->wall_hover_x
           && turn_state->wall_type == HORIZONTAL;

}

bool third_V_wall_cell(Position tile, Turn_State *turn_state) {

    return tile.dy - 1 == turn_state->wall_hover_y
           && tile.dx == turn_state->wall_hover_x
           && turn_state->wall_type == VERTICAL;

}

bool third_H_wall_cell(Position tile, Turn_State *turn_state) {

    return tile.dy == turn_state->wall_hover_y
           && tile.dx - 1 == turn_state->wall_hover_x
           && turn_state->wall_type == HORIZONTAL;

}

bool first_wall_cell_hovered (Position tile, Turn_State *turn_state){

    return first_V_wall_cell(tile, turn_state)
           || first_H_wall_cell(tile, turn_state);

}

bool third_wall_cell_hovered (Position tile, Turn_State *turn_state) {

    return third_V_wall_cell(tile, turn_state)
           || third_H_wall_cell(tile, turn_state);

}

bool main_wall_cell(Position tile, Turn_State *turn_state) {

    return tile.dy == turn_state->wall_hover_y
           && tile.dx == turn_state->wall_hover_x;

}

void print_current_pawn(Game_State *state, Position pawn){

    printf(BRIGHT_MAGENTA " %c" RESET, state->board.ui_board[pawn.dy][pawn.dx]);

}

void print_hovered_pawn(Game_State *state, Position pawn){

    printf(CURSOR_COLOR " %c" RESET, state->board.ui_board[pawn.dy][pawn.dx]);

}

void print_default_cell(Game_State *state, Position tile){

    printf(RESET " %c", state->board.ui_board[tile.dy][tile.dx]);

}

void print_placed_wall(Game_State *state, Position tile){

    printf( BRIGHT_RED BOLD " %c" F_RESET RESET, state->board.ui_board[tile.dy][tile.dx]);

}

void print_secondary_hovered_wall(Game_State *state, Position tile){

    printf(BRIGHT_RED " %c" RESET, state->board.ui_board[tile.dy][tile.dx]);

}

void print_main_hovered_wall(Game_State *state, Position tile){

    printf(CURSOR_COLOR " %c" RESET, state->board.ui_board[tile.dy][tile.dx]);

}

bool secondary_wall_hovered(Position tile, Turn_State *turn_state){

    return first_wall_cell_hovered(tile, turn_state)
           || third_wall_cell_hovered(tile, turn_state);

}

void print_pawn_cell(Game_State *state, Turn_State *turn_state, Position tile, Position current_pawn){

    // find current player pawn
    if(current_player_pawn(state, tile, current_pawn))
        print_current_pawn(state, current_pawn);

        //not found, look for move_cursor
    else if(turn_state->current_state == MOVE){

        if(is_move_hover(tile, turn_state))
            print_hovered_pawn(state, current_pawn);
        else
            print_default_cell(state, tile);
    }
    else
        print_default_cell(state, tile);

}

void print_wall_cell(Game_State *state, Turn_State *turn_state, Position tile){

    if (placed_wall(state, tile))
        print_placed_wall(state, tile);

        // wall_cursor
    else if(turn_state->current_state == WALL_PLACEMENT){

        // check secondary wall_cursor cells
        if(secondary_wall_hovered(tile, turn_state))
            print_secondary_hovered_wall(state, tile);

            // check main(second) wall_cursor cell
        else if(main_wall_cell(tile, turn_state))
            print_main_hovered_wall(state, tile);

        else
            print_default_cell(state, tile);
    }
    else
        print_default_cell(state, tile);

}

void print_ui_board(Game_Config *config, Game_State *state, Turn_State *turn_state) {

    int size = ACTUAL_BOARD_SIZE(config->board_size);
    int turn = state->turn % config->player_count;

    Position current_pawn ={
            .dy = state->players[turn].y,
            .dx = state->players[turn].x
    },
    //print tile:
    tile = {
            .dy = 0,
            .dx = 0
    };

    // draw board.ui_board box
    printf(BRIGHT_CYAN"    ┌");
    for (int i = 0; i < 2 * size - 3; i++){
        printf("─");
    }
    printf("┐\n ");

    tile.dy = 1;
    for(int num = config->board_size - 1; tile.dy < size - 1 ; tile.dy++){

        // draw box
        if (tile.dy % 2 == 0) {
            printf(" %2d│", num);
            num--;
        } else
            printf("   │");

        for(tile.dx = 1; tile.dx < size -1; tile.dx++){

            if(pawn_cell(tile))
                print_pawn_cell(state, turn_state, tile, current_pawn);

            // wall_cells (two wall_position types)
            else
                print_wall_cell(state, turn_state, tile);

        }
        printf(BRIGHT_CYAN" │");
        printf("\n ");

    }

    printf("   └");
    for (tile.dy = 0; tile.dy < 2 * size -3; tile.dy++){
        printf("─");
    }
    printf("┘\n");

    printf("     ");
    for(int x = 1; x <= config->board_size - 1; x ++ ){
        printf("  %2d", x);
    }
    printf(RESET "\n");

}

void print_state(Game_Config* config, Game_State* state){

    printf("  turn : [%d]\n", state->turn + 1);
    if(state->players[state->turn % config->player_count].blocked_turn_left > 0){
        printf("  %s is blocked !\a\nblocked turn left: %d\n", state->players[state->turn % config->player_count].name, state->players[state->turn % config->player_count].blocked_turn_left - 1 );
    }
    else{
    printf( BRIGHT_MAGENTA "  %s" RESET "'s turn: \n" RESET, state->players[state->turn % config->player_count].name );
    }
    printf("  walls left: %d\n", state->players[state->turn % config->player_count].walls_left);

}


void print_game_turn(Game_Config* config, Game_State* state, Turn_State *turn_state){

    print_state(config, state);
    print_ui_board(config, state, turn_state);

}

