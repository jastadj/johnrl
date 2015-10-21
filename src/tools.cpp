#include "tools.hpp"


void replaceImageColor(sf::Image *timage, sf::Color scolor, sf::Color dcolor)
{
    int x = timage->getSize().x;
    int y = timage->getSize().y;

    for(int i = 0; i < y; i++)
    {
        for(int n = 0; n < x; n++)
        {
            if(timage->getPixel(n,i) == scolor) timage->setPixel(n,i, dcolor);
        }
    }
}
