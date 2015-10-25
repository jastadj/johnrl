#ifndef CLASS_CONTAINER
#define CLASS_CONTAINER

#include "item.hpp"

class Container:public Item
{
private:

public:
    Container();
    ~Container();

    int getType() {return OBJ_ITEM_CONTAINER;}
};
#endif // CLASS_CONTAINER
