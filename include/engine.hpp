#ifndef CLASS_ENGINE
#define CLASS_ENGINE

#include <SFML/Graphics.hpp>
#include "defs.hpp"
#include "tools.hpp"
#include <vector>

class Engine
{
private:

    //screen elements
    sf::RenderWindow *m_Screen;
    std::vector<sf::Color> m_AsciiColors;

    //init
    bool initScreen();
    bool initTileArt();

    //resources
    int m_TileWidth;
    int m_TileHeight;
    int m_TileSheetWidth;
    int m_TileSheetHeight;
    int m_ScreenTilesWidth;
    int m_ScreenTilesHeight;
    std::vector< std::vector< sf::Texture> > m_TileTextures;
    std::vector <std::vector< std::vector< sf::Sprite> > > m_TileSprites;

    //loops
    void mainLoop();

public:
    Engine();
    ~Engine();

    void start();

};

#endif // CLASS_ENGINE
