#include "actor.hpp"
#include "player.hpp"

#include <string>
#include <iostream>

#include "engine.hpp"

Actor::Actor()
{
    m_HealthMax = 1;
    m_HealthCurrent = 1;
}

Actor::~Actor()
{

}

bool Actor::isAlive()
{
    if(m_HealthCurrent <= 0) return false;

    return true;
}

/*
bool Actor::walkDir(int direction, bool canLeaveMap)
{
    Engine *eptr = NULL;
    eptr = Engine::getInstance();

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

    //check that newpos is a valid walkable tile
    if(!eptr->validWalkableTile(newpos.x, newpos.y))
    {
        //if actor is able to leave the map, then check if newpos is outside map
        if(canLeaveMap)
        {

        }
        else return false;
    }

    m_Position = newpos;

    //if moving player, increase turn
    if(this->getType() == OBJ_PLAYER)
    {
        //show what items are here at new pos?

        Player *tactor = NULL;
        tactor = dynamic_cast<Player*>(this);
        if(tactor != NULL) tactor->doTurn();

        //set turn counter to true

    }

    return true;
}
*/
