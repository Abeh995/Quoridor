#include "game.h"

int main() {
	
	initialize_ui();

    Game_Config config = {
            .board_size = 9,
            .walls_per_player = 10,
            .player_count = 2,
            .ai_count = 0,
            .ai_difficulty = 1,
            .magic_box = false
    };
    Game_State state;

    if ( handle_main_menu(&config, &state)) {
        start_game(&config, &state);
        cleanup(&config, &state);
    }
	
	return 0;
}