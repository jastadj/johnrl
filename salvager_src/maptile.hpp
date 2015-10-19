#ifndef CLASS_MAPTILE
#define CLASS_MAPTILE

#include <string>

#include <curses.h>

class MapTile
{
private:

public:
    MapTile();

    std::string mName;

    chtype mIcon;
    int mColor;
    bool mBright;
    bool mPassable;

};
#endif // CLASS_MAPTILE
