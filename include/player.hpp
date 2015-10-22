#ifndef CLASS_PLAYER
#define CLASS_PLAYER

#include "actor.hpp"

class Player: public Actor
{
private:

public:
    Player();
    ~Player();

    int getType() { return OBJ_PLAYER;}
};
#endif // CLASS_PLAYER
