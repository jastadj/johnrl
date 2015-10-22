#ifndef CLASS_GAMEOBJ
#define CLASS_GAMEOBJ

#include <string>
#include "defs.hpp"



class GameObj
{
private:

    std::string m_Name;

    int m_TileID;
    int m_BGColor;
    int m_FGColor;

public:
    GameObj();
    virtual ~GameObj();

    virtual int getType()=0;

    std::string getName() { return m_Name;}
    int getTileID() { return m_TileID; }
    int getBGColor() { return m_BGColor;}
    int getFGColor() { return m_FGColor;}

    friend class Engine;
};
#endif // CLASS_GAMEOBJ
