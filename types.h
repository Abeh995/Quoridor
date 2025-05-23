#ifndef QUORIDOR_TYPES_H
#define QUORIDOR_TYPES_H

#include <stdbool.h>

#define BLINK_RATE_MS 300
#define MIN_BOARD_SIZE 5
#define MAX_BOARD_SIZE 15
#define ACTUAL_BOARD_SIZE(n) (2 * (n) + 1)
#define EMPTY_CELL ' '
#define DISPLAY_WALL '*'
#define FIRST_CELL 1
#define MID_CELL(ACTUAL_BOARD_SIZE) (ACTUAL_BOARD_SIZE / 2)
#define LAST_CELL(ACTUAL_BOARD_SIZE) (ACTUAL_BOARD_SIZE - 2)
#define BOARD_WALLS_CAPACITY(n) ((n - 1) * (n - 1))
#define PLAYERS_PLACED_WALL (-2)
#define BORDER_WALL (-1)
#define READY_TO_PLACE_WALL 0
#define MIN_WALLS_PER_PLAYER 4
#define MAX_WALLS_PER_PLAYER 20
#define MAX_NAME_LENGTH 21
#define MIN_AI_COUNT 0
#define TWO_PLAYER_MAX_AI_COUNT 1
#define FOUR_PLAYER_MAX_AI_COUNT 3
#define MAX_PLAYER 4
#define MIN_PLAYER 2
#define TWO_PLAYER_GAME 2
#define FOUR_PLAYER_GAME 4
#define MIN_AI_DIFFICULTY 1
#define MAX_AI_DIFFICULTY 3
#define PLAYER_1 0
#define PLAYER_2 1
#define PLAYER_3 2
#define PLAYER_4 3
#define NO_CHECKED 0
#define UP_CHECKED 1
#define DOWN_CHECKED 2
#define LEFT_CHECKED 3
#define RIGHT_CHECKED 4
#define INVALID_VALUE (-1)
#define DEFAULT_SELECTION 0

typedef enum {
    MENU_NEW_GAME = 0,
    MENU_LOAD_GAME = 1,
    MENU_OPTIONS = 2,
    MENU_QUIT = 3
} MainMenuItem;

typedef struct{
    int dx;
    int dy;
}Position;

typedef enum{
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    ENTER = 13,
    BACKSPACE = 8,
    ESC = 27,
    NUM_2 = 0x32,
    NUM_4 = 0x34,
    NUM_5 = 0x35,
    NUM_6 = 0x36,
    NUM_8 = 0x38
}Keys;

typedef enum {
    KEY_CATEGORY_ARROW,
    KEY_CATEGORY_NUM,
    KEY_CATEGORY_ENTER,
    KEY_CATEGORY_ESC,
    KEY_CATEGORY_OTHER
} KeyCategory;

typedef enum{
    MENU_BOARD_SIZE = 0,
    MENU_WALLS_PER_PLAYER = 1,
    MENU_PLAYERS_COUNT = 2,
    MENU_AI_COUNT = 3,
    MENU_AI_DIFFICULTY = 4
}SetupMenuItem;

typedef enum{
    IDLE,
    MOVE,
    WALL_PLACEMENT
} Input_State;

typedef enum{
    HORIZONTAL,
    VERTICAL
} Wall_Type;

typedef struct{
    Input_State current_state;
    Wall_Type wall_type;
    int wall_hover_y;
    int wall_hover_x;

    int move_hover_y;
    int move_hover_x;
    bool is_move_valid;
}Turn_State;

typedef struct {
    int board_size;
    int walls_per_player;
    int player_count;
    int ai_count;
    int ai_difficulty; // 1 :easy 2: normal 3:hard
    bool magic_box;
} Game_Config;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int x, y;
    int walls_left;
    int blocked_turn_left;
    int move_count;
    int target_row;
    bool is_ai;
} player;

typedef struct {
    unsigned char ** ui_board;
    int ** wall_grid;
    int ** temp_wall_grid;
    int size; // actual_board_size
} Game_Boards;

typedef struct{
    Game_Boards board;
    player players[4];
    int turn;
    int placed_walls_count;
    int last_magic_box_turn;
    bool is_the_match_over;
} Game_State;

//foreground
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define RESET   "\033[0m"

#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

// Background
#define BG_RESET   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"

//font
#define F_RESET     "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define ITALIC      "\033[3m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"
#define HIDDEN      "\033[8m"

#define NUMBER_COLOR    BRIGHT_WHITE
#define BRACKET_COLOR BRIGHT_CYAN
#define OPTION_COLOR BRIGHT_MAGENTA
#define CURSOR_COLOR BRIGHT_GREEN
#define WALL_COLOR CYAN
#define WALL_FONT  BOLD
//#define AI_COLOR

#endif //QUORIDOR_TYPES_H
