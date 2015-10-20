#include "engine.hpp"

//debug
#include <iostream>
#include <string>


Engine::Engine()
{

    //default initialization
    m_TileWidth = 8;
    m_TileHeight = 12;
    m_ScreenTilesWidth = 80;
    m_ScreenTilesHeight = 25;

}

Engine::~Engine()
{

}

void Engine::start()
{
    //init screen
    initScreen();

    //init tile art
    initTileArt();

    //start mainloop
    mainLoop();

}

bool Engine::initScreen()
{
    //create render window
    m_Screen = new sf::RenderWindow(sf::VideoMode(m_ScreenTilesWidth*m_TileWidth, m_ScreenTilesHeight*m_TileHeight,32), "Test");

    //create colors
    m_AsciiColors.push_back(sf::Color(0x00, 0x00, 0x00)); // black
    m_AsciiColors.push_back(sf::Color(0xff, 0xff, 0xff)); // white
    m_AsciiColors.push_back(sf::Color(0xff, 0xff, 0xff)); // bright white
    m_AsciiColors.push_back(sf::Color(0xff, 0x00, 0x00)); // red
    m_AsciiColors.push_back(sf::Color(0xff, 0x00, 0x00)); // bright red
    m_AsciiColors.push_back(sf::Color(0x00, 0x00, 0xff)); // blue
    m_AsciiColors.push_back(sf::Color(0x00, 0x00, 0xff)); // bright blue
    m_AsciiColors.push_back(sf::Color(0x00, 0xff, 0x00)); // green
    m_AsciiColors.push_back(sf::Color(0x00, 0xff, 0x00)); // bright green
    m_AsciiColors.push_back(sf::Color(0x00, 0xff, 0xff)); // cyan
    m_AsciiColors.push_back(sf::Color(0x00, 0xff, 0xff)); // bright cyan
    m_AsciiColors.push_back(sf::Color(0xff, 0x00, 0xff)); // magenta
    m_AsciiColors.push_back(sf::Color(0xff, 0x00, 0xff)); // bright magenta
    m_AsciiColors.push_back(sf::Color(0xff, 0xff, 0x00)); // yellow
    m_AsciiColors.push_back(sf::Color(0xff, 0xff, 0x00)); // bright yellow

    return true;
}

bool Engine::initTileArt()
{
    std::cout << "Generating tile sheets...\n";
    //create texture for each color combination
    for(int i = 0; i < COLOR_TOTAL; i++)
    {
        //add column
        m_TileTextures.resize(m_TileTextures.size()+1);

        for(int n = 0; n < COLOR_TOTAL; n++)
        {
            sf::Image newimage;
            newimage.loadFromFile("tileart.png");
        }
    }


    return true;
}

void Engine::mainLoop()
{
    bool quit = false;

    //test sprite
    sf::Sprite testsprite(m_TileTextures[0][0]);

    //frame loop
    while(!quit)
    {
        //create event que
        sf::Event event;

        //clear screen
        m_Screen->clear();

        //handle events
        while(m_Screen->pollEvent(event))
        {
            if(event.type == sf::Event::Closed) quit = true;
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) quit = true;
            }
        }

        //draw
        m_Screen->draw(testsprite);

        //update and display screen
        m_Screen->display();

    }
}







////////////////////////////////////////////////////////////////////////////////////////
//

void Engine::replaceImageColor(sf::Image *timage, sf::Color scolor, sf::Color dcolor)
{
    int x = timage->getSize().x;
    int y = timage->getSize().y;

    for(int i = 0; i < y; i++)
    {
        for(int n = 0; n < x; n++)
        {
            if(timage->getPixel(n,i) == scolor) timage->setPixel(n,i, dcolor);
        }
    }
}
