#include "player.hpp"
#include <iostream>
#include "engine.hpp"

Player::Player()
{
    m_TileID = int('@');

    m_TurnCounter = 0;

    m_MetabolismHydration = 300;

    m_HydrationLevelMax = 10;
    m_HydrationLevel = 5;
    m_HydrationTick = 0;
}

Player::~Player()
{

}

bool Player::isAlive()
{
    if( m_HealthCurrent <= 0) return false;

    if( m_HydrationLevel < 0) return false;

    return true;
}

void Player::doTurn()
{
    m_TurnCounter++;

    //process hydration
    m_HydrationTick++;
    if(m_HydrationTick >= m_MetabolismHydration)
    {
        m_HydrationTick = 0;
        m_HydrationLevel--;
    }

    //update message que
    Engine *eptr = NULL;
    eptr = Engine::getInstance();
    eptr->playerTurnUpdates();

}

bool Player::drink(Liquid *ltype)
{
    if(ltype == NULL) return false;

    if(ltype->getName() == "water")
    {
        if(m_HydrationLevel == m_HydrationLevelMax)
        {
            std::cout << "Too hydrated to drink any more water!\n";
            return false;
        }

        m_HydrationTick = 0;
        m_HydrationLevel++;

        return true;

    }
}
