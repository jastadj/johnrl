#include "map.hpp"

#include <string>
#include <iostream>
#include <fstream>

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
MapChunk::MapChunk(int nglobalx, int nglobaly, int width, int height)
{
    //set global position
    m_GlobalX = nglobalx;
    m_GlobalY = nglobaly;

    //reset seed
    Engine *eptr = NULL;
    eptr = Engine::getInstance();
    srand(eptr->getSeed());

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

    //add lakes
    //for(int i = 0; i < 10; i++) setTile(rand()%MAPWIDTH, rand()%MAPHEIGHT, 13);
    for(int i = 0; i < 5; i++) genLake(25);

    //add random trees
    genTrees(100);

}

MapChunk::~MapChunk()
{
    //delete monsters
    for(int i = 0; i < int(m_MapMonsters.size()); i++) delete m_MapMonsters[i];
    m_MapMonsters.clear();

    //delete items
    for(int i = 0; i < int(m_MapItems.size()); i++) delete m_MapItems[i];
    m_MapItems.clear();
}

bool MapChunk::save()
{

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

std::vector< Item*> MapChunk::getMapItemsAtTile(int x, int y)
{
    std::vector< Item*> founditems;

    sf::Vector2i tpos(x,y);

    for(int i = 0; i < int(m_MapItems.size()); i++)
    {

        if(m_MapItems[i]->getPosition() == tpos) founditems.push_back( m_MapItems[i]);
    }

    return founditems;
}

///////////////////////////////////////////////////////////////////////////////////////////////
void MapChunk::genLake(int lakesize)
{
    Engine *eptr = NULL;
    eptr = Engine::getInstance();

    //noise settings
    float scale = 9;
    float octaves = 6;
    float persistence = 0.7;

    //noise mask
    int threshold = 60;
    float maskintensity = 1.f; // percentage 1.0 = 100%
    sf::Vector2i mcenter(lakesize/2, lakesize/2);
    float centerdistance = getDistance(0,0, mcenter.x, mcenter.y);
    //float gradientdist = centerdistance * maskintensity;
    float scaler = 255.f / centerdistance;


    //sf::Vector2i noiserel0 = eptr->getNoiseRelPosition0();
    //sf::Vector2i globalpos = eptr->getGlobalPosition();

    std::vector< std::vector<int> > noisemap = eptr->genNoise(lakesize, lakesize, rand()%2000, rand()%2000, persistence, octaves, scale);
    std::vector< std::vector<int> > maskmap;

    //create mask map
    maskmap.resize(lakesize);
    for(int i = 0; i < lakesize; i++)
    {
        for(int n = 0; n < lakesize; n++) maskmap[i].push_back(0);
    }

    //creat mask map gradient
    for(int i = 0; i < lakesize; i++)
    {
        for(int n = 0; n < lakesize; n++)
        {
            //if(getDistance(mcenter.x, mcenter.y, n, i) > gradientdist)
            maskmap[i][n] = getDistance(mcenter.x, mcenter.y, n, i) * scaler;
        }
    }

    //apply mask to noise map
    for(int i = 0; i < lakesize; i++)
    {
        for(int n = 0; n < lakesize; n++)
        {
            noisemap[i][n] -= maskmap[i][n];

            if(noisemap[i][n] < threshold) noisemap[i][n] = 0;
            else noisemap[i][n] = 255;
        }
    }

    //replace 255 values with water tile
    //apply mask to noise map
    for(int i = 0; i < lakesize; i++)
    {
        for(int n = 0; n < lakesize; n++)
        {
            if(noisemap[i][n] == 255) noisemap[i][n] = 13;//eptr->getMapTile(13)->getTileID();
        }
    }

    //trim off empty rows columns
    sf::Vector2i tl(lakesize-1, lakesize-1);
    sf::Vector2i br(0,0);
    //top left trim
    for(int i = 0; i < lakesize; i++)
    {
        for(int n = 0; n < lakesize; n++)
        {
            if(noisemap[i][n] == 13)
            {
                if( i < tl.y) tl.y = i;
                if( n < tl.x) tl.x = n;
            }
        }
    }
    //bottom right trim
    for(int i = lakesize-1; i >= 0; i--)
    {
        for(int n = lakesize-1; n >= 0; n--)
        {
            if(noisemap[i][n] == 13)
            {
                if( i > br.y) br.y = i;
                if( n > br.x) br.x = n;
            }
        }
    }

    std::cout << "tl.y = " << tl.y << " tl.x = " << tl.x << " br.y = " << br.y << " br.x = " << br.x << std::endl;
    //transfer trimmed noise map to lakemap
    std::vector< std::vector<int> > lakemap;
    for(int i = tl.y; i <= br.y; i++)
    {
        lakemap.resize( lakemap.size()+1);

        for(int n = tl.x; n <= br.x; n++)
        {
            lakemap[lakemap.size()-1].push_back( noisemap[i][n]);
        }
    }

    if(lakemap.empty())
    {
        std::cout << "Error generating a lake.  Lake map is empty!\n";
        return;
    }

    sf::IntRect lakedim;
    lakedim.width = int(lakemap[0].size()-1);
    lakedim.height = int(lakemap.size()-1);
    //randomize lake position
    lakedim.left = rand()%getDimensions().x;
    lakedim.top = rand()%getDimensions().y;

    //transfer lake map to map data
    for(int i = 0; i < lakesize; i++)
    {
        for(int n = 0; n < lakesize; n++)
        {
            if(noisemap[i][n] == 13)
            {
                if(n + lakedim.left < 0 || n + lakedim.left >= getDimensions().x || i + lakedim.top < 0 || i + lakedim.top >= getDimensions().y) continue;
                m_MapData[i+lakedim.top][n+lakedim.left] = 13;//eptr->getMapTile(13)->getTileID();
            }
        }
    }

}

void MapChunk::genTrees(int density)
{
    for(int i = 0; i < density; i++)
    {
        sf::Vector2i rpos(rand()%MAPWIDTH, rand()%MAPHEIGHT);

        //check that tile is grass, then put tree there
        if( m_MapData[rpos.y][rpos.x] >= 3 && m_MapData[rpos.y][rpos.x] <= 12)
        {
            m_MapData[rpos.y][rpos.x] = 14;
        }
    }
}
