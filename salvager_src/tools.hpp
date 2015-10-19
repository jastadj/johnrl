#ifndef TOOLS_H
#define TOOLS_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <curses.h>
#include "colors.hpp"
#include "perlin.hpp"

void printError(std::string errorMsg);
void printError(std::stringstream errorMsg);


void printPerlin(double zoom, double p, int o);

float getDistance(int x1, int y1, int x2, int y2);

struct fps_timer
{
    int ticks;
};

#endif // TOOLS_H
