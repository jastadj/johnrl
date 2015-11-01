#ifndef CLASS_ITEM
#define CLASS_ITEM

#include "gameobj.hpp"

//NOTE : when creating new item types, need to modify engine::createitem,

//ABSTRACT
class Item:public GameObj
{
private:
    int m_Weight;
    int m_Encumbrance;
    int m_Value;

    int m_ItemID; // do not change, this gets set during init time
public:
    Item();
    virtual ~Item();

    virtual int getType()=0;
    int getItemID() { return m_ItemID;}
    void setItemID(int nid) { m_ItemID = nid;} // do not use!

    //virtual int getFGColor();

    int getWeight() { return m_Weight;}
    int getEncumbrance() { return m_Encumbrance;}
    int getValue() { return m_Value;}

    void setWeight(int nweight) { m_Weight = nweight;}
    void setEncumbrance(int nenc) { m_Encumbrance = nenc;}
    void setValue(int nvalue) { m_Value = nvalue;}

    std::vector<std::string> saveItemDataToString();

};

class MiscItem:public Item
{
private:

public:
    MiscItem();
    ~MiscItem();

    int getType() { return OBJ_ITEM_MISC;}

    std::vector<std::string> saveDataToString();
};

#endif // CLASS_ITEM
