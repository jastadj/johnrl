#include "map.hpp"

#include <string>
#include <iostream>

//map tiles
MapTile::MapTile()
{

}

MapTile::~MapTile()
{

}

///////////////////////////////////////////////////////////////
// MAP CHUNK
MapChunk::MapChunk()
{

}

MapChunk::~MapChunk()
{

}

bool MapChunk::mapDataValid(int x, int y)
{
    if(m_MapData.empty())
    {
        std::cout << "Error getting tile : Map data is empty!\n";
        return false;
    }
    else if(m_MapData[0].empty())
    {
        std::cout << "Error getting tile : Map data array has no width!\n";
        return false;
    }

    if(x < 0 || y < 0 || x >= int(m_MapData[0].size()) || y >= int(m_MapData.size()) )
    {
        std::cout << "Error getting tile : x,y is out of map data bounds!\n";
        return false;
    }

    return true;
}

int MapChunk::getTile(int x, int y)
{
    if(!mapDataValid(x, y)) return 0;

    else return m_MapData[y][x];
}
