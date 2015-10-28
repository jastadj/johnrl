#ifndef CLASS_ITEM
#define CLASS_ITEM

#include "gameobj.hpp"

class Item:public GameObj
{
private:

public:
    Item();
    virtual ~Item();

    virtual int getType()=0;

    //virtual int getFGColor();
};


#endif // CLASS_ITEM
