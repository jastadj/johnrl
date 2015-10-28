#include "container.hpp"
#include <iostream>

Container::Container()
{

}

Container::~Container()
{

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
