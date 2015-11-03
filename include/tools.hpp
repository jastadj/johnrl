#ifndef _TOOLS
#define _TOOLS

#include <SFML/Graphics.hpp>
#include <cmath>

//tools
void replaceImageColor(sf::Image *timage, sf::Color scolor, sf::Color dcolor);
float getDistance(int x0, int y0, int x1, int y1);

#endif // _TOOLS
