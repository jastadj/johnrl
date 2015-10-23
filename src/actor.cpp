#include "actor.hpp"

#include <string>
#include <iostream>


Actor::Actor()
{
    m_HealthMax = 1;
    m_HealthCurrent = 1;
}

Actor::~Actor()
{

}

bool Actor::walkDir(int direction)
{
    sf::Vector2i newpos = m_Position;

    switch(direction)
    {
    case DIR_NONE:
        break;
    case DIR_SW:
        newpos.x--;
        newpos.y++;
        break;
    case DIR_SOUTH:
        newpos.y++;
        break;
    case DIR_SE:
        newpos.x++;
        newpos.y++;
        break;
    case DIR_WEST:
        newpos.x--;
        break;
    case DIR_SELF:
        break;
    case DIR_EAST:
        newpos.x++;
        break;
    case DIR_NW:
        newpos.x--;
        newpos.y--;
        break;
    case DIR_NORTH:
        newpos.y--;
        break;
    case DIR_NE:
        newpos.x++;
        newpos.y--;
        break;
    default:
        std::cout << "Unable to walk in undefined direction!  dir = " << direction << std::endl;
        break;
    }

    m_Position = newpos;
}
