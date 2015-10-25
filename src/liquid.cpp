#include "liquid.hpp"
#include <iostream>

Liquid::Liquid()
{
    m_Name = "unnamed";
    m_Color = COLOR_WHITE;
}

Liquid::~Liquid()
{


}

void Liquid::setColor(int ncolor)
{
    if(ncolor < 0 || ncolor >= COLOR_TOTAL)
    {
        std::cout << "Error setting liquid color.  Color out of bounds : " << ncolor << std::endl;
        return;
    }

    m_Color = ncolor;
}
