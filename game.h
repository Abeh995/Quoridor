#ifndef QUORIDOR_GAME_H
#define QUORIDOR_GAME_H

#include "config.h"
#include "ui.h"
#include "ai.h"
#include "logic.h"

#include <conio.h>
#include <stdio.h>
#include <windows.h>

void start_game(Game_Config *config, Game_State *state);
void handle_human_turn(Game_Config *config, Game_State *state);

#endif //QUORIDOR_GAME_H
