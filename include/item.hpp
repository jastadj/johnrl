#ifndef CLASS_ITEM
#define CLASS_ITEM

#include "gameobj.hpp"

//NOTE : when creating new item types, need to modify engine::createitem,

class Item:public GameObj
{
private:
    int m_Weight;
    int m_Encumbrance;
    int m_Value;
public:
    Item();
    virtual ~Item();

    virtual int getType()=0;

    //virtual int getFGColor();

    int getWeight() { return m_Weight;}
    int getEncumbrance() { return m_Encumbrance;}
    int getValue() { return m_Value;}

    void setWeight(int nweight) { m_Weight = nweight;}
    void setEncumbrance(int nenc) { m_Encumbrance = nenc;}
    void setValue(int nvalue) { m_Value = nvalue;}
};

class MiscItem:public Item
{
private:

public:
    int getType() { return OBJ_ITEM_MISC;}
};

#endif // CLASS_ITEM
