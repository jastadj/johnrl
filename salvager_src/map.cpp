#include "map.hpp"

Map::Map(int x, int y, int seed)
{
    //set seed
    mSeed = seed;

    //set global map position, relative to origin
    mGlobalX = x;
    mGlobalY = y;

    //set discovered to false by default
    mDiscovered = false;

    //init map vectory
    mMapArray.resize(MAP_HEIGHT);

    for(int i = 0; i < MAP_HEIGHT; i++)
        mMapArray[i].resize(MAP_WIDTH);

}

Map::~Map()
{


    for(int i = int(mMapArray.size()-1); i >= 0; i--)
    {
        mMapArray[i].clear();
    }

    mMapArray.clear();
}

int Map::getTile(int x, int y)
{
    if( x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
    {
        std::cout << "Map tile (" << x << "," << y << ") is not with maps array!\n";
        return -1;
    }

    //first check delta of map array
    for(int i = 0; i < int(mMapDelta.size()); i++)
    {
        if(mMapDelta[i][0] == x && mMapDelta[i][1] == y) return mMapDelta[i][2];
    }

    return mMapArray[y][x];
}

void Map::setTile(int x, int y, int tile)
{
    //go through map deltas and see if this position already exists
    for(int i = 0; i < int(mMapDelta.size()); i++)
    {
        if( mMapDelta[i][0] == x && mMapDelta[i][1] == y)
        {
            mMapDelta[i][2] = tile;
            return;
        }
    }

    //if no map delta at x,y was found, create a new one
    std::vector<int> temparray;
    temparray.push_back(x);
    temparray.push_back(y);
    temparray.push_back(tile);

    mMapDelta.push_back(temparray);
}
void Map::fillMap(int tile)
{
    for(int i = 0; i < int(mMapArray.size()); i++)
    {
        for(int n = 0; n < int(mMapArray[i].size()); n++)
        {
            mMapArray[i][n] = tile;
        }
    }
}

void Map::genGrass()
{
    if(mItemList == NULL)
    {
        printError("Unable to generate, no item list is referenced.\n");
        return;
    }

    //this is not a very good way of creating a random seed per map
    // since 0 * anything will be zero, so all mapes on a 0 axis will gen the same
    int seed = mSeed + (mGlobalX * mGlobalY);

    srand(seed);


    //put code here for a one time generation
    if(!mDiscovered)
    {
        if(rand()%1000 > 500)
        {
            ItemRef *newitem = new ItemRef( &(*mItemList)[0]);
            newitem->setPos( rand()%MAP_WIDTH, rand()%MAP_HEIGHT);
            newitem->setGlobalPos(mGlobalX, mGlobalY);
            mMapItems.push_back(newitem);
        }

        //mob debug
        if(mGlobalX == 0 && mGlobalY == 0)
        {
            MobRef *tmob = new MobRef( &(*mMobList)[0]);
            tmob->setPos(1,1);
            tmob->setGlobalPos(mGlobalX, mGlobalY);
            addMob(tmob,0,0);
        }
        if(mGlobalX == -1 && mGlobalY == -1)
        {

        }

    }

    srand(seed);


    for(int i = 0; i < MAP_HEIGHT; i++)
    {
        for(int n = 0; n < MAP_WIDTH; n++)
        {

            mMapArray[i][n] = rand()%9 + 1;

            //random chance to generate a tree
            if(rand()%1000 > 998) mMapArray[i][n] = 10;
            else if(rand()%1000 > 995) mMapArray[i][n] = rand()%4 + 11;


            //put code here for a one time generation
            if(!mDiscovered)
            {

            }

        }
    }

    //debug
    if(mGlobalX == 0 && mGlobalY == 0)
    {
        for(int i = 12; i < 19; i++)
        {
            for(int n = 12; n < 19; n++)
            {
                mMapArray[i][n] = 15;
            }
        }
    }

    //now that the map generation is complete, set the discovered flag to true
    mDiscovered = true;

}

//items

void Map::removeItem( ItemRef *target)
{
    for(int i = int(mMapItems.size()-1); i >= 0; i--)
    {
        if(mMapItems[i] == target)
        {
             mMapItems.erase( mMapItems.begin() + i);
             return;
        }
    }

}

void Map::addItem(int x, int y, ItemRef *target)
{
    target->setPos(x,y);
    target->setGlobalPos( mGlobalX, mGlobalY);
    mMapItems.push_back(target);
}

//mob functions

void Map::addMob(MobRef *tmob, int x, int y)
{
    if(tmob == NULL)
    {
        printError("Error adding mob to map, mob is null.\n");
        return;
    }

    if(x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
    {
        std::stringstream errormsg;
        errormsg << "Error adding mob to map, position out of bounds (" << x << "," << y << ")";

        printError(errormsg.str());
        return;
    }

    //set mobs map position
    tmob->setPos(x,y);
    tmob->setGlobalPos(mGlobalX, mGlobalY);

    mMapMobs.push_back(tmob);

}

void Map::removeMob(MobRef *tmob)
{
    if(tmob == NULL)
    {
        printError("Unable to remove mob from map, mob is NULL!");
        return;
    }

    for(int i = 0; i < int(mMapMobs.size()); i++)
    {
        if(mMapMobs[i] == tmob)
        {
            mMapMobs.erase(mMapMobs.begin() + i);
            return;
        }
    }

    printError("Can not remove target mob from map, mob is not in the mob list!");
}



//load/save

void Map::saveMap()
{
    //generate filename
    std::stringstream filename;
    //add directory
    filename << "data\\map\\";
    if(mGlobalX < 0) filename << "n";
    else filename << "p";
    filename << mGlobalX;
    if(mGlobalY < 0) filename << "n";
    else filename << "p";
    filename << mGlobalY;
    filename << ".txt";


    //map file system
    //# = 1 or 0, 1 = discovered, 0 = undiscovered
    //# = count of map deltas
    // (if map deltas exist...)
    //x:y:tile  = x and y position and new tile number
    //# = item count
    // (if items exist)
    //id:x:y:item_type_generic: // generic item
    //id:x:y:item_type_drink:volume: // drink with no volume
    //id:x:y:item_type_drink:volume:liquid_type
    //# = mob count
    //mobID:xpos:ypos


    std::ofstream mapsave;
    mapsave.open(filename.str().c_str());
    {
        //save discovered flag
        if(mDiscovered) mapsave << 1 << std::endl;
        else mapsave << 0 << std::endl;

        //record map deltas count
        mapsave << mMapDelta.size() << std::endl;

        for(int i = 0; i < int(mMapDelta.size()); i++)
        {

            mapsave << mMapDelta[i][0] << ":";
            mapsave << mMapDelta[i][1] << ":";
            mapsave << mMapDelta[i][2] << std::endl;
        }

        //save item count
        mapsave << mMapItems.size() << std::endl;
        //save map items
        for(int i = 0; i < int(mMapItems.size()); i++)
        {
            //as item types become more defined, more data will need to be saved
            mapsave << mMapItems[i]->getID() << ":";

            //save item location data
            mapsave << mMapItems[i]->getX() << ":";
            mapsave << mMapItems[i]->getY() << ":";

            //save item type data
            if(mMapItems[i]->isDrink())
            {
                mapsave << I_DRINK << ":";
                if(mMapItems[i]->getDrink() == NULL) mapsave << "0:" << std::endl;
                else
                {
                    mapsave << mMapItems[i]->getDrink()->current_volume << ":";
                    mapsave << mMapItems[i]->getDrink()->liquid << ":" << std::endl;
                }

            }
            else
            {
                mapsave << I_GEN << ":" << std::endl;
            }


        }

        //save map mob count
        int mob_count = mMapMobs.size();
        mapsave << mob_count << std::endl;

        for(int i = 0; i < mob_count; i++)
        {
            //save id
            mapsave << mMapMobs[i]->getID() << ":";

            //save position
            mapsave << mMapMobs[i]->getX() << ":";
            mapsave << mMapMobs[i]->getY() << std::endl;
        }
    }

    mapsave.close();
}

void Map::loadMap()
{
    //clear map deltas
    for(int i = 0; i < int(mMapDelta.size()); i++)
    {
        mMapDelta[i].clear();

    }
    mMapDelta.clear();

    //generate filename
    std::stringstream filename;
    //add directory
    filename << "data\\map\\";
    if(mGlobalX < 0) filename << "n";
    else filename << "p";
    filename << mGlobalX;
    if(mGlobalY < 0) filename << "n";
    else filename << "p";
    filename << mGlobalY;
    filename << ".txt";


    std::ifstream mapsave;
    mapsave.open(filename.str().c_str());


    if(!mapsave.is_open()) return;
    {
        int map_delta_count = 0;
        int map_item_count = 0;
        int map_mob_count = 0;

        //get map discovered
        if(!mapsave.eof())
        {
            char buf[20];
            mapsave.getline(buf,20);
            if(atoi(buf) == 1) mDiscovered = true;
            else mDiscovered = false;

        }

        //get map deltas count
        if(!mapsave.eof())
        {
            char buf[20];
            mapsave.getline(buf,20);
            map_delta_count = atoi(buf);

        }

        //get deltas
        for(int i = 0; i < map_delta_count; i++)
        {

            int x;
            int y;
            int tile;

            char buf[20];

            mapsave.getline(buf,20, ':');
            x = atoi(buf);
            if(mapsave.eof()) break;
            mapsave.getline(buf,20, ':');
            y = atoi(buf);
            if(mapsave.eof()) break;
            mapsave.getline(buf,20);
            tile = atoi(buf);

            std::vector<int> temparray;
            temparray.push_back(x);
            temparray.push_back(y);
            temparray.push_back(tile);

            mMapDelta.push_back(temparray);
        }
        if(int(mMapDelta.size()) != map_delta_count)
        {
            mapsave.close();
            printError("Map deltas in save do not match up!");
            return;
        }

        //load map items
        //get map item count
        if(!mapsave.eof())
        {
            char buf[20];
            mapsave.getline(buf,20);
            map_item_count = atoi(buf);
        }
        //load each map item id,x,y
        for(int i = 0; i < map_item_count; i++)
        {
            if(!mapsave.eof())
            {
                int item_id;
                int item_type;
                int item_x;
                int item_y;

                //get item id
                char b_id[20];
                mapsave.getline(b_id,20, ':');
                item_id = atoi(b_id);

                //get item x pos
                char b_x[20];
                mapsave.getline(b_x,20, ':');
                item_x = atoi(b_x);

                //get item y pos
                char b_y[20];
                mapsave.getline(b_y,20, ':');
                item_y = atoi(b_y);

                //get item type
                char b_type[20];
                mapsave.getline(b_type, 20, ':');
                item_type = atoi(b_type);

                //create item
                ItemRef *temp = new ItemRef( &(*mItemList)[item_id]);
                temp->setPos(item_x, item_y);

                if(item_type == I_DRINK)
                {
                    char b_vol[20];
                    mapsave.getline(b_vol, 20, ':');

                    //if drink has volume and liq assigned
                    if(atoi(b_vol) > 0)
                    {
                        //create drink ref
                        Item_DrinkRef *newdrink = new Item_DrinkRef;

                        newdrink->current_volume = atoi(b_vol);

                        char b_liq[20];
                        mapsave.getline(b_liq,20,':');
                        newdrink->liquid = atoi(b_liq);

                        temp->setDrink(newdrink);

                        mapsave.get();
                    }
                    else //if drink is empty
                    {
                        mapsave.get();
                    }

                }
                else //if gen item
                {
                    mapsave.get();
                }



                mMapItems.push_back(temp);


            }
        }

        //get mob count
        char b_mobcount[20];
        mapsave.getline(b_mobcount, 20);
        map_mob_count = atoi(b_mobcount);

        //load mobs
        for(int i = 0; i < map_mob_count; i++)
        {
            int m_id;
            int m_x;
            int m_y;

            //get mob id
            char b_mid[20];
            mapsave.getline(b_mid,20, ':');
            m_id = atoi(b_mid);

            //get x pos
            char b_x[20];
            mapsave.getline(b_x, 20, ':');
            m_x = atoi(b_x);

            //get y pos
            char b_y[20];
            mapsave.getline(b_y, 20);
            m_y = atoi(b_y);

            //create mobref
            MobRef *tmob = new MobRef( &(*mMobList)[m_id] );
            tmob->setPos(m_x, m_y);
            tmob->setGlobalPos(mGlobalX, mGlobalY);

            //add to map mobs
            mMapMobs.push_back(tmob);



        }




    }

    mapsave.close();
}

///// DEBUG STUFF

void Map::debugDig(int x, int y)
{
    setTile(x,y,9);
}

void Map::debugFill(int seed)
{

    seed += mGlobalX * mGlobalY;

    srand(seed);

    for(int i = 0; i < MAP_HEIGHT; i++)
    {
        for(int n = 0; n < MAP_WIDTH; n++)
        {getch();
            mMapArray[i][n] = rand()%5 + 1;
        }
    }

}

void Map::debugClearDeltas()
{
    mMapDelta.clear();
}
