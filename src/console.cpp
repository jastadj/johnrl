#include "engine.hpp"
#include <iostream>

void Engine::console()
{
    bool quit = false;

    while(!quit)
    {
        std::string buf;

        std::cout << ">";
        std::getline(std::cin, buf);

        parse(buf);
    }
}

void Engine::parse(std::string ccmd)
{
    if(ccmd.empty()) return;

    std::string cmd;
    std::vector< std::string > params;

    size_t ipos = 0;
    ipos = ccmd.find_first_of(' ');

    //check if there are parameters, if there are, parse them out
    if(ipos != std::string::npos)
    {
        cmd = ccmd.substr(0, ipos);
        ccmd.erase(0, ipos + 1);

        do{
            //find position where a space is found
            ipos = ccmd.find_first_of(' ');

            //if space is not found, bail after pushing last bit of string
            if(ipos == std::string::npos)
            {
                //push last bit of string
                params.push_back(ccmd);
                break;
            }

            //substring until space character
            params.push_back(ccmd.substr(0, ipos) );
            //erase from start of string to space character
            ccmd.erase(0, ipos+1);
          }while(1);
    }
    else cmd = ccmd;

    if(cmd == "newgame") newGame();
}
