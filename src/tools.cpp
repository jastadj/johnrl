#include "tools.hpp"

float getDistance(int x0, int y0, int x1, int y1)
{
    float rise = y1 - y0;
    float run = x1 - x0;

    //if(rise == 0) return run;
    //else if(run == 0) return rise;

    return sqrtf( rise*rise + run*run);
}
