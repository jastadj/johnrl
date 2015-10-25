#ifndef CLASS_ACTOR
#define CLASS_ACTOR

#include "gameobj.hpp"
#include "itemtypes.hpp"

class Actor: public GameObj
{
private:

    int m_HealthMax;
    int m_HealthCurrent;

    std::vector<Item*> m_Inventory;

public:
    Actor();
    virtual ~Actor();
    virtual int getType()=0;

    //status
    int getMaxHealth() { return m_HealthMax;}
    int getCurrentHealth() { return m_HealthCurrent;}

    //inventory
    std::vector< Item*> *getInventory() { return &m_Inventory;}
    void addToInventory(Item *titem) { m_Inventory.push_back(titem);}

    //actions
    bool walkDir(int direction);
};
#endif // CLASS_ACTOR
