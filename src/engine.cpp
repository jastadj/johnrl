#include "engine.hpp"

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::start()
{

    //init curses
    initCurses();


    //start main loop
    mainLoop();
}

bool Engine::initCurses()
{
    //init main curses
    initscr();

    return true;
}

void Engine::mainLoop()
{
    bool quit = false;
    int k = 0;

    while(!quit)
    {

        clear();

        printw("test!\n");
        mvprintw(24,0, "Key Pressed:%d", k);

        k = getch();

        //escape key


    }
}
