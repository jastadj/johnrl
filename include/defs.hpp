#ifndef _DEFS
#define _DEFS

#define MAPWIDTH 160
#define MAPHEIGHT 50

enum ASCII_COLORS{COLOR_BLACK, COLOR_WHITE, COLOR_B_WHITE, COLOR_RED, COLOR_B_RED, COLOR_BLUE,
                   COLOR_B_BLUE, COLOR_GREEN, COLOR_B_GREEN, COLOR_CYAN, COLOR_B_CYAN, COLOR_MAGENTA,
                   COLOR_B_MAGENTA, COLOR_YELLOW, COLOR_B_YELLOW, COLOR_TOTAL};

enum _GAMEOBJTYPES{OBJ_NONE, OBJ_MAPTILE, OBJ_PLAYER, OBJ_MONSTER, OBJ_ITEM_CONTAINER, OBJ_ITEM_CONTAINER_LIQUID,
                    OBJ_TOTAL};

enum _DIRECTIONS{DIR_NONE, DIR_SW, DIR_SOUTH, DIR_SE, DIR_WEST, DIR_SELF, DIR_EAST, DIR_NW, DIR_NORTH, DIR_NE, DIR_TOTAL};


#endif // _DEFS
