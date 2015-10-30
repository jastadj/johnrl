#ifndef CLASS_ACTOR
#define CLASS_ACTOR

#include "gameobj.hpp"
#include "itemtypes.hpp"


//ABSTRACT
class Actor: public GameObj
{
protected:

    int m_HealthMax;
    int m_HealthCurrent;

    std::vector<Item*> m_Inventory;

public:
    Actor();
    virtual ~Actor();
    virtual int getType()=0;

    //status
    virtual bool isAlive();
    int getMaxHealth() { return m_HealthMax;}
    void setMaxHealth(int nmaxhealth) { m_HealthMax = nmaxhealth;}
    int getCurrentHealth() { return m_HealthCurrent;}
    void setCurrentHealth(int ncurhealth) { m_HealthCurrent = ncurhealth;}


    //inventory
    std::vector< Item*> *getInventory() { return &m_Inventory;}
    void addToInventory(Item *titem) { m_Inventory.push_back(titem);}

    //actions
    bool walkDir(int direction);
};
#endif // CLASS_ACTOR
