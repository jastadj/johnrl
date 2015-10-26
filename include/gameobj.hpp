#ifndef CLASS_GAMEOBJ
#define CLASS_GAMEOBJ

#include <SFML/Graphics.hpp>
#include <string>
#include "defs.hpp"



class GameObj
{
protected:

    std::string m_Name;

    int m_TileID;
    int m_BGColor;
    int m_FGColor;

    bool m_Walkable;

    sf::Vector2i m_Position;

public:
    GameObj();
    virtual ~GameObj();

    virtual int getType()=0;

    std::string getName() { return m_Name;}
    int getTileID() { return m_TileID; }
    int getBGColor() { return m_BGColor;}
    int getFGColor() { return m_FGColor;}

    sf::Vector2i getPosition() { return m_Position;}
    void setPosition(sf::Vector2i newpos) { m_Position = newpos;}
    void setPosition(int x, int y) { m_Position = sf::Vector2i(x, y);}

    void setWalkable(bool nwalk) { m_Walkable = nwalk;}
    bool isWalkable() { return m_Walkable;}

    friend class Engine;
};
#endif // CLASS_GAMEOBJ
