#ifndef CLASS_SALVAGER
#define CLASS_SALVAGER

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>

#include <curses.h>

#include "colors.hpp"

#include "player.hpp"
#include "map.hpp"
#include "maptile.hpp"
#include "item.hpp"
#include "camera.hpp"
#include "mob.hpp"


//debug on = 1, off = 0
#define DEBUG 1
#define DEBUG_DAYCYCLE 1
#define DEBUG_FOV_OFF 0


const int ACTIVE_MAPS = 3;
const int HDELAY = 1;

enum {SOUTHWEST, SOUTH, SOUTHEAST, WEST, NODIR, EAST, NORTHWEST, NORTH, NORTHEAST};


class Salvager
{
private:

    //init
    void initCurses();
    void initPlayer();
    void initCamera();
    void initMap();
    void initMapTiles();
    void initItems();
    void initSeed();
    void initMobs();

    //game objects
    Camera *mCamera;
    Player *mPlayer;
    std::vector< std::vector< Map* > > mActiveMaps;
    std::vector< MapTile > mMapTiles;
    std::vector< Item > mItems;
    std::vector< Mob > mMobs;

    //modes
    void newGame();
    void clearGame();
    void mainLoop();
    void saveGame();
    void shutdown();

    //drawing
    void drawPlayer();
    void drawMap(); // draw active maps within camera
    void drawTile(int x, int y, int tile, bool vis = true);
    void drawMapItems();
    void drawItem(int x, int y, ItemRef *target, bool vis = true);
    void drawMapMobs();
    void drawMob(int x, int y, MobRef *target, bool vis = true);

    //player functions
    void movePlayer(int dir);
    void playerGet();
    void playerDrop();
    bool playerDrink();

    //mob functions
    void moveMob(Map *tmap, MobRef *target, int dir);

    //map functions
    void getActiveMaps(int x, int y); // use center point x,y to create a new array of active maps around point
    bool validTile(Map *target, int x, int y);
    Map *getActiveMapAt(int gx, int gy);

    //engine
    int mSeed;
    int handleInput(int ch);
    void endTurn();
    void mobTurn();
    int getDaylightRadius();
    bool inFov(int gx1, int gy1, int x1, int y1, int gx2, int gy2, int x2, int y2);
    bool inPlayerFov(int gx, int gy, int x, int y);



    //debug
    void debug();
    void debug_time();
    void debug_resetActiveMaps();


public:
    Salvager();

    void start();

};
#endif // CLASS_SALVAGER
