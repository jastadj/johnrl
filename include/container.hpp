#ifndef CLASS_CONTAINER
#define CLASS_CONTAINER

#include "itemtypes.hpp"

class Container:public Item
{
protected:

    std::vector< Item*> m_Inventory;

public:
    Container();
    ~Container();

    virtual int getType() {return OBJ_ITEM_CONTAINER;}
    //virtual int getFGColor();

    virtual std::vector< Item*> *getInventory() { return &m_Inventory;}
    virtual std::vector<std::string> saveDataToString();
};

class ContainerLiquid:public Item
{
private:

    int m_VolumeMax;
    int m_VolumeCurrent;

    Liquid *m_LiquidType;

public:
    ContainerLiquid();
    ~ContainerLiquid();

    int getType() {return OBJ_ITEM_CONTAINER_LIQUID;}
    Liquid *getLiquidType() { return m_LiquidType;}

    int getFGColor();

    int getMaxVolume() { return m_VolumeMax;}
    void setMaxVolume(int nmaxvol) { m_VolumeMax = nmaxvol;}
    int getCurrentVolume() { return m_VolumeCurrent;}
    void setCurrentVolume( int ncurvol) { m_VolumeCurrent = ncurvol;}

    bool addLiquid(Liquid *ltype, int lvol);
    bool removeLiquid(int lvol);
    bool fillWithLiquid(Liquid *ltype);
    bool isEmpty();

    std::vector<std::string> saveDataToString();
};
#endif // CLASS_CONTAINER
