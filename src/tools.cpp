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

float getDistance(int x0, int y0, int x1, int y1)
{
    float rise = y1 - y0;
    float run = x1 - x0;

    //if(rise == 0) return run;
    //else if(run == 0) return rise;

    return sqrtf( rise*rise + run*run);
}
