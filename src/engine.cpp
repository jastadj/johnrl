#include "engine.hpp"

//debug
#include <iostream>
#include <string>


Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::start()
{

    //init curses
    //initCurses();

    //xml parse testing
    tinyxml2::XMLDocument doc;
    doc.LoadFile("dream.xml");


    tinyxml2::XMLElement *myelement;
    myelement = doc.FirstChildElement("PLAY");
    if(myelement != NULL)
    {
        if(myelement->FirstChild()->Value() != NULL)
        {
            std::cout << myelement->FirstChild()->Value() << std::endl;
            if(myelement->FirstChild()->FirstChild() != NULL)
            {
                std::cout << myelement->FirstChild()->FirstChild()->Value() << std::endl;
            }
        }
    }


    return;


    //start main loop
    mainLoop();

    //clean up terminal before exit
    clear();
    refresh();
}

bool Engine::initCurses()
{
    //init main curses
    initscr();

    //enable other keys
    keypad(stdscr, TRUE);

    //disable cursor
    curs_set(0);

    //disable echoing of keys
    noecho();

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
        if(k == 27) quit = true;

    }
}
