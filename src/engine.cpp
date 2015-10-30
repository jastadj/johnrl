#include "engine.hpp"

//debug
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

//statics
Engine *Engine::onlyinstance = NULL;
std::vector<int> Engine::m_ItemFilterAll;

Engine::Engine()
{

    //init pointers to null
    m_Player = NULL;
    testmap = NULL;
    m_MessageManager = NULL;

    //default initialization
    m_FrameRateLimit = 30;
    m_TileWidth = 8;
    m_TileHeight = 12;
    m_TileSheetWidth = 16;
    m_TileSheetHeight = 16;
    m_ScreenTilesWidth = 80;
    m_ScreenTilesHeight = 25;
    m_TermCurrentBGColor = COLOR_BLACK;
    m_TermCurrentFGColor = COLOR_WHITE;

    m_Viewport.width = 41;
    m_Viewport.height = 25;
    m_ViewportPosition = sf::Vector2i(0,0);

    m_ItemFilterAll.push_back(OBJ_TOTAL);

    //set seed
    m_Seed = long(time(NULL));
    srand(m_Seed);
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

    std::cout << "Initializing liquids...";
    if(initLiquids()) std::cout << "done.\n";
    else std::cout << "failed.\n";

    std::cout << "Initializing map tiles...";
    if(initMapTiles()) std::cout << "done.\n";
    else std::cout << "failed.\n";

    std::cout << "Initializing monster database list...";
    if(initMonsters()) std::cout << "done.\n";
    else std::cout << "failed.\n";

    std::cout << "Initializing item database list...";
    if(initItems()) std::cout << "done.\n";
    else std::cout << "failed.\n";

    std::cout << "Starting new game.\n";
    newGame();

    //start mainloop
    std::cout << "Starting main loop...\n";
    mainLoop();

    //if player died...
    if(!m_Player->isAlive()) playerDeath();

}

void Engine::playerDeath()
{
    bool quit = false;

    while(!quit)
    {
        sf::Event event;

        m_Screen->clear();

        while(m_Screen->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) quit = true;
            }
        }

        drawString(0,0, "You are dead!");

        m_Screen->display();
    }
}

bool Engine::initScreen()
{
    //create render window
    m_Screen = new sf::RenderWindow(sf::VideoMode(m_ScreenTilesWidth*m_TileWidth, m_ScreenTilesHeight*m_TileHeight,32), "Test");
    m_Screen->setFramerateLimit(m_FrameRateLimit);
    m_Screen->clear();
    m_Screen->display();

    //create colors
    m_AsciiColors.push_back(sf::Color(0x00, 0x00, 0x00)); // black
    m_AsciiColors.push_back(sf::Color(0xc0, 0xc0, 0xc0)); // white
    m_AsciiColors.push_back(sf::Color(0xff, 0xff, 0xff)); // bright white
    m_AsciiColors.push_back(sf::Color(0x80, 0x00, 0x00)); // red
    m_AsciiColors.push_back(sf::Color(0xff, 0x00, 0x00)); // bright red
    m_AsciiColors.push_back(sf::Color(0x00, 0x00, 0x80)); // blue
    m_AsciiColors.push_back(sf::Color(0x00, 0x00, 0xff)); // bright blue
    m_AsciiColors.push_back(sf::Color(0x00, 0x80, 0x00)); // green
    m_AsciiColors.push_back(sf::Color(0x00, 0xff, 0x00)); // bright green
    m_AsciiColors.push_back(sf::Color(0x00, 0x80, 0x80)); // cyan
    m_AsciiColors.push_back(sf::Color(0x00, 0xff, 0xff)); // bright cyan
    m_AsciiColors.push_back(sf::Color(0x80, 0x00, 0x80)); // magenta
    m_AsciiColors.push_back(sf::Color(0xff, 0x00, 0xff)); // bright magenta
    m_AsciiColors.push_back(sf::Color(0x80, 0x80, 0x00)); // yellow
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
    //note : the first tile should always be a black/black/blank tile as empty space

    MapTile *newtile = new MapTile;

    //tile 0
    newtile->m_Name = "empty space";
    newtile->m_TileID = 0;
    newtile->m_FGColor = COLOR_BLACK;
    newtile->m_BGColor = COLOR_BLACK;
    m_MapTiles.push_back(newtile);

    //tile 1
    newtile = new MapTile;
    newtile->m_Name = "floor";
    newtile->m_TileID = int('.');
    m_MapTiles.push_back(newtile);

    //tile 2
    newtile = new MapTile;
    newtile->m_Name = "wall";
    newtile->m_TileID = int(219);
    m_MapTiles.push_back(newtile);

    //**********START GRASS TILES***********
    //tile 3 - START GRASS TILES
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int('.');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_GREEN;
    m_MapTiles.push_back(newtile);

    //tile 4
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int(',');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_GREEN;
    m_MapTiles.push_back(newtile);

    //tile 5
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int('`');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_GREEN;
    m_MapTiles.push_back(newtile);

    //tile 6
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int('\'');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_GREEN;
    m_MapTiles.push_back(newtile);

    //tile 7
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int('\"');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_GREEN;
    m_MapTiles.push_back(newtile);

    //tile 8 - START LIGHT GRASS
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int('.');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_B_GREEN;
    m_MapTiles.push_back(newtile);

    //tile 9
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int(',');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_B_GREEN;
    m_MapTiles.push_back(newtile);

    //tile 10
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int('`');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_B_GREEN;
    m_MapTiles.push_back(newtile);

    //tile 11
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int('\'');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_B_GREEN;
    m_MapTiles.push_back(newtile);


    //tile 12
    newtile = new MapTile;
    newtile->m_Name = "grass";
    newtile->m_TileID = int('\"');
    newtile->m_BGColor = COLOR_BLACK;
    newtile->m_FGColor = COLOR_B_GREEN;
    m_MapTiles.push_back(newtile);
    //**********END GRASS TILES***********

    //tile 13
    newtile = new MapTile;
    newtile->m_Name = "water";
    newtile->m_TileID = int('~');
    newtile->m_FGColor = COLOR_B_BLUE;
    newtile->setLiquid(m_Liquids[0]);
    newtile->setWalkable(false);
    m_MapTiles.push_back(newtile);
    return true;
}

bool Engine::initMonsters()
{
    Monster *newmonster = new Monster;
    newmonster->m_Name = "unicorn";
    newmonster->m_TileID = int('U');
    newmonster->m_FGColor = COLOR_YELLOW;
    m_MonsterDB.push_back(newmonster);

    return true;
}

bool Engine::initItems()
{
    //item 0
    Item *newitem = new ContainerLiquid;
    ContainerLiquid *cptr = dynamic_cast<ContainerLiquid*>(newitem);
    cptr->m_Name = "water bottle";
    cptr->setMaxVolume(3);
    cptr->m_TileID = int('!');
    m_ItemDB.push_back(cptr);

    //item 1
    newitem = new MiscItem;
    newitem->m_Name = "rock";
    newitem->m_TileID = int('*');
    m_ItemDB.push_back(newitem);


    std::cout << "Initialized " << m_ItemDB.size() << " items - ";
    return true;
}

bool Engine::initLiquids()
{
    Liquid *newliquid = new Liquid;
    newliquid->setName("water");
    newliquid->setColor(COLOR_BLUE);
    m_Liquids.push_back(newliquid);

    return true;
}

bool Engine::initMap()
{
    testmap = new MapChunk;

    return true;
}

bool Engine::initPlayer()
{
    if(m_Player != NULL) delete m_Player;

    m_Player = new Player;

    m_Player->m_Name = "test player";
    m_Player->setMaxHealth(10);
    m_Player->setCurrentHealth(m_Player->getMaxHealth());

    return true;
}

bool Engine::newGame()
{
    //start new random seed
    m_Seed = time(NULL);
    srand(m_Seed);
    std::cout << "Randomizing seed : " << m_Seed << std::endl;

    //init map
    std::cout << "Initializing map...";
    if(initMap()) std::cout << "done.\n";
    else std::cout << "failed.\n";

    //init player
    std::cout << "Initializing player...";
    if(initPlayer()) std::cout << "done.\n";
    else std::cout << "failed.\n";

    std::cout << "Initializing message manager...";
    if(m_MessageManager != NULL) delete m_MessageManager;
    m_MessageManager = new MessageManager;
    std::cout << "done.\n";

    //create unicorn
    testmap->addMonster(0, testmap->getRandomValidPosition());

    //randomize player starting position
    m_Player->setPosition(testmap->getRandomValidPosition());

    //add water bottle to player
    Item *pitem = createItem(0);
    ContainerLiquid *cptr = dynamic_cast<ContainerLiquid*>(pitem);
    cptr->fillWithLiquid(m_Liquids[0]);
    m_Player->addToInventory(pitem);

    //add rock
    m_Player->addToInventory( createItem(1));

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
                else if(event.key.code == sf::Keyboard::I) showInventory();
                else if(event.key.code == sf::Keyboard::F) selectItemFromInventory();
                else if(event.key.code == sf::Keyboard::D) dropItemUI();
                else if(event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Numpad4)
                {
                    m_Player->walkDir(DIR_WEST);
                }
                else if(event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Numpad6)
                {
                    m_Player->walkDir(DIR_EAST);
                }
                else if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Numpad8)
                {
                    m_Player->walkDir(DIR_NORTH);
                }
                else if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Numpad2)
                {
                    m_Player->walkDir(DIR_SOUTH);
                }
                else if(event.key.code == sf::Keyboard::Numpad1)
                {
                    m_Player->walkDir(DIR_SW);
                }
                else if(event.key.code == sf::Keyboard::Numpad3)
                {
                    m_Player->walkDir(DIR_SE);
                }
                else if(event.key.code == sf::Keyboard::Numpad7)
                {
                    m_Player->walkDir(DIR_NW);
                }
                else if(event.key.code == sf::Keyboard::Numpad9)
                {
                    m_Player->walkDir(DIR_NE);
                }
            }
        }

        //UPDATE
        //center viewport on player
        centerViewport(m_Player->getPosition());


        //draw
        drawMap();
        drawItems();
        drawPlayer();
        drawMonsters();
        drawStatus();
        drawMessageQue();

        //update and display screen
        m_Screen->display();

        if(!m_Player->isAlive())
        {
            return;
        }

    }
}

/////////////////////////////////////////////////////////////////////////////////
//  DRAW
bool Engine::posInViewport(int x, int y)
{
    if(x < m_Viewport.left || y < m_Viewport.top ||
       x >= m_Viewport.left + m_Viewport.width || y >= m_Viewport.top + m_Viewport.height)
    {
         return false;
    }

    return true;
}

void Engine::centerViewport(int x, int y)
{
    m_Viewport.left = x - m_Viewport.width/2;
    m_Viewport.top = y - m_Viewport.height/2;

    //if map moves off viewport, keep map in view
    if(m_Viewport.left < 0) m_Viewport.left = 0;
    else if(m_Viewport.left + m_Viewport.width >= testmap->getDimensions().x) m_Viewport.left = testmap->getDimensions().x - m_Viewport.width;

    if(m_Viewport.top < 0) m_Viewport.top = 0;
    else if(m_Viewport.top + m_Viewport.height >= testmap->getDimensions().y) m_Viewport.top = testmap->getDimensions().y - m_Viewport.height;
}

bool Engine::posInViewport(sf::Vector2i pos)
{
    return posInViewport(pos.x, pos.y);
}

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

void Engine::drawTileInViewport(int x, int y, int tilenum, int fgcolor, int bgcolor)
{
    if(posInViewport(x,y))
    {
        drawTile(x - m_Viewport.left, y - m_Viewport.top, tilenum, fgcolor, bgcolor);
    }
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

void Engine::drawPlayer()
{
    if(m_Player == NULL) return;

    sf::Vector2i ppos = m_Player->getPosition();

    drawTileInViewport(ppos.x, ppos.y, m_Player->getTileID(), m_Player->getFGColor(), m_Player->getBGColor());
}

void Engine::drawMap()
{

    for(int i = 0; i < testmap->getDimensions().y; i++)
    {
        for(int n = 0; n < testmap->getDimensions().x; n++)
        {
            MapTile *ttile = getMapTile( testmap->getTile(n, i));

            if(posInViewport(n, i))
            drawTileInViewport(n, i, ttile->getTileID(), ttile->getFGColor(), ttile->getBGColor());

        }
    }
}

void Engine::drawMonsters()
{
    for(int i = 0; i < int(testmap->getMapMonsters()->size()); i++)
    {
        Monster *tmonster = (*testmap->getMapMonsters())[i];

        if(posInViewport(tmonster->getPosition()))
        drawTileInViewport(tmonster->getPosition().x, tmonster->getPosition().y, tmonster->getTileID(), tmonster->getFGColor(),
                 tmonster->getBGColor());
    }
}

void Engine::drawItems()
{
    for(int i = 0; i < int(testmap->getMapItems()->size()); i++)
    {
        Item *titem = (*testmap->getMapItems())[i];

        if(posInViewport(titem->getPosition()))
        drawTileInViewport(titem->getPosition().x, titem->getPosition().y, titem->getTileID(), titem->getFGColor(),
                 titem->getBGColor());
    }
}

void Engine::drawStatus()
{
    std::stringstream pname;
    pname << "Name : " << m_Player->getName();
    drawString(50, 2, pname.str());

    std::stringstream pturns;
    pturns << "Turns : " << m_Player->getTurns();
    drawString(50,3, pturns.str());

    std::stringstream phealth;
    phealth << "HP : " << m_Player->getCurrentHealth() << "/" << m_Player->getMaxHealth();
    drawString(50,4, phealth.str());

    //if player needs to drink
    if(m_Player->getHydrationLevel() <= 3)
    {
        //if player is getting thirsty
        if(m_Player->getHydrationLevel() >= 2) drawString(50, 5, "Thirsty", COLOR_BLUE);
        else drawString(50,5, "Dehydrated", COLOR_RED);
    }
    else if(m_Player->getHydrationLevel() == m_Player->getMaxHydrationLevel())
    {
        drawString(50,5, "Well Hydrated", COLOR_GREEN);
    }
}

void Engine::drawMessageQue()
{
    std::vector<Message*> *msgque = m_MessageManager->getMessageQue();

    if(msgque == NULL)
    {
        std::cout << "Error - unable to draw message que, que = NULL!\n";
        return;
    }
    if(msgque->empty()) return;

    //cycle through each message and draw
    for(int i = 0; i < int(msgque->size()); i++)
    {
        drawString(0, i, (*msgque)[i]->getString());
    }
}

///////////////////////////////////////////////////////////////////

void Engine::showInventory()
{
    bool quit = false;

    int selecteditem = 0;

    std::vector< Item*> *inv = m_Player->getInventory();

    while(!quit)
    {
        m_Screen->clear();

        sf::Event event;

        while(m_Screen->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) quit = true;
                else if(event.key.code == sf::Keyboard::Down) selecteditem++;
                else if(event.key.code == sf::Keyboard::Up) selecteditem--;
                else if(event.key.code == sf::Keyboard::Return)
                {
                    //if using liquid container
                    if( (*inv)[selecteditem]->getType() == OBJ_ITEM_CONTAINER_LIQUID)
                    {
                        ContainerLiquid *cptr = dynamic_cast<ContainerLiquid*>( (*inv)[selecteditem]);
                        //if liquid container is not empty
                        if(!cptr->isEmpty() )
                        {
                            if(m_Player->drink(cptr->getLiquidType()))
                            {
                                cptr->removeLiquid(1);
                            }
                        }
                    }
                }
            }
        }

        if(selecteditem < 0) selecteditem = int(inv->size()-1);
        else if(selecteditem >= int(inv->size())) selecteditem = 0;
        //draw



        if(inv->empty())
        {
            drawString(0,0,"You have nothing!\n");
        }
        else
        {
            drawString(0,0, "You are carrying:");
            drawString(0,1, "-----------------");

            for(int i = 0; i < int(inv->size()); i++)
            {
                std::stringstream istring;

                istring << (*inv)[i]->getName();

                //if item is a container
                if( (*inv)[i]->getType() == OBJ_ITEM_CONTAINER)
                {
                    //get container pointer
                    Container *cptr = NULL;
                    cptr = dynamic_cast<Container*>((*inv)[i]);

                    //if container is empty
                    if(cptr->getInventory()->empty()) istring << " (empty)";
                }
                else if( (*inv)[i]->getType() == OBJ_ITEM_CONTAINER_LIQUID)
                {
                    ContainerLiquid *cptr = dynamic_cast<ContainerLiquid*>( (*inv)[i]);
                    if(cptr->getCurrentVolume() <= 0) istring << " (empty)";
                    else
                    {
                        istring << " (" << cptr->getCurrentVolume() << "/" << cptr->getMaxVolume() << " of " << cptr->getLiquidType()->getName() << ")";

                    }
                }

                if(selecteditem == i)
                {
                    drawString(0, i+2, istring.str(), COLOR_BLACK, COLOR_WHITE);
                }
                else drawString(0, i+2, istring.str());
            }
        }



        //update
        m_Screen->display();
    }

}

Item *Engine::selectItemFromInventory(std::string promptstr, std::vector<int> itemfilter)
{
    bool quit = false;

    Item *selecteditem = NULL;
    int selecteditemindex = 0;

    //get player inventory list
    std::vector<Item*> *inv = m_Player->getInventory();
    std::vector<Item*> filteredlist;

    //build item list based on filter
    for(int i = 0; i < int(inv->size()); i++)
    {
        //for each inventory item, check to see if it matches filter criteria
        for(int n = 0; n < int(itemfilter.size()); n++)
        {
            //if filter matches or OBJ_TOTAL filter is used, add item to filtered items list
            if( (*inv)[i]->getType() == itemfilter[n] || itemfilter[n] == OBJ_TOTAL)
            {
                filteredlist.push_back( (*inv)[i]);
                break;
            }
        }
    }

    while(!quit)
    {
        sf::Event event;

        m_Screen->clear();

        while(m_Screen->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) quit = true;
                else if(event.key.code == sf::Keyboard::Down) selecteditemindex++;
                else if(event.key.code == sf::Keyboard::Up) selecteditemindex--;
                else if(event.key.code == sf::Keyboard::Return)
                {
                    selecteditem = filteredlist[selecteditemindex];

                    //debug
                    std::cout << "selected " << selecteditem->getName() << std::endl;

                    return selecteditem;
                }
            }
        }

        //resolve selected item index if out of bounds
        if(selecteditemindex >= int(filteredlist.size()) ) selecteditemindex = 0;
        else if(selecteditemindex < 0) selecteditemindex = int(filteredlist.size()-1);

        //draw
        drawString(0,0, promptstr);

        //draw all items in filtered items list
        for(int i = 0; i < int(filteredlist.size()); i++)
        {
            std::stringstream inamestr;
            inamestr << filteredlist[i]->getName();

            if(selecteditemindex == i) drawString(0, i+2, inamestr.str(), COLOR_BLACK, COLOR_WHITE);
            else drawString(0, i+2, inamestr.str());
        }

        //display
        m_Screen->display();
    }

    return selecteditem;
}


///////////////////////////////////////////////////////////////////
MapTile *Engine::getMapTile(int tileid)
{
    if(m_MapTiles.empty())
    {
        std::cout << "ERROR!  There are no maptiles stored in memory!!\n";
        return NULL;
    }

    if(tileid < 0 || tileid >= int(m_MapTiles.size()) )
    {
        std::cout << "Error getting tile " << tileid << ", outside range of available map tiles!\n";
        return m_MapTiles[0];
    }

    return m_MapTiles[tileid];
}

bool Engine::validWalkableTile(int x, int y)
{
    sf::Vector2i mapdim = testmap->getDimensions();
    if(x < 0 || y < 0 || x >= mapdim.x || y >= mapdim.y) return false;

    MapTile *ttile = getMapTile( testmap->getTile(x,y) );
    if(!ttile->isWalkable()) return false;

    return true;
}

int Engine::getDirectionFromUser()
{
    bool quit = false;
    int dir = DIR_NONE;

    while(!quit)
    {
        sf::Event event;

        //handle events
        while(m_Screen->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Numpad4)
                {
                    dir = DIR_WEST;
                }
                else if(event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Numpad6)
                {
                    dir = DIR_EAST;
                }
                else if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Numpad8)
                {
                    dir = DIR_NORTH;
                }
                else if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Numpad2)
                {
                    dir = DIR_SOUTH;
                }
                else if(event.key.code == sf::Keyboard::Numpad1)
                {
                    dir = DIR_SW;
                }
                else if(event.key.code == sf::Keyboard::Numpad3)
                {
                    dir = DIR_SE;
                }
                else if(event.key.code == sf::Keyboard::Numpad7)
                {
                    dir = DIR_NW;
                }
                else if(event.key.code == sf::Keyboard::Numpad9)
                {
                    dir = DIR_NE;
                }

                quit = true;
            }
        }

    }

    return dir;
}

///////////////////////////////////////////////////////////////////
Monster *Engine::createMonster(int monsterid)
{
    if(monsterid < 0 || monsterid >= getMonsterDBSize())
    {
        std::cout << "Error copying monster, monster ID out of range!\n";
        return NULL;
    }

    Monster *newmonster = new Monster();
    *newmonster = *m_MonsterDB[monsterid];

    return newmonster;
}

Item *Engine::createItem(int itemid)
{
    if(itemid < 0 || itemid > getItemDBSize())
    {
        std::cout << "Error creating item.  Item ID is out of range!\n";
        return NULL;
    }

    Item *newitem = NULL;

    //determine which type to create
    switch( m_ItemDB[itemid]->getType())
    {
    case OBJ_ITEM_CONTAINER:
        newitem = new Container();
        //*newitem = *m_ItemDB[itemid];
        break;
    case OBJ_ITEM_CONTAINER_LIQUID:
        newitem = new ContainerLiquid();
        //*newitem = *m_ItemDB[itemid];
        break;
    case OBJ_ITEM_MISC:
        newitem = new MiscItem;
        //*newitem = *m_ItemDB[itemid];
        break;
    default:
        std::cout << "Error creating item, unrecognized type!\n";
        break;
    }

    if(newitem == NULL) return false;
    else *newitem = *m_ItemDB[itemid];

    return newitem;
}

bool Engine::moveItem(Item *titem, std::vector<Item*> *isource, std::vector<Item*> *idest)
{
    if(isource == NULL || idest == NULL || titem == NULL)
    {
        std::cout << "Error moving item.  Item, source, or destionation is not valid!\n";
        return false;
    }

    //find item in source list
    for(int i = int(isource->size()-1); i >= 0; i--)
    {
        //target object found in source list
        if(titem == (*isource)[i])
        {
            //remove from source list
            isource->erase(isource->begin() + i);
            break;
        }

        if(i == 0)
        {
            std::cout << "Error in moveitem, unable to find target item in source list\n";
            return false;
        }
    }

    //add item to destination list
    idest->push_back(titem);


    std::cout << "Moved item " << titem->getName() << " to destination list.\n";
    return true;
}

void Engine::dropItemUI()
{
    Item *titem = selectItemFromInventory("Drop what?");

    //no valid item selected to drop
    if(titem == NULL) return;

    //move item from player inventory to map items
    moveItem(titem, m_Player->getInventory(), testmap->getMapItems());

    //set item's position to players position
    titem->setPosition( m_Player->getPosition());
    m_MessageManager->addMessage("Dropped item.");
}

void Engine::playerTurnUpdates()
{
    //m_MessageManager->update();
}
