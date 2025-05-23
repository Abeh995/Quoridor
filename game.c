#include "game.h"

void start_game(Game_Config *config, Game_State *state){

    while( !state->is_the_match_over ){

        int turn = state->turn % config->player_count;
        if( state->players[turn].is_ai ){
            handle_ai_turn(config, state);
        }
        else{
            handle_human_turn(config,state);
        }
//        check_winner(config, state);

    }

}

void handle_human_turn(Game_Config *config, Game_State *state){

    Turn_State turn_state = {
            .current_state = IDLE,
            .move_hover_y = INVALID_VALUE,
            .move_hover_x = INVALID_VALUE,
            .is_move_valid = false,

            .wall_type = HORIZONTAL, // default wall type
            .wall_hover_y = INVALID_VALUE,
            .wall_hover_x = INVALID_VALUE,
    };

    while(1){

        clear();
        print_game_turn(config, state, &turn_state);

        int key = handle_user_input();
        KeyCategory key_category = categorize_key(key);

        switch (key_category) {

            case KEY_CATEGORY_ARROW:

                turn_state.current_state = MOVE;
                validate_move(config, state, &turn_state, key);
                break;

            case KEY_CATEGORY_NUM:

                turn_state.current_state = WALL_PLACEMENT;
                set_wall_cursor(config, state, &turn_state, key);
                break;

            case KEY_CATEGORY_ENTER:

                // confirm action
                if(turn_state.current_state == IDLE){
                    break;
                }
                if(turn_state.current_state == WALL_PLACEMENT){
                    place_wall(config, state, &turn_state);
                    state->turn++;
                    return;
                }
                else {
                    if(turn_state.is_move_valid){
                        move_pawn(config, state, &turn_state);
                        state->turn++;
                        return;
                    }
                    else{
                        // didn't choose valid move yet
                    }
                }
                break;

            case KEY_CATEGORY_ESC:

                // pause menu
                break;

            case KEY_CATEGORY_OTHER:

                break;
        }

        Sleep(60);
    }

}
