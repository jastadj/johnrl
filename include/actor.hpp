#ifndef CLASS_ACTOR
#define CLASS_ACTOR

#include "gameobj.hpp"

class Actor: public GameObj
{
private:

    int m_HealthMax;
    int m_HealthCurrent;

public:
    Actor();
    virtual ~Actor();

    virtual int getType()=0;

    int getMaxHealth() { return m_HealthMax;}
    int getCurrentHealth() { return m_HealthCurrent;}

    bool walkDir(int direction);
};
#endif // CLASS_ACTOR
