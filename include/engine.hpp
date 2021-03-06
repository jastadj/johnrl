#ifndef CLASS_ENGINE
#define CLASS_ENGINE

#include <SFML/Graphics.hpp>
#include <vector>

#include "sfmlcurs.hpp"
#include "simplexnoise.h"
#include "defs.hpp"
#include "tools.hpp"
#include "gameobj.hpp"
#include "map.hpp"
#include "player.hpp"
#include "monster.hpp"
#include "itemtypes.hpp"
#include "message.hpp"

struct consolecmd
{
    std::string cmd;
    std::string helptxt;
    consolecmd *parent;
};

class Engine
{
private:

    //singleton
    Engine();
    static Engine *onlyinstance;


    //screen elements
    sf::RenderWindow *m_Screen;
    SFMLCurs *m_Curses;
    int m_ScreenTilesWidth;
    int m_ScreenTilesHeight;
    int m_FrameRateLimit;

    //viewport
    sf::IntRect m_Viewport;
    sf::Vector2i m_ViewportPosition;

    bool posInViewport(int x, int y);
    bool posInViewport(sf::Vector2i pos);
    void centerViewport(int x, int y);
    void centerViewport(sf::Vector2i pos) { centerViewport(pos.x, pos.y);}


    //init
    bool initScreen();
    bool initCurses();
    bool initMapTiles();
    bool initMonsters();
    bool initItems();
    bool initLiquids();
    bool initMap();
    bool initPlayer();
    bool newGame(long nseed = time(NULL) );

    //resources
    std::vector< MapTile* > m_MapTiles;
    MapTile *getMapTile(int tilenum);
    std::vector < Monster* > m_MonsterDB;
    std::vector < Item* > m_ItemDB;
    std::vector < Liquid*> m_Liquids;



    //game objects
    long m_Seed;
    MessageManager *m_MessageManager;
    Player *m_Player;
    std::vector< MapChunk*> m_Maps;
    MapChunk *m_CurrentMap;


    //player actions
    void playerDeath();
    void showInventory();
    static std::vector<int> m_ItemFilterAll;
    Item *selectItemFromInventory(std::vector<Item*> *source,std::string promptstr = "Select Item:",
                                  std::vector<int> itemfilter = m_ItemFilterAll);
    std::vector<Item*> selectMultipleItemsFromInventory(std::vector<Item*> *source, std::string promptstr = "Select Item:",
                                  std::vector<int> itemfilter = m_ItemFilterAll);
    void dropItemUI();
    void pickupItemFromTileUI(int x, int y);
    void pickupItemFromTileUI(sf::Vector2i tpos);
    bool fillLiquidContainer();

    //loops
    void mainLoop();


    //draw
    void drawGame();
    void drawTile(int x, int y, int tilenum, int fgcolor = 1, int bgcolor = 0);
    void drawTile(int x, int y, char ch, int fgcolor = 1, int bgcolor = 0);
    void drawTileInViewport(int x, int y, int tilenum, int fgcolor = 1, int bgcolor = 0);
    //void drawTileInViewport(int x, int y, char ch, int fgcolor = 1, int bgcolor = 0);
    void drawString(int x, int y, std::string tstring, int fgcolor = 1, int bgcolor = 0);
    void drawWindow(int x, int y, int width, int height,int fgcolor = COLOR_WHITE, int bgcolor = COLOR_BLACK,
                     int tl = 218, int hor = 196, int tr = 191, int vert = 179, int bl = 192, int br = 217, int filltile = 0);
    void drawPlayer();
    void drawMap();
    void drawMonsters();
    void drawItems();
    void drawStatus();
    void drawMessageQue();
    bool inFOV(int sx, int sy, int tx, int ty);

public:
    ~Engine();

    static Engine *getInstance()
    {
        if(onlyinstance == NULL) onlyinstance = new Engine;
        return onlyinstance;
    }

    void start();

    sf::RenderWindow *getScreen() { return m_Screen;}

    long getSeed() { return m_Seed;}

    void playerTurnUpdates();
    bool walkInDir(Actor *tactor, int direction);
    int getMonsterDBSize() { return int(m_MonsterDB.size()); }
    Monster *createMonster(int monsterid);

    int getItemDBSize() { return int(m_ItemDB.size()); }
    Item *createItem(int itemid);
    bool moveItem(Item *titem, std::vector<Item*> *isource, std::vector<Item*> *idest);

    bool validWalkableTile(MapChunk *tmap, int x, int y);
    int getDirectionFromUser(sf::Vector2i *mcoord = NULL);

    sf::Vector2i getGlobalPosition() { return m_Player->getGlobalPos();}

    //noise
    sf::Vector2i getNoiseRelPosition0() { return m_Player->getNoisePosRel0();}
    std::vector< std::vector<int> > genNoise(int width, int height, int xoffset = 0, int yoffset = 0,
                                             float persistence = 0.7, float octaves = 6, float scale = 9,
                                             int minval = 0, int maxval = 255);


    //debug stuff
    void debugtest();
    void noisetest();
    sf::Thread *console_thread;
    void console(); //see console.cpp
    std::vector<consolecmd*> cCommands;
    void parse(std::string ccmd); // see console.cpp
};

#endif // CLASS_ENGINE
