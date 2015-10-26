#include "gameobj.hpp"

GameObj::GameObj()
{
    m_Name = "unnamed";
    m_BGColor = COLOR_BLACK;
    m_FGColor = COLOR_WHITE;
    m_TileID = 63;

    m_Walkable = true;
}

GameObj::~GameObj()
{

}
