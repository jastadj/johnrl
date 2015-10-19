#ifndef CLASS_MAP
#define CLASS_MAP

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

#include "item.hpp"
#include "tools.hpp"
#include "perlin.hpp"
#include "mob.hpp"


const int MAP_WIDTH = 64;
const int MAP_HEIGHT = 64;

class Map
{

private:
    std::vector< std::vector<int> > mMapArray;

    std::vector< std::vector<int> > mMapDelta;

    std::vector< ItemRef* > mMapItems;
    std::vector< Item > *mItemList;
    std::vector< MobRef* > mMapMobs;
    std::vector< Mob > *mMobList;


    int mGlobalX;
    int mGlobalY;

    bool mDiscovered;

    int mSeed;

public:
    Map(int x, int y, int seed);
    ~Map();

    //get map dimensions
    int getWidth() { return mMapArray[0].size();}
    int getHeight() { return mMapArray.size();}

    //global position
    int getGlobalX() { return mGlobalX;}
    int getGlobalY() { return mGlobalY;}

    //get and set tile at x,y
    int getTile(int x, int y);
    void setTile(int x, int y, int tile); // only sets map delta tile

    //fill map with a number (tile)
    void fillMap(int tile);

    //generation
    void genGrass();

    //items
    void setItemReference(std::vector<Item> *itemlist) { mItemList = itemlist;}
    void addItem(int x, int y, ItemRef *target);
    void removeItem(ItemRef *target);
    std::vector< ItemRef* > *getMapItems() {return &mMapItems;}

    //mobs
    void setMobReference(std::vector<Mob> *moblist) { mMobList = moblist;}
    std::vector< MobRef* > *getMapMobs() { return &mMapMobs;}
    void addMob( MobRef *tmob, int x, int y );
    void removeMob(MobRef *tmob);

    //load/saving map
    void saveMap();
    void loadMap();

    //discovery
    //the discovered flag is set to true when the map is being saved
    //when loading, if the flag isnt set in the map file, the map is flagged as not discovered
    //this can be handy when using to generate map items etc... as a one time item generation mechanism
    bool getDiscovered() { return mDiscovered;}
    void setDiscovered(bool ndiscovered) { mDiscovered = ndiscovered;}

    //debug
    void debugFill(int seed);
    void debugDig(int x, int y);
    void debugClearDeltas();

};
#endif // CLASS_MAP
