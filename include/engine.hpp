#ifndef CLASS_ENGINE
#define CLASS_ENGINE

#include <SFML/Graphics.hpp>
#include <vector>

class Engine
{
private:

    //screen elements
    sf::RenderWindow *m_Screen;

    //init
    bool initScreen();
    bool initTileArt();

    //resources
    int m_TileWidth;
    int m_TileHeight;
    std::vector< std::vector< sf::Texture> > m_TileTextures;
    std::vector <std::vector< std::vector< sf::Sprite> > > m_TileSprites;

    //loops
    void mainLoop();

    //tools
    void replaceImageColor(sf::Image *timage, sf::Color scolor, sf::Color dcolor);

public:
    Engine();
    ~Engine();

    void start();

};

#endif // CLASS_ENGINE
