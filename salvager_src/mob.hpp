#ifndef CLASS_MOB
#define CLASS_MOB

#include <cstdlib>
#include <string>
#include <curses.h>

enum {AI_NONE, AI_WANDER};

class Mob
{
public:
    std::string mName;
    chtype mIcon;
    int mID;
    int mDefaultBehavior;

    Mob();
    ~Mob();
};

class MobRef
{
private:
    Mob *mRef;

    int mX;
    int mY;
    int mGlobalX;
    int mGlobalY;

public:
    MobRef(Mob *nref);
    ~MobRef();

    Mob *getRef() { return mRef;}
    std::string getName() { return mRef->mName;}
    chtype getIcon() { return mRef->mIcon;}
    int getID() { return mRef->mID;}
    int getDefaultBehavior() { return mRef->mDefaultBehavior;}

    int getX() { return mX;}
    int getY() { return mY;}
    int getGlobalX() { return mGlobalX;}
    int getGlobalY() { return mGlobalY;}
    void setPos(int nx, int ny) { mX = nx; mY = ny;}
    void setGlobalPos(int nx, int ny) { mGlobalX = nx; mGlobalY = ny;}

};

#endif // CLASS_MOB
