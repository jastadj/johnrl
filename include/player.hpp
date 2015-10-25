#ifndef CLASS_PLAYER
#define CLASS_PLAYER

#include "actor.hpp"

class Player: public Actor
{
private:

    int m_TurnCounter;

    //hydration
    int m_MetabolismHydration;
    int m_HydrationLevel;
    int m_HydrationLevelMax;
    int m_HydrationTick;

public:
    Player();
    ~Player();

    int getType() { return OBJ_PLAYER;}

    bool isAlive();

    int getTurns() { return m_TurnCounter;}
    void doTurn();

    int getHydrationLevel() { return m_HydrationLevel;}
    void setHydrationLevel(int nhydlevel) { m_HydrationLevel = nhydlevel;}
    bool drink(Liquid *ltype);

};
#endif // CLASS_PLAYER
