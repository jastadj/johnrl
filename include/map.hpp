#ifndef CLASS_MAPCHUNK
#define CLASS_MAPCHUNK

#include <string>
#include <vector>
#include "gameobj.hpp"
#include "monster.hpp"
#include "itemtypes.hpp"

class MapTile: public GameObj
{
private:

    Liquid *m_Liquid;

public:
    MapTile();
    ~MapTile();

    int getType() { return OBJ_MAPTILE;}

    bool setLiquid(Liquid *nliquid);
    Liquid *getLiquid() { return m_Liquid;}
    bool hasLiquid() { if(m_Liquid != NULL) return true;  else return false;}

    std::vector<std::string> saveDataToString() {};

};

class MapChunk
{
private:

    std::vector < std::vector< int > > m_MapData;
    std::vector < std::vector< bool > > m_MapDataExplored;

    std::vector< Monster*> m_MapMonsters;
    std::vector< Item*> m_MapItems;

    //connected maps
    std::vector< MapChunk*> m_AdjacentMaps;
    bool hasAdjacent(int direction);
    bool connectAdjacent(int direction, MapChunk *tmap);

    int m_GlobalX;
    int m_GlobalY;

    //procedural generation
    void genLake(int lakesize);
    void genTrees(int density);

public:
    MapChunk(int nglobalx, int nglobaly, int width = MAPWIDTH, int height = MAPHEIGHT);
    ~MapChunk();

    sf::Vector2i getGlobalPos() { return sf::Vector2i(m_GlobalX, m_GlobalY);}

    bool save();

    bool mapDataValid(int x, int y);
    sf::Vector2i getDimensions();
    int getTile(int x, int y);
    void fillMap(int tileid);
    void setTile(int x, int y, int tileid);
    void setTileRandom(int x, int y, int tileidstart, int tileidend);
    sf::Vector2i getRandomValidPosition();
    bool tileExplored(int x, int y);
    void setExplored(int x, int y, bool isexplored);

    bool addMonster(int monsterid, int x, int y);
    bool addMonster(int monsterid, sf::Vector2i pos);
    std::vector< Monster*> *getMapMonsters() { return &m_MapMonsters;}

    bool addItem(int itemid, int x, int y);
    bool addItem(int itemid, sf::Vector2i ipos);
    std::vector< Item*> *getMapItems() { return &m_MapItems;}
    std::vector< Item*> getMapItemsAtTile(int x, int y);
};

#endif // CLASS_MAPCHUNK
