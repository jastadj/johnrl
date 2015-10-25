#ifndef CLASS_ENGINE
#define CLASS_ENGINE

#include <SFML/Graphics.hpp>
#include <vector>

#include "defs.hpp"
#include "tools.hpp"
#include "gameobj.hpp"
#include "map.hpp"
#include "player.hpp"
#include "monster.hpp"
#include "itemtypes.hpp"

class Engine
{
private:

    //singleton
    Engine();
    static Engine *onlyinstance;


    //screen elements
    sf::RenderWindow *m_Screen;
    int m_FrameRateLimit;
    std::vector<sf::Color> m_AsciiColors;
    int m_TermCurrentFGColor;
    int m_TermCurrentBGColor;
    sf::Vector2f m_TermCurrentCursorPos;

    //viewport
    sf::IntRect m_Viewport;
    sf::Vector2i m_ViewportPosition;

    bool posInViewport(int x, int y);
    bool posInViewport(sf::Vector2i pos);
    void centerViewport(int x, int y);
    void centerViewport(sf::Vector2i pos) { centerViewport(pos.x, pos.y);}


    //init
    bool initScreen();
    bool initTileArt();
    bool initMapTiles();
    bool initMonsters();
    bool initItems();
    bool initMap();
    bool initPlayer();
    bool newGame();

    //resources
    int m_TileWidth;
    int m_TileHeight;
    int m_TileSheetWidth;
    int m_TileSheetHeight;
    int m_ScreenTilesWidth;
    int m_ScreenTilesHeight;
    std::vector< std::vector< sf::Texture> > m_TileTextures;
    std::vector <std::vector< std::vector< sf::Sprite> > > m_TileSprites;
    std::vector< MapTile* > m_MapTiles;
    MapTile *getMapTile(int tilenum);
    std::vector < Monster* > m_MonsterDB;
    std::vector < Item* > m_ItemDB;

    //game objects
    long m_Seed;
    Player *m_Player;
    MapChunk *testmap;

    //loops
    void mainLoop();
    void showInventory();

    //draw
    void drawTile(int x, int y, int tilenum, int fgcolor = 1, int bgcolor = 0);
    void drawTile(int x, int y, char ch, int fgcolor = 1, int bgcolor = 0);
    void drawTileInViewport(int x, int y, int tilenum, int fgcolor = 1, int bgcolor = 0);
    //void drawTileInViewport(int x, int y, char ch, int fgcolor = 1, int bgcolor = 0);
    void drawString(int x, int y, std::string tstring, int fgcolor = 1, int bgcolor = 0);
    void drawPlayer();
    void drawMap();
    void drawMonsters();
    void drawItems();
    void drawStatus();

public:
    ~Engine();

    static Engine *getInstance()
    {
        if(onlyinstance == NULL) onlyinstance = new Engine;
        return onlyinstance;
    }

    void start();

    int getMonsterDBSize() { return int(m_MonsterDB.size()); }
    Monster *createMonster(int monsterid);

    int getItemDBSize() { return int(m_ItemDB.size()); }
    Item *createItem(int itemid);

};

#endif // CLASS_ENGINE
