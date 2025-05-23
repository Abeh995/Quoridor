#include "ai.h"

void handle_ai_turn(Game_Config* config, Game_State* state){

    Turn_State turn_state = {
            .current_state = IDLE, // default state
            .move_hover_y = INVALID_VALUE,
            .move_hover_x = INVALID_VALUE,
            .is_move_valid = false,

            .wall_type = HORIZONTAL, // default wall type
            .wall_hover_y = INVALID_VALUE,
            .wall_hover_x = INVALID_VALUE,
    };

}
