#include "engine.hpp"

//debug
#include <iostream>
#include <string>


Engine::Engine()
{

    //default initialization
    m_TileWidth = 8;
    m_TileHeight = 12;

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
    m_Screen = new sf::RenderWindow(sf::VideoMode(800,600,32), "Test");

    return true;
}

bool Engine::initTileArt()
{
    //load tile sheet

    sf::Image tempimg;
    tempimg.loadFromFile("tileart.png");

    //replace color
    replaceImageColor(&tempimg, sf::Color(0xff, 0x00, 0xff), sf::Color(255,0,0));

    sf::Texture temptexture;
    temptexture.loadFromImage(tempimg);

    m_TileTextures.resize(1);
    m_TileTextures[0].resize(1);
    m_TileTextures[0][0] = temptexture;


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
