#include "salvager.hpp"

Salvager::Salvager()
{
    //null out pointers
    mPlayer = NULL;
    mCamera = NULL;



}

void Salvager::start()
{
    //init curses
    initCurses();

    //init camera
    initCamera();

    //init map tiles
    initMapTiles();

    //init master items
    initItems();

    //init master mobs
    initMobs();

    //start new game
    newGame();

    shutdown();
}

void Salvager::shutdown()
{
    //clear game
    clearGame();

    //clear screen
    clear();
    refresh();
}
void Salvager::newGame()
{
    //clear out game data
    clearGame();

    //init seed
    initSeed();

    //init player
    initPlayer();

    //init map
    initMap();

    //start main loop
    mainLoop();
}

void Salvager::clearGame()
{

    if(mPlayer != NULL)
    {
        delete mPlayer;
    }

    for(int i = 0; i < int(mActiveMaps.size()); i++)
    {
        for(int n = 0; n < int(mActiveMaps[i].size()); n++)
        {
            delete mActiveMaps[i][n];
            mActiveMaps[i][n] = NULL;
        }
        mActiveMaps[i].clear();
    }
    mActiveMaps.clear();
}

void Salvager::initCurses()
{
    //init screen
    initscr();

    //no echoing
    noecho();

    //allow arrowkeys and other extended keys
    keypad(stdscr, TRUE);

    //set cursor to invisible
    curs_set(0);

    cbreak();
    raw();

    //nodelay(stdscr, TRUE);

    //halfdelay
    halfdelay(HDELAY);


    //init colors
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);

}

void Salvager::initSeed()
{
    std::ifstream seedf;

    seedf.open("data\\map\\seed.txt");

    //if unable to open seed file
    if(!seedf.is_open())
    {
        //generate new seed
        mSeed = int(time(NULL));

        //write to file
        std::ofstream seedfo;
        seedfo.open("data\\map\\seed.txt");
        seedfo << mSeed << std::endl;
        seedfo.close();

    }
    else
    {
        char buf[20];
        seedf.getline(buf,20);
        mSeed = atoi(buf);

        seedf.close();
    }
}

void Salvager::initCamera()
{
    mCamera = new Camera(0,0,60,23);
    mCamera->setCenter(5,5);
}

void Salvager::initMapTiles()
{
    //initialize master index of map tile types
    //this is only done once

    MapTile temp;
    //0
    temp.mIcon = ' ';
    temp.mColor = C_WHITE;
    temp.mBright = false;
    temp.mPassable = true;
    mMapTiles.push_back(temp);

    //1
    temp.mIcon = '.';
    temp.mName = "sand";
    temp.mColor = C_YELLOW;
    temp.mBright = false;
    temp.mPassable = true;
    mMapTiles.push_back(temp);

    //2
    temp.mIcon = '\'';
    mMapTiles.push_back(temp);

    //3
    temp.mIcon = ',';
    mMapTiles.push_back(temp);

    //4
    temp.mIcon = '`';
    mMapTiles.push_back(temp);

    //5
    temp.mIcon = '.';
    temp.mBright = true;
    mMapTiles.push_back(temp);

    //6
    temp.mIcon = '\'';
    mMapTiles.push_back(temp);

    //7
    temp.mIcon = ',';
    mMapTiles.push_back(temp);

    //8
    temp.mIcon = '`';
    mMapTiles.push_back(temp);

    //9
    temp.mIcon = '~';
    temp.mColor = C_YELLOW;
    temp.mBright = false;
    mMapTiles.push_back(temp);

    //10
    temp.mIcon = ACS_LANTERN;
    temp.mName = "cactus";
    temp.mColor = C_GREEN;
    temp.mBright = false;
    temp.mPassable = false;
    mMapTiles.push_back(temp);

    //11
    temp.mIcon = ',';
    temp.mName = "rock";
    temp.mColor = C_WHITE;
    temp.mBright = true;
    temp.mPassable = true;
    mMapTiles.push_back(temp);

    //12
    temp.mIcon = '.';
    mMapTiles.push_back(temp);

    //13
    temp.mIcon = '\'';
    mMapTiles.push_back(temp);

    //14
    temp.mIcon = '`';
    mMapTiles.push_back(temp);

    //15
    temp.mIcon = ACS_BLOCK;
    temp.mColor = C_WHITE;
    temp.mBright = false;
    temp.mPassable = false;
    mMapTiles.push_back(temp);

}

void Salvager::initItems()
{
    Item temp;

    //0
    temp.mID = 0;
    temp.mIcon = '*';
    temp.mName = "rock";
    mItems.push_back(temp);

    //1
    temp.mID = 1;
    temp.mIcon = '%';
    temp.mName = "apple";
    temp.mFood = new Item_Food;
    temp.mFood->calories = 180;
    temp.mColor = C_RED;
    mItems.push_back(temp);
    temp.mFood = NULL;

    //2
    temp.mID = 2;
    temp.mIcon = '\\';
    temp.mColor = C_WHITE;
    temp.mBright = true;
    temp.mName = "weapon";
    mItems.push_back(temp);

    //3
    temp.mID = 3;
    temp.mIcon = '[';
    temp.mColor = C_RED;
    temp.mBright = false;
    temp.mName = "clothing";
    mItems.push_back(temp);

    //4
    temp.mID = 4;
    temp.mIcon = '!';
    temp.mName = "plastic bottle";
    temp.mColor = C_CYAN;
    temp.mBright = true;
    temp.mDrink = new Item_Drink;
    temp.mDrink->volume = 12;
    mItems.push_back(temp);
    temp.mDrink = NULL;

    //check that all IDs match up
    for(int i = 0; i < int(mItems.size()); i++)
    {
        if(mItems[i].mID != i) printError("Item IDs do not match up!");
    }

}

void Salvager::initMobs()
{
    Mob temp;

    //0
    temp.mID = 0;
    temp.mName = "rabbit";
    temp.mIcon = 'r';
    temp.mDefaultBehavior = AI_WANDER;
    mMobs.push_back(temp);
}

void Salvager::initPlayer()
{
    //create player
    if(mPlayer != NULL)
    {
        std::cout << "Error initializing player, mPlayer != NULL\n";
        exit(1);
    }
    mPlayer = new Player;

    //if new player
    if(!mPlayer->loadPlayer(&mItems))
    {
        mPlayer->setPosition(4,4);
        mPlayer->setGlobalPosition(0,0);
        mPlayer->setHydration(500);
        mPlayer->setHour(12.0);
        mPlayer->setCalories(800);

    }

}

void Salvager::initMap()
{

    //generate active map array
    //resize array
    getActiveMaps(mPlayer->getGlobalX(), mPlayer->getGlobalY());

    //save all starting maps
    for(int i = 0; i < 3; i++)
        for(int n = 0; n < 3; n++) mActiveMaps[i][n]->saveMap();

}

//main loop
void Salvager::mainLoop()
{
    bool quit = false;

    int ch = 0;

    while(!quit)
    {

        //clear screen
        clear();

        //center camera on player
        mCamera->setCenter( mPlayer->getX(), mPlayer->getY());

        //draw
        drawMap();
        drawMapItems();
        drawMapMobs();
        mvprintw(24,0, "ch=%d", ch);

        drawPlayer();


        //debug info
        if(DEBUG)
        {

            mvprintw(23,0, "player:[%d][%d](%d,%d)", mPlayer->getGlobalX(), mPlayer->getGlobalY(), mPlayer->getX(), mPlayer->getY());
            mvprintw(23,30, "on tile :[");
            drawTile(40, 23, mActiveMaps[1][1]->getTile(mPlayer->getX(), mPlayer->getY()));
            mvprintw(23,41, "]-%s", mMapTiles[mActiveMaps[1][1]->getTile(mPlayer->getX(), mPlayer->getY())].mName.c_str());
            mvprintw(24,30, "seed:%d", mSeed);
            mvprintw(24,7, "Turns:%d", mPlayer->getTurns());
            mvprintw(1, 60, "Day :%d", mPlayer->getDay());
            mvprintw(2, 60, "Hour:%f", mPlayer->getHour());
            mvprintw(3, 60, "Hyd :%d", mPlayer->getHydration());
            mvprintw(4, 60, "Cal :%d", mPlayer->getCalories());


        }
        //refresh screen
        refresh();

        //get input
        ch = getch();

        if(handleInput(ch) == -1) quit = true;

        halfdelay(HDELAY);
    }

    //save states
    clear();
    printw("Saving...");
    refresh();
    saveGame();


}

void Salvager::saveGame()
{
    //save player state
    mPlayer->savePlayer();

    //save map state
    getActiveMaps(mPlayer->getGlobalX(), mPlayer->getGlobalY());
}


//draw
void Salvager::drawPlayer()
{
    int px = mPlayer->getX();
    int py = mPlayer->getY();

    if(px >= mCamera->getMapX() && px < mCamera->getMapX() + mCamera->getWidth() && py >= mCamera->getMapY() && py < mCamera->getMapY() + mCamera->getWidth())
    mvaddch(py - mCamera->getMapY() + mCamera->getAnchorY(), px - mCamera->getMapX() + mCamera->getAnchorX(), mPlayer->getIcon());
}

void Salvager::drawMap()
{
    //calculate center map position in array
    int centerMap = ACTIVE_MAPS/2;

    for(int i = 0; i < int(mActiveMaps.size()); i++)
    {
        for(int n = 0; n < int(mActiveMaps[i].size()); n++)
        {
            for(int y = 0; y < MAP_HEIGHT; y++)
            {
                for(int x = 0; x < MAP_WIDTH; x++)
                {
                    if( mCamera->isVisible(x + (n-centerMap)*MAP_WIDTH,  y + (i-centerMap)*MAP_HEIGHT) )
                    {
                        //if tile is visible in ambient light radius
                        if(getDistance(x + (n-centerMap)*MAP_WIDTH - mCamera->getMapX(), y + (i-centerMap)*MAP_HEIGHT - mCamera->getMapY(),
                                       mPlayer->getX() - mCamera->getMapX() + mCamera->getAnchorX(), mPlayer->getY() - mCamera->getMapY() + mCamera->getAnchorY() ) < getDaylightRadius())
                            {
                                //if tile is in player fov
                                if(inPlayerFov(mActiveMaps[i][n]->getGlobalX(), mActiveMaps[i][n]->getGlobalY(), x,y))
                                {
                                    drawTile(x + (n-centerMap)*MAP_WIDTH - mCamera->getMapX(), y + (i-centerMap)*MAP_HEIGHT - mCamera->getMapY(), mActiveMaps[i][n]->getTile(x,y));
                                }

                            }
                        //if tile is outside of visible light radius
                        else drawTile(x + (n-centerMap)*MAP_WIDTH - mCamera->getMapX(), y + (i-centerMap)*MAP_HEIGHT - mCamera->getMapY(), mActiveMaps[i][n]->getTile(x,y), false);
                    }
                }
            }
        }
    }

}

void Salvager::drawTile(int x, int y, int tile, bool vis)
{
    if(tile < 0 || tile >= int(mMapTiles.size()) )
    {
        std::cout << "Unable to draw map tile :" << tile << " is not in the mMapTiles index\n";
        return;
    }

    //mvaddch(y - mCamera->getMapY() + mCamera->getAnchorY(), x - mCamera->getMapX() + mCamera->getAnchorX(), mMapTiles[tile].mIcon);
    //if visible
    if(vis)
    {
        attron(COLOR_PAIR(mMapTiles[tile].mColor));
        if(mMapTiles[tile].mBright) attron(A_BOLD);
        mvaddch(y,x, mMapTiles[tile].mIcon);
        standend();
    }
    else
    {
        attron(COLOR_PAIR(C_CYAN));
        mvaddch(y,x, mMapTiles[tile].mIcon);
        standend();
    }

}

void Salvager::drawMapItems()
{
    //calculate center map position in array
    int centerMap = ACTIVE_MAPS/2;

    for(int i = 0; i < int(mActiveMaps.size()); i++)
    {
        for(int n = 0; n < int(mActiveMaps[i].size()); n++)
        {
            std::vector< ItemRef* > *mapitems = mActiveMaps[i][n]->getMapItems();

            for(int o = 0; o < int(mActiveMaps[i][n]->getMapItems()->size()); o++)
            {
                int x = (*mapitems)[o]->getX();
                int y = (*mapitems)[o]->getY();
                if( mCamera->isVisible(x + (n-centerMap)*MAP_WIDTH,  y + (i-centerMap)*MAP_HEIGHT) )
                {

                    drawItem(x + (n-centerMap)*MAP_WIDTH - mCamera->getMapX(), y + (i-centerMap)*MAP_HEIGHT - mCamera->getMapY(), (*mapitems)[o]);
                }
            }

        }
    }
}

void Salvager::drawItem(int x, int y, ItemRef *target, bool vis)
{
    if(target == NULL) {printError("Target itemref is NULL!"); return;}

    //if visible
    if(vis)
    {
        attron( COLOR_PAIR(target->getRef()->mColor));
        if(target->getRef()->mBright) attron( A_BOLD);
        mvaddch(y, x, target->getRef()->mIcon);
        standend();
    }
}

void Salvager::drawMapMobs()
{
    //calculate center map position in array
    int centerMap = ACTIVE_MAPS/2;

    for(int i = 0; i < int(mActiveMaps.size()); i++)
    {
        for(int n = 0; n < int(mActiveMaps[i].size()); n++)
        {
            std::vector< MobRef* > *mapmobs = mActiveMaps[i][n]->getMapMobs();

            for(int o = 0; o < int(mActiveMaps[i][n]->getMapMobs()->size()); o++)
            {
                int x = (*mapmobs)[o]->getX();
                int y = (*mapmobs)[o]->getY();
                if( mCamera->isVisible(x + (n-centerMap)*MAP_WIDTH,  y + (i-centerMap)*MAP_HEIGHT) )
                {

                    drawMob(x + (n-centerMap)*MAP_WIDTH - mCamera->getMapX(), y + (i-centerMap)*MAP_HEIGHT - mCamera->getMapY(), (*mapmobs)[o]);
                }
            }

        }
    }
}

void Salvager::drawMob(int x, int y, MobRef *target, bool vis)
{
    if(target == NULL) {printError("Target itemref is NULL!"); return;}

    //if visible
    if(vis)
    {
        //attron( COLOR_PAIR(target->getRef()->mColor));
        //if(target->getRef()->mBright) attron( A_BOLD);
        mvaddch(y, x, target->getRef()->mIcon);
        //standend();
    }
}

//player functions
void Salvager::movePlayer(int dir)
{
    //proposed new player position
    int nx = mPlayer->getX();
    int ny = mPlayer->getY();
    int gx = mPlayer->getGlobalX();
    int gy = mPlayer->getGlobalY();

    //used for valid tile check
    int mapoffsetX = 0;
    int mapoffsetY = 0;

    switch(dir)
    {
    case NORTH:
        ny--;
        break;
    case SOUTH:
        ny++;
        break;
    case WEST:
        nx--;
        break;
    case EAST:
        nx++;
        break;
    case SOUTHWEST:
        nx--;
        ny++;
        break;
    case SOUTHEAST:
        nx++;
        ny++;
        break;
    case NORTHWEST:
        nx--;
        ny--;
        break;
    case NORTHEAST:
        nx++;
        ny--;
        break;
    default:
        break;
    }

    //if player globally transitioned west
    if(nx < 0)
    {
        nx = MAP_WIDTH-1;
        gx--;
        mapoffsetX = -1;
    }
    //if player globally transitioned east
    else if(nx >= MAP_WIDTH)
    {
        nx = 0;
        gx++;
        mapoffsetX = 1;
    }
    //if player globally transitioned north
    if(ny < 0)
    {
        ny = MAP_HEIGHT-1;
        gy--;
        mapoffsetY = -1;
    }
    //if player globally transitioned south
    else if(ny >= MAP_HEIGHT)
    {
        ny = 0;
        gy++;
        mapoffsetY = 1;
    }

    //if no map transition was made, do a tile check
    //if passed, set players position and return
    if(mapoffsetX == 0 && mapoffsetY == 0)
    {
        if(!validTile(mActiveMaps[1][1], nx, ny)) return;

        //set players position to new position
        mPlayer->setPosition(nx, ny);
       endTurn();
        return;
    }

    //set players position to new position
    //mPlayer->setPosition(nx, ny);

    //if player transitioned
    //do a tile check on adjacent map
    //and if passed, move player globally and locally
    if( mPlayer->getGlobalX() != gx || mPlayer->getGlobalY() != gy)
    {
        if(!validTile( mActiveMaps[1+mapoffsetY][1+mapoffsetX], nx, ny)) return;

        //set players position to new position
        mPlayer->setPosition(nx, ny);

        //since player moved outside of current map
        //change players global position
        mPlayer->setGlobalPosition(gx,gy);
        //save and get new active maps
        getActiveMaps(gx, gy);

        //increase players turn
        endTurn();

    }

}

void Salvager::playerGet()
{
    //get the active player centric map's map items
    std::vector< ItemRef* > *mapitems = mActiveMaps[1][1]->getMapItems();

    //go backwards, since last item on the list is what is displayed in stacked items
    //go through each map item and check for any items at player location
    for(int i = mapitems->size()-1; i >= 0; i--)
    {
        //if map item is at player location
        if( (*mapitems)[i]->getX() == mPlayer->getX() && (*mapitems)[i]->getY() == mPlayer->getY())
        {
            //get address for maps item
            ItemRef *transition = (*mapitems)[i];

            //remove item from maps item list
            mActiveMaps[1][1]->removeItem(transition);

            //add item to player inventory
            mPlayer->addItem(transition);

            return;
        }
    }
}

void Salvager::playerDrop()
{
    bool quit = false;
    int cursor = 0;
    int ch = 0;

    std::vector<ItemRef*> *playerinv = mPlayer->getInventory();

    clear();

    if(playerinv->empty())
    {
        printw("You have nothing to drop.");
        refresh();
        getch();
        return;
    }

    while(!quit)
    {
        clear();

        printw("Drop what?\n");

        for(int i = 0; i < int(playerinv->size()); i++ )
        {
            if(i == cursor) attron(A_REVERSE);
            printw("%s\n", (*playerinv)[i]->getName().c_str());
            standend();
        }

        refresh();

        ch = getch();

        if(ch == 27) quit = true;
        else if(ch == 13)
        {
            ItemRef *transition = (*playerinv)[cursor];
            mActiveMaps[1][1]->addItem(mPlayer->getX(), mPlayer->getY(),transition);
            mPlayer->removeItem(transition);
            return;

        }
        else if(ch == 258) cursor++;
        else if(ch ==259) cursor--;

        if(cursor < 0) cursor = playerinv->size()-1;
        else if(cursor >= int(playerinv->size()) ) cursor = 0;

    }

}

bool Salvager::playerDrink()
{
    std::vector< ItemRef*> playerDrinks;
    bool quit = false;
    int ch = 0;
    int cursor = 0;

    //disable halfdelay
    nocbreak();

    //std::vector< ItemRef*> *playerInv = mPlayer->getInventory();

    for(int i = 0; i < int(mPlayer->getInventory()->size()); i++)
    {
        if( (*mPlayer->getInventory())[i]->isDrink())
        {
            playerDrinks.push_back( (*mPlayer->getInventory())[i] );
        }
    }

    if(playerDrinks.empty())
    {
        clear();
        printw("You have nothing to drink.");
        refresh();
        getch();
        return false;
    }



    while(!quit)
    {
        clear();

        printw("Drink what?\n");

        for(int i = 0; i < int(playerDrinks.size()); i++)
        {

            //print volume gauge
            if(playerDrinks[i]->getDrink() != NULL)
            {
                float per_full = float(playerDrinks[i]->getDrink()->current_volume) / float(playerDrinks[i]->getRef()->mDrink->volume) * 100;
                mvprintw(1+i,1,"[");
                attron(COLOR_PAIR(C_GREEN));
                addch(ACS_BLOCK);
                if(per_full > 20) addch(ACS_BLOCK);
                if(per_full > 40) addch(ACS_BLOCK);
                if(per_full > 60) addch(ACS_BLOCK);
                if(per_full > 80) addch(ACS_BLOCK);
                standend();
                mvprintw(1+i, 7, "]");

            }
            else mvprintw(1+i, 1, "[     ]");

            //reverse color is cursor is selecting this item
            if(cursor == i) attron(A_REVERSE);
            //print container name
            mvprintw(i+1, 10,"%s", playerDrinks[i]->getName().c_str());

            //if empty
            if(playerDrinks[i]->getDrink() == NULL)
            {
                printw(" (empty)");
            }
            else //print liquid type
            {
                switch( playerDrinks[i]->getDrink()->liquid)
                {
                case 0:
                    printw(" of water");
                    break;
                case 1:
                    printw(" of beer");
                    break;
                default:
                    printw(" of unknown liquid");
                    break;
                }
                printw(" : %d", playerDrinks[i]->getDrink()->current_volume);
                 //if(playerDrinks[i]->getDrink()->current_volume == playerDrinks[i]->getRef()->mDrink->volume) printw(" (FULL)");
            }
            printw("\n");
            //reset screen attributes
            standend();
        }

        refresh();

        ch = getch();

        switch(ch)
        {
        case 27:
            quit = true;
            break;
        case KEY_DOWN:
            cursor++;
            break;
        case KEY_UP:
            cursor--;
            break;
        case 13: // enter
            if(mPlayer->drink(playerDrinks[cursor])) return true;
            else return false;
            break;
        default:
            break;
        }

        if(cursor < 0) cursor = playerDrinks.size()-1;
        else if(cursor >= int(playerDrinks.size()) ) cursor = 0;
    }

    return false;
}

//mob functions
void Salvager::moveMob(Map *tmap, MobRef *target, int dir)
{
    if(target == NULL)
    {
        printError("Cannot move target mob because it is null.\n");
        return;
    }

    if(dir < 0 || dir >=9)
    {
        std::stringstream errormsg;
        errormsg << "Cannot move mob " << target->getName() << " in direction " << dir << ".  Direction out of range.";
        printError(errormsg.str());
    }

    //proposed mob position
    int mx = target->getX();
    int my = target->getY();
    int gx = target->getGlobalX();
    int gy = target->getGlobalY();
    int gxoffset = gx - mActiveMaps[1][1]->getGlobalX();
    int gyoffset = gy - mActiveMaps[1][1]->getGlobalY();

    //move mobs position in direction
    switch(dir)
    {
    case SOUTHWEST:
        mx--;
        my++;
        break;
    case SOUTH:
        my++;
        break;
    case SOUTHEAST:
        mx++;
        my++;
        break;
    case WEST:
        mx--;
        break;
    case NODIR:
        break;
    case EAST:
        mx++;
        break;
    case NORTHWEST:
        mx--;
        my--;
        break;
    case NORTH:
        my--;
        break;
    case NORTHEAST:
        mx++;
        my--;
        break;
    default:
        break;
    }

    //check to see if mob transitioned off its current map
    if(mx < 0)
    {
        gxoffset--;
        mx = MAP_WIDTH-1;
    }
    else if(mx >= MAP_WIDTH)
    {
        gxoffset++;
        mx = 0;
    }

    if(my < 0)
    {
        gyoffset--;
        my = MAP_HEIGHT-1;
    }
    else if(my >= MAP_HEIGHT)
    {
        gyoffset++;
        my = 0;
    }

    //check active maps to see if mob is trying to move outside of active maps
    if(gxoffset < -1 || gyoffset < -1) return;
    else if(gxoffset > 1 || gyoffset > 1) return;

    //if mob did not transition outside of map
    if( gxoffset == gx - mActiveMaps[1][1]->getGlobalX() && gyoffset == gy - mActiveMaps[1][1]->getGlobalY())
    {
        target->setPos(mx,my);
    }

    else
    {
        //add mob to destination map
        mActiveMaps[1+gyoffset][1+gxoffset]->addMob(target,mx,my);

        //remove mob origin map
        tmap->removeMob(target);
    }
}


//map functions
void Salvager::getActiveMaps(int x, int y)
{
    //clear active maps
    // save map before deleting
    for(int i = 0; i < int(mActiveMaps.size()); i++)
    {
        for(int n = 0; n < int(mActiveMaps[i].size()); n++)
        {
            mActiveMaps[i][n]->setDiscovered(true);
            mActiveMaps[i][n]->saveMap();
            delete mActiveMaps[i][n];
        }
        mActiveMaps[i].clear();
    }

    mActiveMaps.clear();

    //generate new maps around input global coordinate
    //and put into the array



    mActiveMaps.resize(ACTIVE_MAPS);
    for(int i = 0; i < int(mActiveMaps.size()); i++)
    {
        for(int n = 0; n < ACTIVE_MAPS; n++)
        {

            Map *temp = new Map( n+x-1, i+y-1, int(mSeed) );
            //set master item list reference
            temp->setItemReference( &mItems);
            temp->setMobReference( &mMobs);

            //load mapfile
            temp->loadMap();

            temp->genGrass();

            //load mapfile
            //temp->loadMap();

            mActiveMaps[i].push_back(temp);
        }

    }
}

bool Salvager::validTile(Map *target, int x, int y)
{
    if( !mMapTiles[target->getTile(x, y)].mPassable) return false;

    return true;
}

Map *Salvager::getActiveMapAt(int gx, int gy)
{
    for(int i = 0; i < int(mActiveMaps.size()); i++)
    {
        for(int n = 0; n < int(mActiveMaps[i].size()); n++)
        {
            if(mActiveMaps[i][n]->getGlobalX() == gx && mActiveMaps[i][n]->getGlobalY()) return mActiveMaps[i][n];
        }
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////
//   ENGINE

int Salvager::handleInput(int ch)
{
    //handle input
        switch(ch)
        {
        case 27:
            return -1;
            break;
        case 32: // space
            movePlayer(NODIR);
            break;
        case 49:
            movePlayer(SOUTHWEST);
            break;
        case 50:
        case 258: //down
            movePlayer(SOUTH);
            break;
        case 51:
            movePlayer(SOUTHEAST);
            break;
        case 259: //up
        case 56:
            movePlayer(NORTH);
            break;
        case 260: // left
        case 52:
            movePlayer(WEST);
            break;
        case 53: //keypad 5
            mActiveMaps[1][1]->setTile(mPlayer->getX(), mPlayer->getY(), 15 );
            break;
        case 261: // right
        case 54:
            movePlayer(EAST);
            break;
        case 55:
            movePlayer(NORTHWEST);
            break;
        case 57:
            movePlayer(NORTHEAST);
            break;
        case 265://f1
            //printPerlin(10, 1, 2);
            debug();
            break;
        case 266://f2
            debug_time();
            break;
        case 269://f5

            break;
        case 272://f8

            break;
        /////// PLAYER COMMANDS
        case 105://i
            mPlayer->debug_viewInventory();
            break;
        case 103://g
            playerGet();
            break;
        case 100://d
            playerDrop();
            break;
        case 113: //q
            if(playerDrink()) endTurn();
            break;
        case 274: // f10
            //debug_resetActiveMaps();
            break;
        default:
            break;
        }
    return 0;
}

void Salvager::endTurn()
{
    mPlayer->increaseTurn();

    mobTurn();

}

void Salvager::mobTurn()
{
    for(int i = 0; i < int(mActiveMaps.size()); i++)
    {
        for(int n = 0; n < int(mActiveMaps[i].size()); n++)
        {

            std::vector< MobRef* > *mapmobs = mActiveMaps[i][n]->getMapMobs();

            for(int m = 0; m < int(mapmobs->size()); m++)
            {
                if( (*mapmobs)[m]->getDefaultBehavior() == AI_WANDER)
                {
                    moveMob(mActiveMaps[i][n], (*mapmobs)[m], rand()%9);
                }
            }

        }
    }
}

int Salvager::getDaylightRadius()
{
    //4-7 - daylight increases from radius 4 - 32
    //7 - 7 - daylight stays at 32
    // 7 - 9 - daylight decreases from 32 - 4
    if(DEBUG_DAYCYCLE) return 28;

    if(mPlayer->getHour() >= 4 && mPlayer->getHour() <= 7)
    {
        //recalculate , keep return value no greater than 30
    }
    else if( mPlayer->getHour() > 7 && mPlayer->getHour() <= 19)
    {
        //recalculate , keep return value no greater than 30
    }
    else if(mPlayer->getHour() > 19 && mPlayer->getHour() <= 21)
    {
        //recalculate , keep return value no greater than 30
    }
    else if(mPlayer->getHour() > 21)
    {
        //recalculate , keep return value no greater than 30
    }
    else if(mPlayer->getHour() < 4)
    {
        //recalculate , keep return value no greater than 30
    }

    return 0;
}

bool Salvager::inFov(int gx1, int gy1, int x1, int y1, int gx2, int gy2, int x2, int y2)
{
    //convert coordinate #2 relative to coord #1
    x2 += (gx2-gx1)*MAP_WIDTH;
    y2 += (gy2-gy1)*MAP_HEIGHT;
    //sa;lkfjaslkfj

    //y = mx + b
    //float m = float(y2/y1) / float(x2/x1);
    //float b = y1 - m*x1;

    return true;

}

bool Salvager::inPlayerFov(int gx, int gy, int x, int y)
{
    //some sight radius calculations should be done first to determine
    //if this check should be performed in the first place...

    //debug check
    if(DEBUG_FOV_OFF) return true;

    int px = mPlayer->getX();
    int py = mPlayer->getY();
    int pgx = mPlayer->getGlobalX();
    int pgy = mPlayer->getGlobalY();

    int x1 = ((gx-pgx)*MAP_WIDTH) + x;
    int y1 = ((gy-pgy)*MAP_HEIGHT) + y;

    //mvprintw(0,0,"plr[%d,%d](%d,%d)", pgx,pgy,px,py);
    //mvprintw(1,0,"tgt[%d,%d](%d,%d)", gx, gy, x, y);
    //mvprintw(2,0,"off(%d,%d)",x1,y1);

    //if checking tile player is on
    if(px-x1 == 0 && py-y1 == 0) return true;

    //if los lands on y axis
    if(px-x1 == 0)
    {
        //start from target and walk back to plr pos
        for(int i = y1; i != py; i+= (py-y1)/abs(py-y1))
        {
            //ignore first tile
            if(i == y1) continue;

            //if i is north of pgy
            if(i < 0)
            {
                //if target tile is passable return true
                if( !mMapTiles[mActiveMaps[1 +(gy-pgy)][1 + (gx-pgx)]->getTile(x,MAP_HEIGHT+i)].mPassable) return false;
            }
            //if i is south of
            else if( i >= MAP_HEIGHT)
            {
                if( !mMapTiles[mActiveMaps[1 +(gy-pgy)][1 + (gx-pgx)]->getTile(x,i - MAP_HEIGHT)].mPassable) return false;
            }
            else //if tile is within p map
            {
                if( !mMapTiles[mActiveMaps[1][1]->getTile(x,i)].mPassable) return false;
            }
        }

        //check passed, return true
        return true;

    }
    else //if tile lands on x axis
    if(py-y1 == 0)
    {
       //start from target and walk back to plr pos
        for(int i = x1; i != px; i+= (px-x1)/abs(px-x1))
        {
            //ignore first tile
            if(i == x1) continue;

            //if i is north of pgx
            if(i < 0)
            {
                //if target tile is passable return true
                if( !mMapTiles[mActiveMaps[1 +(gy-pgy)][1 + (gx-pgx)]->getTile(MAP_WIDTH+i,y)].mPassable) return false;
            }
            //if i is south of pgx
            else if( i >= MAP_WIDTH)
            {
                if( !mMapTiles[mActiveMaps[1 +(gy-pgy)][1 + (gx-pgx)]->getTile(i - MAP_WIDTH,y)].mPassable) return false;
            }
            else //if tile is within p map
            {
                if( !mMapTiles[mActiveMaps[1][1]->getTile(i,y)].mPassable) return false;
            }
        }

        //check passed, return true
        return true;
    }

    //y = mx+b
    float m = (float(y1-py)/float(x1-px) );
    float b = py - (m*px);

    //if coords are on the same active map as plr
    //if(gx == pgx && gy == pgy)
    //{
        for(int i = x1; i != px; i+= (px-x1)/abs(px-x1))
        {
            //if first tile, ignore
            if(i == x1) continue;

            int tempx = i;
            int tempy = round(m*i+b);
            int tempgx = pgx;
            int tempgy = pgy;

            //make adjustments as necessary to reflect local coordinate
            if(tempy < 0) {tempy = tempy + MAP_HEIGHT; tempgy--;}
            if(tempy >= MAP_HEIGHT) {tempy = tempy - MAP_HEIGHT; tempgy++;}
            if(tempx < 0) {tempx = tempx + MAP_WIDTH; tempgx--;}
            if(tempx >= MAP_WIDTH) {tempx = tempx - MAP_WIDTH; tempgx++;}

            //check to see if target tile is passable
            if( !mMapTiles[mActiveMaps[1 + (tempgy-pgy)][1 + (tempgx-pgx)]->getTile(tempx, tempy)].mPassable) return false;
        }

        for(int i = y1; i != py; i+= (py-y1)/abs(py-y1))
        {
            //if first tile, ignore
            if(i == y1) continue;

            int tempx = round((i-b)/m);
            int tempy = i;
            int tempgx = pgx;
            int tempgy = pgy;

            //make adjustments as necessary to reflect local coordinates
            if(tempy < 0) {tempy = tempy + MAP_HEIGHT; tempgy--;}
            if(tempy >= MAP_HEIGHT) {tempy = tempy - MAP_HEIGHT; tempgy++;}
            if(tempx < 0) {tempx = tempx + MAP_WIDTH; tempgx--;}
            if(tempx >= MAP_WIDTH) {tempx = tempx - MAP_WIDTH; tempgx++;}

            //check to see if target tile is passable
            if( !mMapTiles[mActiveMaps[1 + (tempgy-pgy)][1 + (tempgx-pgx)]->getTile( tempx, tempy)].mPassable) return false;
        }

        return true;
    //}



    return false;
}

//debug

void Salvager::debug()
{

    bool quit = false;
    int ch = 0;

    while(!quit)
    {
        clear();

        std::vector<std::string> menu_options;
        menu_options.push_back("Add Item to Player");
        menu_options.push_back("Add 1 of Each Item to Player");

        printw("DEBUG MENU\n");
        printw("----------\n");
        for(int opt = 0; opt < int(menu_options.size()); opt++)
        {
            printw("  %d) %s\n", opt+1, menu_options[opt].c_str());
        }

        mvprintw(20,0, "Press ESC to quit...");

        refresh();

        ch = getch();

        if(ch == 27) quit = true;
        else if(ch == 49) // 1
        {
            int itype;
            int qty;

            clear();
            echo();
            //print items
            for(int ic = 0; ic < int(mItems.size()); ic++) printw("%d - %s\n", ic, mItems[ic].mName.c_str());

            printw("Enter item id [0-%d] :", mItems.size()-1);
            scanw("%d", &itype);
            if(itype < 0 || itype >= int(mItems.size()) )
            {
                printw("Invalid item type.\n");
                getch();
                return;
            }

            printw("Enter qty. to add? :");
            scanw("%d", &qty);

            if(qty <= 0)
            {
                printw("Invalid QTY.\n");
                noecho();
                getch();
                return;
            }

            printw("Adding %s x%d to player.\n", mItems[itype].mName.c_str(), qty );


            if(mItems[itype].isDrink())
            {
                printw("Will this drink container contain liquid? (y/n) ");
                ch = getch();

                if(ch == 121)
                {

                    int liq;


                    printw("\nEnter liquid type [0-1] :");
                    scanw("%d", &liq);

                    for(int i = 0; i < qty; i++)
                    {

                        ItemRef *newitem = new ItemRef( &mItems[itype]);
                        Item_DrinkRef *newdrink = new Item_DrinkRef;
                        newdrink->liquid = liq;
                        newdrink->current_volume = 0;
                        newitem->setDrink(newdrink);
                        newitem->fillDrink(liq);

                        mPlayer->addItem(newitem);
                    }


                }
                else // add empty bottle
                {
                    for(int i = 0; i < qty; i++)
                    {
                        ItemRef *newitem = new ItemRef( &mItems[itype]);
                        mPlayer->addItem(newitem);
                    }
                }

            }
            else
            {
                for(int i = 0; i < qty; i++)
                {
                    ItemRef *newitem = new ItemRef( &mItems[itype]);
                    mPlayer->addItem(newitem);
                }
                getch();
            }


            noecho();
            quit = true;
        }
        else if(ch==50) // 2
        {
            for(int i = 0; i < int(mItems.size()); i++)
            {
                ItemRef *newitem = new ItemRef( &mItems[i]);
                mPlayer->addItem(newitem);
            }
            clear();
            printw("Added %d items to inventory.", mItems.size());
            getch();
            return;
        }
    }

}

void Salvager::debug_resetActiveMaps()
{
    //clear all map deltas from each map in the active map array
    for(int i = 0; i < int(mActiveMaps.size()); i++)
    {
        for(int n = 0; n < int(mActiveMaps[i].size()); n++)
        {
            mActiveMaps[i][n]->debugClearDeltas();
            mActiveMaps[i][n]->saveMap();

        }
    }
}

void Salvager::debug_time()
{
    int turns = 0;

    clear();
    echo();
    curs_set(1);

    printw("Enter turns:");
    refresh();
    scanw("%d", &turns);

    printw("Days:%d", turns/24);
    printw("\nLeftover : %d", turns%24);
    refresh();
    getch();


}
