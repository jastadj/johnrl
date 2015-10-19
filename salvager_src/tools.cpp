#include "tools.hpp"

void printError(std::string errorMsg)
{
    nocbreak();
    clear();
    printw("%s\n", errorMsg.c_str());
    refresh();
    getch();
}

void printError(std::stringstream errorMsg)
{
    nocbreak();
    clear();
    printw("%s\n", errorMsg.str().c_str());
    refresh();
    getch();
}

void printPerlin(double zoom, double p, int o)
{
    std::vector< std::vector<int> > pmap = genHeightMapV(80, 25,0,0, zoom, p, o);

    int water_level = 100;

    clear();

    for(int i = 0; i < int(pmap.size()); i++)
    {
        for(int n = 0; n < int(pmap[i].size()); n++)
        {
            if(pmap[i][n] <= water_level)
            {
                attron( COLOR_PAIR(C_BLUE));
                mvaddch(i,n,'~');
                standend();
            }
            else
            {
                attron( COLOR_PAIR(C_GREEN));
                mvaddch(i,n,'*');
                standend();
            }
        }
    }

    refresh();
    getch();
}

float getDistance(int x1, int y1, int x2, int y2)
{
    int length = abs(x1 - x2);
    int height = abs(y1 - y2);

    return sqrt( (length * length) + (height * height));
}
