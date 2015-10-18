#ifndef CLASS_ENGINE
#define CLASS_ENGINE

#include "curses.h"
#include "tinyxml2.h"

class Engine
{
private:

    //init
    bool initCurses();

    //loops
    void mainLoop();

public:
    Engine();
    ~Engine();

    void start();

};

#endif // CLASS_ENGINE
