#ifndef CLASS_MONSTER
#define CLASS_MONSTER

#include "actor.hpp"

class Monster: public Actor
{
private:

public:
    Monster();
    ~Monster();

    int getType() { return OBJ_MONSTER;}

    std::vector<std::string> saveDataToString();
};
#endif // CLASS_MONSTER
