#ifndef CLASS_PLAYER
#define CLASS_PLAYER

#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "item.hpp"
#include "tools.hpp"

#define PLAYER_DRINK_AMT 2
class Player
{
private:

    //player position, local and global
    int mX;
    int mY;
    int mGlobalX;
    int mGlobalY;

    //player status
    int mTurns;
    float mTurnsPerHour;
    int mDay;
    float mHour;
    int mHydration;
    int mHydrationLossPH;
    int mCalories;
    int mCalorieBurnPH;


    //player display character
    char mIcon;

    //player inventory
    std::vector<ItemRef*> mInventory;


public:
    Player();

    //position
    int getX() { return mX;}
    int getY() { return mY;}
    int getGlobalX() { return mGlobalX;}
    int getGlobalY() { return mGlobalY;}
    void setPosition(int nx, int ny) {mX = nx; mY = ny;}
    void setGlobalPosition( int nx, int ny) { mGlobalX = nx; mGlobalY = ny;}

    //icon
    char getIcon() { return mIcon;}
    void setIcon( char nicon) {mIcon = nicon;}

    //inventory
    void addItem(ItemRef *newitem);
    std::vector< ItemRef* > *getInventory() { return &mInventory;}
    void removeItem(ItemRef *target);
    bool drink(ItemRef *target);

    //load/save
    void savePlayer();
    bool loadPlayer(std::vector<Item> *itemlist);

    //player status
    void increaseTurn();
    int getTurns() { return mTurns;}
    float getTurnsPerHour() { return mTurnsPerHour;}
    void setTurnsPerHour(float nturnsph) { mTurnsPerHour = nturnsph;}
    float getHour() { return mHour;}
    void setHour (float nhour) {mHour = nhour;}
    int getDay() { return mDay;}
    int getHydration() { return mHydration;}
    void setHydration(int nhyd) { mHydration = nhyd;}
    void setCalories(int ncal) { mCalories = ncal;}
    int getCalories() { return mCalories;}

    //debug
    void debug_viewInventory();

};
#endif // CLASS_PLAYER
