#include "container.hpp"
#include <iostream>
#include <sstream>

Container::Container()
{

}

Container::~Container()
{

}

std::vector<std::string> Container::saveDataToString()
{
    std::vector<std::string> savedata = saveItemDataToString();

    return savedata;
}

//////////////////////////////////////////////////////////

ContainerLiquid::ContainerLiquid()
{
    m_LiquidType = NULL;

    m_VolumeMax = 12;
    m_VolumeCurrent = 0;
}

ContainerLiquid::~ContainerLiquid()
{

}

std::vector<std::string> ContainerLiquid::saveDataToString()
{
    std::vector<std::string> savedata = saveItemDataToString();

    if(!isEmpty())
    {
        std::stringstream sstr;
        sstr << "ADD_LIQUID:" << getLiquidType()->getLiquidID() << "," << m_VolumeCurrent << std::endl;
        savedata.push_back(sstr.str());
    }

    return savedata;
}

int ContainerLiquid::getFGColor()
{
    if(!isEmpty()) return getLiquidType()->getColor();
    else return m_FGColor;
}

bool ContainerLiquid::addLiquid(Liquid *ltype, int lvol)
{
    if(ltype == NULL) return false;

    //can only add liquid if liquid in container is the same type
    if(ltype == m_LiquidType)
    {
        if(lvol + m_VolumeCurrent > m_VolumeMax)
        {
            std::cout << "Adding too much liquid to container.  Returning false for addliquid\n";
            return false;
        }

        m_VolumeCurrent += lvol;
        return true;
    }
}

bool ContainerLiquid::removeLiquid(int lvol)
{
    if(m_LiquidType == NULL) return false;

    if(lvol <= 0) return false;

    if(lvol > m_VolumeCurrent) return false;

    m_VolumeCurrent -= lvol;

    std::cout << "Removed " << lvol << " units of " << m_LiquidType->getName() << " from liquid container.\n";

    if(m_VolumeCurrent == 0)
    {
        std::cout << "No more volume of liquid type " << m_LiquidType->getName() << " in container.  Removing type...\n";

        m_LiquidType = NULL;
    }

    return true;
}

bool ContainerLiquid::fillWithLiquid(Liquid *ltype)
{
    if(ltype == NULL) return false;

    m_LiquidType = ltype;

    m_VolumeCurrent = m_VolumeMax;

    return true;
}

bool ContainerLiquid::isEmpty()
{
    if(m_VolumeCurrent == 0) return true;
    else return false;
}
