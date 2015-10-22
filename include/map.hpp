#ifndef CLASS_MAPCHUNK
#define CLASS_MAPCHUNK

#include <string>
#include <vector>
#include "gameobj.hpp"

class MapTile: public GameObj
{
private:

public:
    MapTile();
    ~MapTile();

    int getType() { return OBJ_MAPTILE;}
};

class MapChunk
{
private:

    std::vector < std::vector< int > > m_MapData;

public:
    MapChunk();
    ~MapChunk();

    bool mapDataValid(int x, int y);

    int getTile(int x, int y);
    void setTile(int x, int y, int tileid);

    void fillMap(int tileid);
};

#endif // CLASS_MAPCHUNK
