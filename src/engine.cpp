#include "engine.hpp"

//debug
#include <iostream>
#include <string>

Engine *Engine::onlyinstance = NULL;

Engine::Engine()
{

    //default initialization
    m_TileWidth = 8;
    m_TileHeight = 12;
    m_TileSheetWidth = 16;
    m_TileSheetHeight = 16;
    m_ScreenTilesWidth = 80;
    m_ScreenTilesHeight = 25;
    m_TermCurrentBGColor = COLOR_BLACK;
    m_TermCurrentFGColor = COLOR_WHITE;
}

Engine::~Engine()
{

}

void Engine::start()
{
    //init screen
    std::cout << "Initializing screen...";
    if(initScreen()) std::cout << "done.\n";
    else std::cout << "failed.\n";

    //init tile art
    std::cout << "Initializing tile sprites...";
    if(initTileArt()) std::cout << "done.\n";
    else std::cout << "failed.\n";

    //start mainloop
    std::cout << "Starting main loop...\n";
    mainLoop();

}

bool Engine::initScreen()
{
    //create render window
    m_Screen = new sf::RenderWindow(sf::VideoMode(m_ScreenTilesWidth*m_TileWidth, m_ScreenTilesHeight*m_TileHeight,32), "Test");
    m_Screen->clear();
    m_Screen->display();

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
    //color mask for foreground and background
    sf::Color colormaskbg(0xff,0x00,0xff);
    sf::Color colormaskfg(0xff,0xff,0xff);

    //create texture for each color combination
    //background color loop
    for(int i = 0; i < COLOR_TOTAL; i++)
    {
        //add column
        m_TileTextures.resize(m_TileTextures.size()+1);

        //foreground color loop
        for(int n = 0; n < COLOR_TOTAL; n++)
        {
            //texture for image
            sf::Texture newtxt;

            //create temporary image file
            sf::Image newimage;
            newimage.loadFromFile("tileart.png");

            //set foreground color
            replaceImageColor(&newimage, colormaskfg, m_AsciiColors[n]);

            //set background color
            replaceImageColor(&newimage, colormaskbg, m_AsciiColors[i]);

            //set texture from image
            newtxt.loadFromImage(newimage);

            //debug
            //sf::Sprite testsprite(newtxt);
            //m_Screen->draw(testsprite);
            //m_Screen->display();

            m_TileTextures[i].push_back(newtxt);
        }
    }

    //clip all the characters for each character type from bg/fg combos
    for(int i = 0; i < m_TileSheetWidth*m_TileSheetHeight; i++)
    {
        //add new character index
        m_TileSprites.resize( m_TileSprites.size()+1);

        //for each character, go through each color combination and clip to a sprite
        //bg color loop
        for(int n = 0; n < COLOR_TOTAL; n++)
        {
            //add new background index
            m_TileSprites[i].resize( m_TileSprites[i].size()+1);

            //fg color loop
            for(int p = 0; p < COLOR_TOTAL; p++)
            {
                sf::IntRect clip;

                clip.width = m_TileWidth;
                clip.height = m_TileHeight;
                clip.left = (i - ( (i/m_TileSheetWidth) * m_TileSheetWidth ) ) * m_TileWidth;
                clip.top = (i/m_TileSheetWidth) * m_TileHeight;

                sf::Sprite newsprite(m_TileTextures[n][p], clip);

                //debug
                //m_Screen->draw(newsprite);
                //m_Screen->display();

                m_TileSprites[i][n].push_back(newsprite);
            }
        }
    }

    return true;
}

bool Engine::initMapTiles()
{
    MapTile newtile;


    newtile.m_Name = "floor";
    newtile.m_TileID = int('.');

    m_MapTiles.push_back(newtile);
}

void Engine::mainLoop()
{
    bool quit = false;

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
                else if(event.key.code == sf::Keyboard::Left)
                {

                }
                else if(event.key.code == sf::Keyboard::Right)
                {

                }
            }
        }

        //draw


        //update and display screen
        m_Screen->display();

    }
}

/////////////////////////////////////////////////////////////////////////////////
//  DRAW
void Engine::drawTile(int x, int y, int tilenum, int fgcolor, int bgcolor)
{
    //assuming color black = 0, dont do anything
    if(fgcolor == 0 && bgcolor == 0) return;

    //check that color and tile indices are in range
    if(fgcolor < 0 || bgcolor < 0 || fgcolor >= COLOR_TOTAL || bgcolor >= COLOR_TOTAL)
    {
        std::cout << "Error drawing tile, color index out of range : bg=" << bgcolor << " , fg=" << fgcolor << std::endl;
        return;
    }
    else if(tilenum < 0 || tilenum >= int(m_TileSprites.size()) )
    {
        std::cout << "Error drawing tile, sprite index out of range : " << tilenum << std::endl;
        return;
    }

    m_TileSprites[tilenum][bgcolor][fgcolor].setPosition(x*m_TileWidth, y*m_TileHeight);
    m_Screen->draw(m_TileSprites[tilenum][bgcolor][fgcolor]);
}

void Engine::drawTile(int x, int y, char ch, int fgcolor, int bgcolor)
{
    drawTile(x, y, int(ch), fgcolor, bgcolor);
}

void Engine::drawString(int x, int y, std::string tstring, int fgcolor, int bgcolor)
{
    sf::Vector2i cursorpos = sf::Vector2i(x,y);

    for(int i = 0; i < int(tstring.length()); i++)
    {
        drawTile(cursorpos.x, cursorpos.y, tstring.c_str()[i], fgcolor, bgcolor);
        cursorpos.x++;
    }
}