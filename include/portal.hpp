#ifndef CLASS_PORTAL
#define CLASS_PORTAL

#include "itemtypes.hpp"

//forward dec
class MapChunk;

class Portal:public Item
{
private:

    MapChunk *m_DestinationMap;
    sf::Vector2i m_DestinationPos;

public:
    Portal();
    ~Portal();
    std::vector<std::string> saveDataToString();

    int getType() {return OBJ_ITEM_PORTAL;}

    MapChunk *getDestinationMap() { return m_DestinationMap;}
    sf::Vector2i getDestinationPos() { return m_DestinationPos;}

    void setDestinationMap( MapChunk *tmap) { m_DestinationMap = tmap;}
    void setDestinationPos( sf::Vector2i tpos) { m_DestinationPos = tpos;}
};

#endif // CLASS_PORTAL
