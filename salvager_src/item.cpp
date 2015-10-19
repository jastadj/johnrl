#include "item.hpp"

Item::Item()
{

    mIcon = '?';
    mName = "unnamed";
    mColor = 0;
    mBright = false;
    mPassable = true;

    //item types
    mDrink = NULL;
    mFood = NULL;
}

ItemRef::ItemRef(Item *master)
{
    mRef = master;

    mX = 0;
    mY = 0;
    //not sure if global positions are really needed since items are stored in
    //each maps item vector?
    mGlobalX = 0;
    mGlobalY = 0;

    //item types
    mDrink = NULL;
}

void ItemRef::fillDrink(int ltype)
{
    //if its not a drink return
    if(!isDrink()) return;

    //does it currently have liquid in it?
    if( mDrink != NULL)
    {
        //is liquid the same type that is to be filled?
        if(mDrink->liquid == ltype)
        {
            mDrink->current_volume = mRef->mDrink->volume;
        }
    }
    else
    {
        mDrink = new Item_DrinkRef;
        mDrink->liquid = ltype;
        mDrink->current_volume = mRef->mDrink->volume;
    }

}

void ItemRef::setDrink( Item_DrinkRef *target)
{
    //if item is not even a drink, return
    if(!isDrink()) return;
    //if item has a drink assigned to it already, but trying to assign NULL
    //delete drink and assign NULL
    if(mDrink != NULL && target == NULL)
    {
        delete mDrink;
        mDrink = NULL;
        return;
    }
    //else if a drink is already assigned and trying to assign another drink, return
    else if(mDrink != NULL) return;

    //go ahead and assign the drink to the target drink reference
    mDrink = target;
}
