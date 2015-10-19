#include "player.hpp"

Player::Player()
{
    //set player default starting position
    mX = 0;
    mY = 0;
    mGlobalX = 0;
    mGlobalY = 0;

    mTurns = 0;
    mTurnsPerHour = 12;
    mDay = 0;
    mHour = 0;

    mHydration = 0;
    mHydrationLossPH = 12;

    mCalories = 0;
    mCalorieBurnPH = 72;

    //set player default graphic
    mIcon = '@';

}

//inventory
void Player::addItem( ItemRef *newitem)
{
    if(newitem == NULL) {printError("Cannot add item to player :itemref = NULL"); return;}

    mInventory.push_back(newitem);
}

void Player::removeItem( ItemRef *target)
{
    for(int i = mInventory.size()-1; i >= 0; i--)
    {
        if(mInventory[i] == target)
        {
            mInventory.erase( mInventory.begin() + i);
            return;
        }
    }
}

bool Player::drink(ItemRef *target)
{
    for(int i = mInventory.size()-1; i >= 0; i--)
    {
        if(mInventory[i] == target)
        {
            if(target->isDrink())
            {
                if(target->getDrink() == NULL)
                {
                    clear();
                    printw("The %s contains nothing to drink.\n", target->getName().c_str());
                    getch();
                    return false;
                }
                else
                {

                    //if the volume left in the drink is less than the drinking amount
                    if(target->getDrink()->current_volume - PLAYER_DRINK_AMT <= 0)
                    {
                        //need to calculate hydration for different liquid types and amounts
                        mHydration += target->getDrink()->current_volume * LIQ_TABLE[target->getDrink()->liquid][1];
                        //remove drinkable liquid from container
                        target->setDrink(NULL);
                        return true;
                    }
                    else
                    {
                        //need to calculate hydration for different liquid types and amounts
                        mHydration += PLAYER_DRINK_AMT * LIQ_TABLE[target->getDrink()->liquid][1];
                        //subtract dranken volume from liquids current volume
                        target->getDrink()->current_volume -= PLAYER_DRINK_AMT;

                        return true;
                    }
                }

            }
        }
    }

    return false;
}

//load/save
void Player::savePlayer()
{
    //generate filename
    std::stringstream filename;
    //add directory
    filename << "data\\map\\player.txt";



    std::ofstream playersave;

    playersave.open(filename.str().c_str());
    {
        //save player position
        //save global
        playersave << mGlobalX << ":";
        playersave << mGlobalY << ":" << std::endl;
        //save local
        playersave << mX << ":";
        playersave << mY << std::endl;

        //save player turn count
        playersave << mTurns << ":";
        playersave << mTurnsPerHour  << std::endl;

        //save date
        playersave << mDay << ":";
        playersave << mHour << std::endl;

        //save hydration
        playersave << mHydration << ":";
        playersave << mHydrationLossPH << std::endl;

        //save calories
        playersave << mCalories << ":";
        playersave << mCalorieBurnPH << std::endl;


        //save item count
        playersave << mInventory.size() << std::endl;

        for(int i = 0; i < int(mInventory.size()); i++)
        {
            //as item types become more defined, more data will need to be saved
            playersave << mInventory[i]->getID() << ":";

            if(mInventory[i]->isDrink())
            {
                playersave << I_DRINK << ":";

                //check to see if the drinking container has anything in it
                if(mInventory[i]->getDrink() != NULL)
                {
                    playersave << mInventory[i]->getDrink()->current_volume << ":";
                    playersave << mInventory[i]->getDrink()->liquid << std::endl;
                }
                else
                {
                    playersave << "0:" << std::endl;
                }

            }
            else playersave << I_GEN << ":" << std::endl;



        }
    }

    playersave.close();
}

bool Player::loadPlayer( std::vector<Item> *itemlist)
{

    //generate filename
    std::stringstream filename;
    //add directory
    filename << "data\\map\\player.txt";


    std::ifstream playerload;
    playerload.open(filename.str().c_str());

    if(!playerload.is_open())
    {
        return false;
    }

    //clear player data
    for(int i = mInventory.size()-1; i >= 0; i--)
    {
        delete mInventory[i];
    }

    mInventory.clear();
    {
        int player_item_count = 0;

        if(!playerload.eof())
        {
            //get positions

            char buf[20];
            playerload.getline(buf,20, ':');
            mGlobalX = atoi(buf);

            char buf2[20];
            playerload.getline(buf2, 20);
            mGlobalY = atoi(buf2);

            char buf3[20];
            playerload.getline(buf3, 20, ':');
            mX = atoi(buf3);

            char buf4[20];
            playerload.getline(buf4, 20);
            mY = atoi(buf4);

        }

        //get player turn count
        if(!playerload.eof())
        {
            char buf[20];
            playerload.getline(buf,20, ':');
            mTurns = atoi(buf);
        }

        //get player turns per hour
        if(!playerload.eof())
        {
            char buf[20];
            playerload.getline(buf,20);
            mTurnsPerHour = atoi(buf);
        }

        //get day and hour
        if(!playerload.eof())
        {
            char buf[20];
            playerload.getline(buf,20, ':');
            mDay = atoi(buf);
        }
        if(!playerload.eof())
        {
            char buf[20];
            playerload.getline(buf,20);
            mHour = atoi(buf);
        }

        //get hydration
        if(!playerload.eof())
        {
            char buf[20];
            playerload.getline(buf,20, ':');
            mHydration = atoi(buf);

            char b_hl[20];
            playerload.getline(b_hl, 20);
            mHydrationLossPH = atoi(b_hl);
        }

        //get calories
        if(!playerload.eof())
        {
            char b_cal[20];
            playerload.getline(b_cal,20,':');
            mCalories = atoi(b_cal);

            char b_cph[20];
            playerload.getline(b_cph, 20);
            mCalorieBurnPH = atoi(b_cal);
        }

        //get inv count
        if(!playerload.eof())
        {
            char buf[20];
            playerload.getline(buf,20);
            player_item_count = atoi(buf);

        }

        for(int i = 0; i < player_item_count; i++)
        {
            /*//player items do not need positions
            int x;
            int y;
            */

            int item_id;

            char buf[20];

            playerload.getline(buf,20, ':');
            item_id = atoi(buf);

            //create item
            ItemRef *temp = new ItemRef( &(*itemlist)[item_id]);

            //get item sub data
            char btype[20];
            playerload.getline(btype, 20, ':');
            if(atoi(btype) == I_DRINK)
            {
                int drinkvol;

                //get drink volume
                char bvol[20];
                playerload.getline(bvol,20,':');
                drinkvol = atoi(bvol);

                //if the drink is empty
                if(drinkvol == 0)
                {
                    playerload.get();
                }
                else
                {

                    Item_DrinkRef *tempdrink = new Item_DrinkRef;

                    tempdrink->current_volume = drinkvol;

                    char bliq[20];
                    playerload.getline(bliq,20);
                    tempdrink->liquid = atoi(bliq);

                    temp->setDrink(tempdrink);
                }

            }
            else
            {
                //its a general item
                playerload.get();
            }

            //push item into inventory
            mInventory.push_back(temp);

        }


    }

    playerload.close();
    return true;
}

void Player::increaseTurn()
{
    mTurns++;

    mHour += ((60/mTurnsPerHour) * 100) / 60 * .01;

    if(mHour >= 24)
    {
        mHour -= 24;
        mDay++;
    }

    //calculate hydration loss for movement turns
    mHydration -= mHydrationLossPH / mTurnsPerHour;
    //calculate calorie burn for movement turns
    mCalories -= mCalorieBurnPH / mTurnsPerHour;
}

//debug
void Player::debug_viewInventory()
{
    clear();

    nocbreak();

    if(mInventory.empty())
    {
        printw("You are not carrying anything.\n");
    }
    else
    {
        printw("You are carring:\n");

        for(int i = 0; i < int(mInventory.size()); i++)
        {
            printw(" - %s\n", mInventory[i]->getName().c_str());
        }

    }

    refresh();
    getch();
}
