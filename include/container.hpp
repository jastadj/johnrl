#ifndef CLASS_CONTAINER
#define CLASS_CONTAINER

#include "itemtypes.hpp""

class Container:public Item
{
private:

    std::vector< Item*> m_Inventory;

public:
    Container();
    ~Container();

    int getType() {return OBJ_ITEM_CONTAINER;}

    std::vector< Item*> *getInventory() { return &m_Inventory;}

};
#endif // CLASS_CONTAINER
