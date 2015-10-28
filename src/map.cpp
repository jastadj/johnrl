#include "map.hpp"

#include <string>
#include <iostream>

#include "engine.hpp"

///////////////////////////////////////////////////////////////
// MAP TILE
MapTile::MapTile()
{

    m_Liquid = NULL;
}

MapTile::~MapTile()
{

}

bool MapTile::setLiquid(Liquid *nliquid)
{
    if(nliquid == NULL) return false;

    m_Liquid = nliquid;

    return true;
}

///////////////////////////////////////////////////////////////
// MAP CHUNK
MapChunk::MapChunk(int width, int height)
{
    //resize array
    m_MapData.resize(height);
    for(int i = 0; i < int(m_MapData.size()); i++) m_MapData[i].resize(width);

    //fillMap(1);
    for(int i = 0; i < int(m_MapData.size()); i++)
    {
        for(int n = 0; n < int(m_MapData[0].size()); n++)
        {
            setTileRandom(n, i, 3, 12);
        }
    }

    //add some water tiles
    for(int i = 0; i < 10; i++) setTile(rand()%MAPWIDTH, rand()%MAPHEIGHT, 13);

}

MapChunk::~MapChunk()
{
    //delete monsters
    for(int i = 0; i < int(m_MapMonsters.size()); i++) delete m_MapMonsters[i];
    m_MapMonsters.clear();
}

sf::Vector2i MapChunk::getDimensions()
{
    if(m_MapData.empty())
    {
        std::cout << "Error getting map dimensions, map data is empty!\n";
        return sf::Vector2i(0,0);
    }

    else return sf::Vector2i( int(m_MapData[0].size()), int(m_MapData.size()) );
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

void MapChunk::setTile(int x, int y, int tileid)
{
    if(!mapDataValid(x,y))
    {
        std::cout << "Error setting map tile, map position " << x << "," << y << " is not valid!\n";
        return;
    }

    else m_MapData[y][x] = tileid;
}

void MapChunk::fillMap(int tileid)
{
    for(int i = 0; i < int(m_MapData.size()); i++)
    {
        for(int n = 0; n < int(m_MapData[0].size()); n++)
        {
            m_MapData[i][n] = tileid;
        }
    }
}

sf::Vector2i MapChunk::getRandomValidPosition()
{
    sf::Vector2i mapdim = getDimensions();

    return sf::Vector2i(rand()%mapdim.x, rand()%mapdim.y);
}

void MapChunk::setTileRandom(int x, int y, int tileidstart, int tileidend)
{
    if(!mapDataValid(x, y))
    {
        std::cout << "Error setting map tile random, map position " << x << "," << y << " is not valid!\n";
        return;
    }

    m_MapData[y][x] = rand()%(tileidend - tileidstart + 1) + tileidstart;
}

bool MapChunk::addMonster(int monsterid, int x, int y)
{
    Engine *eptr = NULL;
    eptr = Engine::getInstance();

    if(monsterid < 0 || monsterid >= eptr->getMonsterDBSize())
    {
        std::cout << "Error adding monster to map, monster id outsize of bounds.  Id = " << monsterid << std::endl;
        std::cout << "Total monsters in DB list : " << eptr->getMonsterDBSize() << std::endl;
        return false;
    }

    Monster *newmonster = NULL;
    //*newmonster = eptr->copyMonsterFromDB(monsterid);
    newmonster = eptr->createMonster(monsterid);

    newmonster->setPosition(x, y);

    m_MapMonsters.push_back(newmonster);


    return true;
}

bool MapChunk::addMonster(int monsterid, sf::Vector2i pos)
{
    return addMonster(monsterid, pos.x, pos.y);
}

bool MapChunk::addItem(int itemid, int x, int y)
{
    Engine *eptr = NULL;
    eptr = Engine::getInstance();

    if(itemid < 0 || itemid >= eptr->getItemDBSize())
    {
        std::cout << "Error in adding item to map : itemid not within valid range : " << itemid << std::endl;
        return false;
    }

    Item *newitem = eptr->createItem(itemid);

    m_MapItems.push_back(newitem);

    return true;

}

bool MapChunk::addItem(int itemid, sf::Vector2i ipos)
{
    return addItem(itemid, ipos.x, ipos.y);
}
