#ifndef CLASS_PLAYER
#define CLASS_PLAYER

#include "actor.hpp"

class Player: public Actor
{
private:

    int m_TurnCounter;

    //relative position 0,0 for world map noise
    sf::Vector2i m_NoisePosRel0;
    sf::Vector2i m_GlobalPos;

    //hydration
    int m_MetabolismHydration;
    int m_HydrationLevel;
    int m_HydrationLevelMax;
    int m_HydrationTick;

public:
    Player();
    ~Player();

    int getType() { return OBJ_PLAYER;}

    sf::Vector2i getNoisePosRel0() { return m_NoisePosRel0;}
    sf::Vector2i getGlobalPos() { return m_GlobalPos;}

    bool isAlive();

    int getTurns() { return m_TurnCounter;}
    void doTurn();

    int getHydrationLevel() { return m_HydrationLevel;}
    int getMaxHydrationLevel() { return m_HydrationLevelMax;}
    void setHydrationLevel(int nhydlevel) { m_HydrationLevel = nhydlevel;}
    bool drink(Liquid *ltype);

    std::vector<std::string> saveDataToString();

};
#endif // CLASS_PLAYER
