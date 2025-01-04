#include "Action.h"
#include "Monster.h"
#include "Inventory.h"
#include "Party.h"
#include "Map.h"
// #include "Menu.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

Action::Action() {}

int Action::getClearedRoom() const
{
    return cleared_room_;
}

int Action::getKey() const
{
    return key_;
}

bool Action::endGame()
{
    if (map_.isDungeonExit(map_.getPlayerRow(), map_.getPlayerCol()) == true)
    {
        if (cleared_room_ == 5 && party_size_ >= 2)
        {
            cout << "CONGRATULATIONS!! You have successfully escaped the dungeon." << endl
                 << endl;
            return true;
        }
        else
        {
            cout << "You can not exit. Your party has not cleared all 5 rooms." << endl
                 << endl;
        }
    }
    if (party_[0].getFullnessLevel() <= 0)
    {
        party_size_;
        cout << "OH NO! " << party_[0].getName() << " , you've died. Since the leader has died, the party members are stucked in the dungeon forever." << endl
             << endl;
        return true;
    }
    if (party_size_ <= 1)
    {
        cout << "OH NO! All members have died. You are stucked in the dungeon forever." << endl
             << endl;
        return true;
    }
    if (monster_.getSorcererAnger() >= 100)
    {
        for (int i = 0; i < party_size_; i++)
        {
            party_[i].setFullnessLevel(-50);
        }
        cout << "The Sorcerer's anger level has reached 100 and the monster has exploded the dungeon and killed the whole party." << endl
             << endl;
        return true;
    }
    return false;
}

void Action::printActionStatus()
{
    cout << "+-------------+" << endl
         << "| STATUS      |" << endl
         << "+-------------+" << endl
         << "| Rooms Cleared: " << cleared_room_ << " | Keys: " << key_ << " | Anger Level: " << monster_.getSorcererAnger() << endl;
    menu_.printInventoryStatus();
    cout << "+-------------+" << endl
         << "| PARTY       |" << endl
         << "+-------------+" << endl;
    for (int i = 0; i < CAPACITY; i++)
    {
        if (party_[i].getFullnessLevel() > 0)
            cout << "| " << party_[i].getName() << " | Fullness: " << party_[i].getFullnessLevel() << endl;
    }
    cout << "+-------------+" << endl;
}

void Action::printMerchantMenu()
{
    cout << "If you're looking to get supplies, you've come to the right place. I would be happy to part with some of my wares...for the proper price!" << endl
         << endl;
    int option = 0;
    do
    {
        menu_.printInventoryStatus();
        cout << endl
             << "Choose one of the following:" << endl
             << " 1. Ingredients: To make food, you have to cook raw ingredients." << endl
             << " 2. Cookware: You will need something to cook those ingredients." << endl
             << " 3. Weapons: It's dangerous to go alone, take this!" << endl
             << " 4. Armor: If you want to survive monster attacks, you will need some armor." << endl
             << " 5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl
             << " 6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl
             << endl
             << "> ";
        cin >> option;
        cout << endl;

        if (option == 1)
            menu_.printIngredientMenu(cleared_room_);
        else if (option == 2)
            menu_.printCookwareMenu(cleared_room_);
        else if (option == 3)
            menu_.printWeaponsMenu(cleared_room_);
        else if (option == 4)
            menu_.printArmorMenu(cleared_room_);
        else if (option == 5)
            menu_.sellTreasure();
        else if (option == 6)
        {
            char confirm;
            cout << "Are you sure you're finished? You won't be able to buy anything else from me! (y/n)" << endl
                 << endl
                 << "> ";
            cin >> confirm;
            if (confirm == 'n')
                option = 1; // not 6 so the loop still continues
        }
        else
            cout << "Please pick a valid option" << endl;

    } while (option != 6);
}

void Action::setNames(string name)
{
    party_[party_size_] = Party(name, 50);
    party_size_++;
}

void Action::createRoom()
{
    int count = 0;
    srand((unsigned int)time(0));
    while (count < 5)
    {
        int row = rand() % 12 + 1; // create a random number between 1 - 12
        int col = rand() % 12 + 1;
        if (map_.addRoom(row, col) == true)
            count++;
    }
}

void Action::creatNPC()
{
    int count = 0;
    srand((unsigned int)time(0));
    while (count < 5)
    {
        int row = rand() % 12 + 1; // create a random number between 1 - 12
        int col = rand() % 12 + 1;
        if (map_.addNPC(row, col) == true)
            count++;
    }
}

void Action::move() // game ends, return true if sorcerer anger reaches 100
{
    char move;
    bool result;
    do
    {
        cout << "Select w (up), s (down), a (left), d (right) to move." << endl
             << endl
             << "> ";
        cin >> move;
        result = map_.move(move);
        if (result == true)
        {
            if (map_.isNPCLocation(map_.getPlayerRow(), map_.getPlayerCol()) == true)
                map_.exploreSpace(map_.getPlayerRow(), map_.getPlayerCol());
            if (map_.isExplored(map_.getPlayerRow(), map_.getPlayerCol()) == false)
            {
                if (cleared_room_ == 5)
                    monster_.setSorcererAnger(-monster_.getSorcererAnger());
                else
                    monster_.setSorcererAnger(1); // increse by one
            }
            for (int i = 0; i < CAPACITY; i++)
            {
                if (party_[i].getFullnessLevel() > 0)
                {
                    party_[i].fullnessChange(20, -1);
                    if (party_[i].getFullnessLevel() <= 0)
                        party_size_--;
                }
            }
        }
        else
            cout << "You're hitting the wall! Please move in a different direction." << endl
                 << endl;
    } while (result == false);
}

void Action::PrintMap()
{
    map_.displayMap();
}

void Action::investigate()
{
    map_.exploreSpace(map_.getPlayerRow(), map_.getPlayerCol());
    if (map_.isFreeSpace(map_.getPlayerRow(), map_.getPlayerCol()))
        explored_space_++;
    srand((unsigned int)time(0));
    int random = rand() % 100 + 1;
    if (random <= 10)
    {
        key_++;
        cout << "You have found a key" << endl
             << endl;
    }
    else if (random > 10 && random <= 30)
    {
        if (cleared_room_ == 0)
        {
            menu_.setRing(1);
            cout << "You have found a ring" << endl
                 << endl;
        }
        else if (cleared_room_ == 1)
        {
            menu_.setNecklace(1);
            cout << "You have found a necklace" << endl
                 << endl;
        }
        else if (cleared_room_ == 2)
        {
            menu_.setBracelet(1);
            cout << "You have found a bracelet" << endl
                 << endl;
        }
        else if (cleared_room_ == 3)
        {
            menu_.setCirclet(1);
            cout << "You have found a circlet" << endl
                 << endl;
        }
        else if (cleared_room_ == 4)
        {
            menu_.setGoblet(1);
            cout << "You have found a goblet" << endl
                 << endl;
        }
    }
    else if (random > 30 && random <= 50)
    {
        cout << "The party has encountered a monster!" << endl << endl;
        fightMonster();
        return; // no more 50% chance of droping fullness point
    }

    for (int i = 0; i < CAPACITY; i++)
    {
        if (party_[i].getFullnessLevel() > 0)
        {
            party_[i].fullnessChange(50, -1);
            if (party_[i].getFullnessLevel() <= 0)
                party_size_--;
        }
    }
}

void Action::cookAndEat()
{
    srand((unsigned int)time(0));
    int rand_num = rand() % 100 + 1;
    int kg;
    do
    {
        cout << "You have " << menu_.getIngredients() << " kg of ingredients." << endl
             << "How many kg of ingredients do you want to cook? (Enter a positive mulitple of 5)" << endl
             << endl
             << "> ";
        cin >> kg;
        cout << endl;
        if (kg % 5 != 0)
            cout << "Please enter a positive mulitple of 5" << endl
                 << endl;
        else if (menu_.getIngredients() < kg)
            cout << "You have less than " << kg << " kg of ingredients." << endl
                 << endl;
    } while (kg % 5 != 0 || menu_.getIngredients() < kg);

    int new_fullness = kg / 5;
    bool valid = true;
    char option;
    do
    {
        cout << "You have " << menu_.getCeramicPot() << " Ceramic Pot(s) (P), " << menu_.getFryingPan() << " Frying Pan(s) (F), and " << menu_.getCauldron() << " Cauldron(s) (C)" << endl
             << "Please select P, F, or C to use a cookware or 0 to cancel." << endl
             << endl;
        cin >> option;
        cout << endl;
        if (option == 'P')
        {
            if (menu_.getCeramicPot() == 0)
            {
                cout << "You don't own a Ceramic Pot, please select a different cookware." << endl
                     << endl;
                valid = false;
            }
            else
            {
                menu_.setCeramicPot(-1);
                if (rand_num <= 25)
                {
                    cout << "OH NO! Your cookware breaks while cooking, you've lost both ingredients and the cookware." << endl
                         << endl;
                    break;
                }
                else
                {
                    cout << "You've cooked successfully! Each member have just recieved " << new_fullness << " fullness point(s)." << endl
                         << endl;
                    menu_.setIngredients(-kg);
                    for (int i = 0; i < CAPACITY; i++)
                    {
                        if (party_[i].getFullnessLevel() > 0)
                            party_[i].fullnessChange(100, new_fullness);
                    }
                    break;
                }
            }
        }
        else if (option == 'F')
        {
            if (menu_.getFryingPan() == 0)
            {
                cout << "You don't own a Frying Pan, please select a different cookware." << endl
                     << endl;
                valid = false;
            }
            else
            {
                menu_.setFryingPan(-1);
                if (rand_num <= 10)
                {
                    cout << "OH NO! Your cookware breaks while cooking, you've lost both ingredients and the cookware." << endl
                         << endl;
                    break;
                }
                else
                {
                    cout << "You've cooked successfully! Each member have just recieved " << new_fullness << " fullness point(s)." << endl
                         << endl;
                    menu_.setIngredients(-kg);
                    for (int i = 0; i < CAPACITY; i++)
                    {
                        if (party_[i].getFullnessLevel() > 0)
                            party_[i].fullnessChange(100, new_fullness);
                    }
                    break;
                }
            }
        }
        else if (option == 'C')
        {
            if (menu_.getCauldron() == 0)
            {
                cout << "You don't own a Cauldron, please select a different cookware." << endl
                     << endl;
                valid = false;
            }
            else
            {
                menu_.setCauldron(-1);
                if (rand_num <= 2)
                {
                    cout << "OH NO! Your cookware breaks while cooking, you've lost both ingredients and the cookware." << endl
                         << endl;
                    break;
                }
                else
                {
                    cout << "You've cooked successfully! Each member have just recieved " << new_fullness << " fullness point(s)." << endl
                         << endl;
                    menu_.setIngredients(-kg);
                    for (int i = 0; i < CAPACITY; i++)
                    {
                        if (party_[i].getFullnessLevel() > 0)
                            party_[i].fullnessChange(100, new_fullness);
                    }
                    break;
                }
            }
        }
        else if (option == '0')
        {
            return;
        }
        else
        {
            cout << "Invalid." << endl
                 << endl;
            valid = false;
        }
        menu_.printInventoryStatus();
        cout << endl
             << "Remaining kg of ingredients: " << menu_.getIngredients() << endl
             << endl;

    } while (!valid);
}

bool Action::misfortunes() //return true if leader dies
{
    srand((unsigned int)time(0));
    int rand_num = rand() % 100 + 1;
    if (rand_num <= 30)
    {
        int random1 = rand() % 3;
        if (random1 == 0)
        {
            menu_.setIngredients(-10);
            cout << "OH NO! Your team was robbed by dungeon bandits!" << endl
                 << "You lost 10 kg of ingredients!" << endl
                 << endl;
        }
        else if (random1 == 1)
        {
            int rand1 = rand() % 3;
            if (rand1 == 0 && menu_.getCeramicPot() > 0)
            {
                menu_.setCeramicPot(-1);
                cout << "OH NO! Your team was robbed by dungeon bandits!" << endl
                     << "You lost 1 Ceramic Pot!" << endl
                     << endl;
            }
            else if (rand1 == 1 && menu_.getFryingPan() > 0)
            {
                menu_.setFryingPan(-1);
                cout << "OH NO! Your team was robbed by dungeon bandits!" << endl
                     << "You lost 1 Frying Pan!" << endl
                     << endl;
            }
            else if (rand1 == 2 && menu_.getCauldron() > 0)
            {
                menu_.setCauldron(-1);
                cout << "OH NO! Your team was robbed by dungeon bandits!" << endl
                     << "You lost 1 Cauldron!" << endl
                     << endl;
            }
        }
        else if (random1 == 2 && menu_.getArmor() > 0)
        {
            menu_.setArmor(-1);
            cout << "OH NO! Your team was robbed by dungeon bandits!" << endl
                 << "You lost 1 armor!" << endl
                 << endl;
        }
    }
    else if (rand_num > 30 && rand_num <= 40)
    {
        int random2 = rand() % 4;
        if (random2 == 0 && menu_.getStoneClub() > 0)
        {
            menu_.setStoneClub(-1);
            cout << "OH NO! Your Stone Club broke!" << endl
                 << endl;
        }
        if (random2 == 1 && menu_.getIronSpear() > 0)
        {
            menu_.setIronSpear(-1);
            cout << "OH NO! Your Iron Spear broke!" << endl
                 << endl;
        }
        if (random2 == 2 && menu_.getMythrilRapier() > 0)
        {
            menu_.setMythrilRapier(-1);
            cout << "OH NO! Your +1 Mythril Rapier broke!" << endl
                 << endl;
        }
        if (random2 == 3 && menu_.getFlamingBattleAxe() > 0)
        {
            menu_.setFlamingBattleAxe(-1);
            cout << "OH NO! Your +2 Flaming Battle-Axe broke!" << endl
                 << endl;
        }
        if (random2 == 4 && menu_.getVorpalLongsword() > 0)
        {
            menu_.setVorpalLongsword(-1);
            cout << "OH NO! Your +3 Vorpal Longsword broke!" << endl
                 << endl;
        }
    }
    else if (rand_num > 40 && rand_num <= 70) // 30% 1 member get reduced 10 fullness points
    {
        int rand_mem;
        do
        {
            rand_mem = rand() % CAPACITY;
        } while (party_[rand_mem].getFullnessLevel() <= 0);
        party_[rand_mem].fullnessChange(100, -10);
        if (party_[rand_mem].getFullnessLevel() <= 0)
            party_size_--;
        cout << party_[rand_mem].getName() << " got food poisoning and have lost 10 points of hunger." << endl
             << endl;
    }
    return endGame();
}

bool Action::attack(int challenge_rate) // true if win
{
    int num_weapon = menu_.getNumWeapons();
    if (num_weapon < party_size_)
        num_weapon = party_size_;
    int d = 0;
    if (menu_.difWeapons() == true)
        d = 4;
    int w = num_weapon + menu_.getMythrilRapier() + 2 * menu_.getFlamingBattleAxe() + 3 * menu_.getVorpalLongsword();
    srand((unsigned int)time(0));
    double r1 = rand() % 6 + 1;
    double r2 = rand() % 6 + 1;
    double outcome = (r1 * w + d) - (r2 * challenge_rate / menu_.getArmor());
    if (outcome > 0)
    {
        menu_.setGold(10 * challenge_rate);
        menu_.setIngredients(5 * challenge_rate);
        cout << "You have defeated the monster!" << endl
             << endl;
        monster_defeated_++;
        if ((rand() % 100 + 1) <= 15)
        {
            cout << "The monster has dropped a key!" << endl
                 << endl;
            key_++;
        }
        return true;
    }
    else
    {
        menu_.setGold(-menu_.getGold() / 4); // quarter of the current gold

        int no_armor = party_size_ - menu_.getArmor(); //**
        if (menu_.getArmor() >= party_size_)
            no_armor = 0;

        for (int i = 1; i <= no_armor; i++)
        {
            if (party_[i].getFullnessLevel() > 0)
            {
                if ((rand() % 100 + 1) <= 10)
                {
                    party_[i].setFullnessLevel(-50);
                    party_size_--;
                    cout << "OH NO " << party_[i].getName() << " has been slained. Your party now has " << party_size_ << " people." << endl
                         << endl;
                }
            }
        }
        for (int i = no_armor + 1; i < CAPACITY; i++)
        {
            if (party_[i].getFullnessLevel() > 0)
            {
                if ((rand() % 100 + 1) <= 5)
                {
                    party_[i].setFullnessLevel(-50);
                    party_size_--;
                    cout << "OH NO " << party_[i].getName() << " has been slained. Your party now has " << party_size_ << " people." << endl
                         << endl;
                }
            }
        }
        menu_.setIngredients(-30);
        cout << "The party has been defeated by the monster!" << endl
             << endl;
        return false;
    }
}

bool Action::fightMonster() // return true if win
{
    srand((unsigned int)time(0));
    if (menu_.getNumWeapons() > 0)
    {
        int option;
        cout << "You have at least one weapon and you are given options to:" << endl
             << "1. Attack" << endl
             << "2. Surrender" << endl
             << endl
             << "> ";
        cin >> option;
        if (option == 1)
        {
            int c;
            if (cleared_room_ == 0)
            {
                if (open_door_ == true)
                {
                    c = 2;
                    cout << monster_.monsterTwo() << " AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
                else
                {
                    c = 1;
                    cout << monster_.monsterOne() << " AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
            }
            else if (cleared_room_ == 1)
            {
                if (open_door_ == true)
                {
                    c = 3;
                    cout << monster_.monsterThree() << " AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
                else
                {
                    c = 2;
                    cout << monster_.monsterTwo() << " AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
            }
            else if (cleared_room_ == 2)
            {
                if (open_door_ == true)
                {
                    c = 4;
                    cout << monster_.monsterFour() << " AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
                else
                {
                    c = 3;
                    cout << monster_.monsterThree() << " AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
            }
            else if (cleared_room_ == 3)
            {
                if (open_door_ == true)
                {
                    c = 5;
                    cout << monster_.monsterFive() << " AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
                else
                {
                    c = 4;
                    cout << monster_.monsterFour() << " AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
            }
            else if (cleared_room_ == 4)
            {
                if (open_door_ == true)
                {
                    c = 6;
                    cout << "SORCERER AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
                else
                {
                    c = 5;
                    cout << monster_.monsterFive() << " AHEAD! THEY LOOK HOSTILE!" << endl
                         << endl;
                }
            }
            if (attack(c) == true)// win
                return true;
        }
        else if (option == 2)
        {
            int rand_mem;
            do
            {
                rand_mem = rand() % (CAPACITY - 1) + 1; // from 1 to 4
            } while (party_[rand_mem].getFullnessLevel() <= 0);
            party_[rand_mem].setFullnessLevel(-50);
            party_size_--;
            cout << party_[rand_mem].getName() << " has been held captive. The party loses one member." << endl
                 << "You now have " << party_size_ << " members." << endl;
        }
    }
    else
    {
        cout << "The party has no weapons, therefore, only given the option of surrendering." << endl;
        int rand_mem1;
        do
        {
            rand_mem1 = rand() % (CAPACITY - 1) + 1; // from 1 to 4
        } while (party_[rand_mem1].getFullnessLevel() <= 0);
        party_[rand_mem1].setFullnessLevel(-50);
        party_size_--;
        cout << party_[rand_mem1].getName() << " has been held captive. The party loses one member." << endl
             << "You now have " << party_size_ << " members." << endl;
    }

    for (int i = 0; i < CAPACITY; i++)
    {
        if (party_[i].getFullnessLevel() > 0)
        {
            party_[i].fullnessChange(50, -1);
            if (party_[i].getFullnessLevel() <= 0)
                party_size_--;
        }
    }
    return false;
}

bool Action::normalSpace()
{
    bool investigated = false; // use do while loop for option 2
    int option;
    do
    {
        investigated = false;
        cout << "Select one:" << endl
             << "1. Move" << endl
             << "2. Investigate" << endl
             << "3. Pick a Fight" << endl
             << "4. Cook and Eat" << endl
             << "5. Give up" << endl
             << endl
             << "> ";
        cin >> option;
        cout << endl;
        if (option == 1)
        {
            turns_++;
            move();
            cout << endl;
            return endGame(); // return true or false
        }
        else if (option == 2)
        {
            if (map_.isExplored(map_.getPlayerRow(), map_.getPlayerCol()) == true)
            {
                cout << "This space has been explored. Please select another option." << endl
                     << endl;
                investigated = true;
            }
            else
            {
                investigate();
                turns_++;
            }
            cout << endl;
            return endGame();
        }
        else if (option == 3)
        {
            turns_++;
            fightMonster();
            cout << endl;
            return endGame();
        }
        else if (option == 4)
        {
            turns_++;
            cookAndEat();
            cout << endl;
            return endGame();
        }
        else
        {
            turns_++;
            cout << "You have given up:( Sorry that you could not make it out of the dungeon." << endl
                 << endl;
            return true;
        }
    } while (investigated == true);
}

void Action::speakToNpc()
{
    cout << "Hello! Please help me solve a puzzle!" << endl
         << endl;
    if (monster_.npcPuzzle() == true)
    {
        char option;
        cout << "Thanks for solving the puzzle. Do you wish to barter for goods? (y/n)" << endl
             << endl
             << "> ";
        cin >> option;
        if (option == 'y')
            printMerchantMenu(); // with different price
    }
    else
        fightMonster();
    map_.removeNPC(map_.getPlayerRow(), map_.getPlayerCol());
    explored_space_++;

}

bool Action::npcSpace()
{
    int option;
    cout << "You have encountered a Non-player Character" << endl << endl
         << "Select one:" << endl
         << "1. Move" << endl
         << "2. Speak to NPC" << endl
         << "3. Give up" << endl
         << endl
         << "> ";
    cin >> option;
    cout << endl;
    if (option == 1)
    {
        turns_++;
        move();
        cout << endl;
        return endGame(); // return true or false
    }
    else if (option == 2)
    {
        turns_++;
        speakToNpc();
        cout << endl;
        return endGame();
    }
    else
    {
        turns_++;
        cout << "You have given up:( Sorry that you could not make it out of the dungeon." << endl
             << endl;
        return true;
    }
}

void Action::openDoor()
{
    srand((unsigned int)time(0));
    if (key_ > 0)
    {
        key_--;
        open_door_ = true;
        if (fightMonster() == true) // win
        {
            cleared_room_++;
            if (rand() % 10 <= 60) // 60% chance misfortune occurs
                misfortunes();
            map_.removeRoom(map_.getPlayerRow(), map_.getPlayerCol());
            explored_space_++;
        }
        else
        {
            if (rand() % 10 <= 40) // 40% chance misfortune occurs
                misfortunes();
        }
        open_door_ = false; // close door

        if (rand() % 100 <= 30) // 30% chance one mem get locked inside the room
        {
            int rand_mem;
            do
            {
                rand_mem = rand() % (CAPACITY - 1) + 1; // from 1 to 4
            } while (party_[rand_mem].getFullnessLevel() <= 0);
            party_[rand_mem].setFullnessLevel(-50);
            party_size_--;
            cout << " OH NO! Your teammate " << party_[rand_mem].getName() << " is trapped in the previous room and is unable to get through. You must continue without them." << endl
                 << "Your party size has reduced to " << party_size_ << " members." << endl
                 << endl;
        }
    }
    else // play puzzle
    {
        int tries = 1;
        string option;
        do
        {
            do
            {
                cout << "The party has trapped in a door puzzle because you attempted to open the door with no keys." << endl
                     << "You are required to play a game of Rock/Paper/Scissors with the door based on the following rules:" << endl
                     << "Rock beats Sissor" << endl
                     << "Scissors beats Paper" << endl
                     << "Paper beats Rock" << endl
                     << endl
                     << "Please enter either rock, paper, or scissors (lowercase). Shoot!" << endl
                     << "> ";
                cin >> option;
                if (option != "rock" && option != "paper" && option != "scissors")
                    cout << "Please enter a valid option." << endl
                         << endl;
            } while (option != "rock" && option != "paper" && option != "scissors");

            if (monster_.doorPuzzle(option) == 0)
                cout << "Ties! Again" << endl
                     << endl;
            else if (monster_.doorPuzzle(option) == 1)
                cout << "You win after " << tries << " tries!" << endl
                     << endl;
            else
            {
                cout << "OH NO! You have " << 3 - tries << " more tries." << endl
                     << endl;
                tries++;
            }
        } while (monster_.doorPuzzle(option) != 1 && tries < 4);

        if (tries < 4)
        {
            cout << "You can now enter the door without a key." << endl
                 << endl;
            open_door_ = true;
            if (fightMonster() == true) // win
            {
                cleared_room_++;
                map_.removeRoom(map_.getPlayerRow(), map_.getPlayerCol());
                explored_space_++;
            }
            open_door_ = false;
        }
        else
        {
            int rand_mem;
            do
            {
                rand_mem = rand() % (CAPACITY - 1) + 1; // from 1 to 4
            } while (party_[rand_mem].getFullnessLevel() <= 0);
            party_[rand_mem].setFullnessLevel(-50);
            party_size_--;
            cout << "You have lost the door puzzle." << endl
                 << party_[rand_mem].getName() << " has been held captive. The party loses one member." << endl
                 << "You now have " << party_size_ << " members." << endl
                 << endl;
        }
    }
}

bool Action::roomSpace()
{
    int option;
    cout << "Select one:" << endl
         << "1. Move" << endl
         << "2. Open the door" << endl
         << "3. Give up" << endl
         << endl
         << "> ";
    cin >> option;
    cout << endl;
    if (option == 1)
    {
        move();
        turns_++;
        cout << endl;
        return endGame(); // return true or false
    }
    else if (option == 2)
    {
        openDoor();
        turns_++;
        cout << endl;
        return endGame();
    }
    else
    {
        turns_++;
        cout << "You have given up:( Sorry that you could not make it out of the dungeon." << endl
             << endl;
        return true;
    }
}

string Action::spaceType()
{
    if (map_.isNPCLocation(map_.getPlayerRow(), map_.getPlayerCol()) == true)
        return "NPC";
    else if (map_.isRoomLocation(map_.getPlayerRow(), map_.getPlayerCol()) == true)
        return "Room";
    else if (map_.isFreeSpace(map_.getPlayerRow(), map_.getPlayerCol()) == true)
        return "Free";
    return "";
}

void Action::printStatistics()
{
    ofstream out_file;
    out_file.open("statistics.txt");
    if (out_file.is_open())
    {
        out_file << "Leader: " << party_[0].getName() << " | Surviving member(s): ";
        for (int i = 1; i < CAPACITY; i++)
        {
            if (party_[i].getFullnessLevel() > 0)
            {
                out_file << party_[i].getName() << "  ";
            }
        
        }
        out_file << endl;
        out_file << "Number of rooms cleared: " << cleared_room_ << endl;
        out_file << "Gold pieces remaining: " << menu_.getGold() << endl;
        out_file << "Treasure items in the party's inventory:  R: " << menu_.getRing() << " | N: " << menu_.getNecklace() << " | B: " << menu_.getBracelet() << " | C: " << menu_.getCirclet() << " | G: " << menu_.getGoblet() << endl;
        out_file << "Number of spaces explored: " << explored_space_ << endl;
        out_file << "Number of monsters defeated: " << monster_defeated_ << endl;
        out_file << "Number of turns elapsed: " << turns_ << endl;
    }
    else
        cout << "File fails to open." << endl;
    
    out_file.close();
}