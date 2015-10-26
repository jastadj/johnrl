#ifndef CLASS_MAPCHUNK
#define CLASS_MAPCHUNK

#include <string>
#include <vector>
#include "gameobj.hpp"
#include "monster.hpp"

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

};

class MapChunk
{
private:

    std::vector < std::vector< int > > m_MapData;

    std::vector< Monster*> m_MapMonsters;

public:
    MapChunk(int width = MAPWIDTH, int height = MAPHEIGHT);
    ~MapChunk();

    bool mapDataValid(int x, int y);
    sf::Vector2i getDimensions();
    int getTile(int x, int y);
    void fillMap(int tileid);
    void setTile(int x, int y, int tileid);
    void setTileRandom(int x, int y, int tileidstart, int tileidend);
    sf::Vector2i getRandomValidPosition();

    bool addMonster(int monsterid, int x, int y);
    bool addMonster(int monsterid, sf::Vector2i pos);
    const std::vector< Monster*> *getMapMonsters() const { return &m_MapMonsters;}
};

#endif // CLASS_MAPCHUNK
