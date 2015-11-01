#include "item.hpp"
#include <sstream>

Item::Item()
{
    m_Weight = 1;
    m_Encumbrance = 1;
    m_Value = 1;

    m_ItemID = -1;
}

Item::~Item()
{

}

std::vector<std::string> Item::saveItemDataToString()
{
    std::vector<std::string> savedata;

    std::stringstream sstr;
    sstr << "ADD_ITEM:" << m_ItemID << std::endl;
    savedata.push_back(sstr.str());

    sstr.str(std::string());

    sstr << "POSITION:" << m_Position.x << "," << m_Position.y << std::endl;
    savedata.push_back(sstr.str());

    return savedata;
}

//////////////////////////////////////////////////////////////////
MiscItem::MiscItem()
{

}

MiscItem::~MiscItem()
{

}

std::vector<std::string> MiscItem::saveDataToString()
{
    std::vector<std::string> savedata = saveItemDataToString();

    return savedata;
}
