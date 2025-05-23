#include "input.h"

int handle_user_input(){

    if(!_kbhit()) return INVALID_VALUE;

    int key = _getch();
    if(key == 0xE0 || key == 0) key = _getch();
    switch(key) {
        case UP:
            return UP;
        case DOWN:
            return DOWN;
        case LEFT:
            return LEFT;
        case RIGHT:
            return RIGHT;
        case NUM_2:
            return NUM_2;
        case NUM_4:
            return NUM_4;
        case NUM_5:
            return NUM_5;
        case NUM_6:
            return NUM_6;
        case NUM_8:
            return NUM_8;
        case ENTER:
            return ENTER;
        case ESC:
            return ESC;
        default:
            return INVALID_VALUE;
    }

}

KeyCategory categorize_key(int key) {

    switch(key) {
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
            return KEY_CATEGORY_ARROW;

        case NUM_2:
        case NUM_4:
        case NUM_5:
        case NUM_6:
        case NUM_8:
            return KEY_CATEGORY_NUM;

        case ENTER:
            return KEY_CATEGORY_ENTER;

        case ESC:
            return KEY_CATEGORY_ESC;

        default:
            return KEY_CATEGORY_OTHER;
    }

}
