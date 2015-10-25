#ifndef CLASS_PLAYER
#define CLASS_PLAYER

#include "actor.hpp"

class Player: public Actor
{
private:

    int m_TurnCounter;

public:
    Player();
    ~Player();

    int getType() { return OBJ_PLAYER;}

    int getTurns() { return m_TurnCounter;}
};
#endif // CLASS_PLAYER
