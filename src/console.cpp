#include "engine.hpp"
#include <iostream>

void Engine::console()
{
    bool quit = false;

    //build commands
    consolecmd *newcmd = new consolecmd{"help", "Print this help menu", NULL};
    cCommands.push_back(newcmd);
    newcmd = new consolecmd{"newgame","Start new game", NULL};
    cCommands.push_back(newcmd);
    newcmd = new consolecmd{"seed","Print current game seed", NULL};
    cCommands.push_back(newcmd);
    newcmd = new consolecmd{"test","This is a test", NULL};
    cCommands.push_back(newcmd);
    newcmd = new consolecmd{"print","Prints parameters", cCommands.back()};
    cCommands.push_back(newcmd);

    while(!quit)
    {
        std::string buf;

        std::cout << "\n>";
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
    cmd.resize(1);


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

    //find first parent command
    for(int i = 0; i < int(cCommands.size()); i++)
    {
        //if cmd is found
        if(cmd == cCommands[i]->cmd && cCommands[i]->parent == NULL)
        {
            break;
        }

        if(i == int(cCommands.size()-1))
        {
            std::cout << "Unknown command.  Type 'help'.\n";
            return;
        }
    }

    if(cmd == "help")
    {
        for(int i = 0; i < int(cCommands.size()); i++)
        {
            if(cCommands[i]->parent == NULL)
            {
                std::cout << cCommands[i]->cmd << "........" << cCommands[i]->helptxt << std::endl;
            }
        }

        std::cout << std::endl;
    }
    else if(cmd == "newgame")
    {
        if(params.empty()) newGame();
        else newGame( atol(params[0].c_str()));
    }
    else if(cmd == "seed")
    {
        std::cout << "seed = " << m_Seed << std::endl;
    }
    else
    {
        std::cout << "Unimplemented command.\n";
    }
}
