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
#include "message.hpp"

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
    bool initLiquids();
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
    std::vector < Liquid*> m_Liquids;

    //game objects
    long m_Seed;
    MessageManager *m_MessageManager;
    Player *m_Player;

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
    void drawPlayer();
    void drawMap();
    void drawMonsters();
    void drawItems();
    void drawStatus();
    void drawMessageQue();

public:
    ~Engine();

    static Engine *getInstance()
    {
        if(onlyinstance == NULL) onlyinstance = new Engine;
        return onlyinstance;
    }

    void start();

    long getSeed() { return m_Seed;}

    void playerTurnUpdates();

    int getMonsterDBSize() { return int(m_MonsterDB.size()); }
    Monster *createMonster(int monsterid);

    int getItemDBSize() { return int(m_ItemDB.size()); }
    Item *createItem(int itemid);
    bool moveItem(Item *titem, std::vector<Item*> *isource, std::vector<Item*> *idest);

    MapChunk *testmap;
    bool validWalkableTile(int x, int y);
    int getDirectionFromUser(sf::Vector2i *mcoord = NULL);

};

#endif // CLASS_ENGINE
