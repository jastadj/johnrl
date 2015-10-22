#ifndef CLASS_ENGINE
#define CLASS_ENGINE

#include <SFML/Graphics.hpp>
#include <vector>

#include "defs.hpp"
#include "tools.hpp"
#include "gameobj.hpp"
#include "map.hpp"


class Engine
{
private:

    //singleton
    Engine();
    static Engine *onlyinstance;


    //screen elements
    sf::RenderWindow *m_Screen;
    std::vector<sf::Color> m_AsciiColors;
    int m_TermCurrentFGColor;
    int m_TermCurrentBGColor;
    sf::Vector2f m_TermCurrentCursorPos;

    //init
    bool initScreen();
    bool initTileArt();
    bool initMapTiles();

    //resources
    int m_TileWidth;
    int m_TileHeight;
    int m_TileSheetWidth;
    int m_TileSheetHeight;
    int m_ScreenTilesWidth;
    int m_ScreenTilesHeight;
    std::vector< std::vector< sf::Texture> > m_TileTextures;
    std::vector <std::vector< std::vector< sf::Sprite> > > m_TileSprites;
    std::vector< MapTile > m_MapTiles;

    //loops
    void mainLoop();

    //draw
    void drawTile(int x, int y, int tilenum, int fgcolor = 1, int bgcolor = 0);
    void drawTile(int x, int y, char ch, int fgcolor = 1, int bgcolor = 0);


public:
    ~Engine();

    static Engine *getInstance()
    {
        if(onlyinstance == NULL) onlyinstance = new Engine;
        return onlyinstance;
    }

    void start();

};

#endif // CLASS_ENGINE
