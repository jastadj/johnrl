#ifndef CLASS_ITEM
#define CLASS_ITEM

#include <string>
#include <curses.h>

enum I_TYPE{I_GEN, I_DRINK};

//hydration table needs to be updated as new liquid are added
enum I_LIQUID{L_WATER, L_BEER};
const int LIQ_TABLE[2][2] ={ { L_WATER, 10},{ L_BEER , 2} };

//const int LIQ_HYDRATION[][] = {}

struct Item_Drink
{
    int volume;
};

struct Item_Food
{
    int calories;
};

struct Item_DrinkRef
{
    int liquid;
    int current_volume;
};

class Item
{

public:
    Item();

    //item properties
    int mID;
    chtype mIcon;
    std::string mName;
    int mColor;
    bool mBright;
    bool mPassable;

    //item types
    Item_Drink *mDrink;
    Item_Food *mFood;

    bool isDrink() { if(mDrink != NULL) return true; else return false;}
    bool isFood() { if(mFood != NULL) return true; else return false;}


};

class ItemRef
{
private:
    Item *mRef;

    int mX;
    int mY;
    int mGlobalX;
    int mGlobalY;

    Item_DrinkRef *mDrink;

public:
    ItemRef( Item *master);
    Item *getRef() { return mRef;}

    int getID() { return mRef->mID;}

    chtype getIcon() { return mRef->mIcon;}
    std::string getName() { return mRef->mName;}
    bool getBright() { return mRef->mBright;}
    int getColor() { return mRef->mColor;}
    bool getPassable() { return mRef->mPassable;}

    //drink
    bool isDrink() { return mRef->isDrink();}
    Item_DrinkRef *getDrink() { return mDrink;}
    void fillDrink(int ltype); // fill an empty drink with type
    void setDrink( Item_DrinkRef *target); // set the drink liquid and volume to a drinkref

    //food
    bool isFood() { return mRef->isFood();}

    int getX() { return mX;}
    int getY() { return mY;}
    int getGlobalX() { return mGlobalX;}
    int getGlobalY() { return mGlobalY;}

    void setPos(int x, int y) { mX = x; mY = y;}
    void setGlobalPos(int x, int y) { mGlobalX = x; mGlobalY = y;}


};
#endif // CLASS_ITEM
