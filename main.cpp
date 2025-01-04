#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Party.h"
// #include "Menu.h"
#include "Inventory.h"
#include "Action.h"
#include "Monster.h"

using namespace std;

int main()
{
     Action action = Action();

     string leader_name, mem1_name, mem2_name, mem3_name, mem4_name;
     cout << "Wellcome to The Game of Dungeon Escape!" << endl
          << "Please enter your name: ";
     cin >> leader_name;
     cout << endl;

     cout << leader_name << ", you will be the leader of the party." << endl
          << "Please enter the names of the other four traveling companions:" << endl;
     cin >> mem1_name >> mem2_name >> mem3_name >> mem4_name;
     cout << endl;

     // define object party class Party using its parametized constructor
     action.setNames(leader_name);
     action.setNames(mem1_name);
     action.setNames(mem2_name);
     action.setNames(mem3_name);
     action.setNames(mem4_name);

     // merchant first words
     cout << "Between the 5 of you, you have 100 gold pieces." << endl
          << "You will need to spend the some of your money on the following items:" << endl
          << endl
          << "- INGREDIENTS: To cook food. *recommend purchasing 10kg per person*" << endl
          << "- COOKWARE: If you want to cook, you have to have cookware first." << endl
          << "- WEAPONS: To fend off monsters. *recommend purchasing 5 weapons (max) worth at least 5 gold pieces for each person*" << endl
          << "- ARMOR: Increases the chances of surviving a monster attack. *Recommend equipping 5 armors. Adding more armor on top of the maximum amount will not increase your chances further*" << endl
          << endl
          << "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way.But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price…" << endl;

     cout << endl;
     action.printMerchantMenu();

     cout << endl;
     cout << "You have now enter the dungeon. There are five locked rooms in the dungeon, each of which must be cleared by defeating the monster. After clearing all five rooms, the exit of the dungeon will unlock. Good luck!" << endl
          << endl;
     bool game_end = false;
     action.createRoom();
     action.creatNPC();
     do
     {
          action.printActionStatus();
          cout << endl;
          action.PrintMap();
          cout << endl;

          string space_type = action.spaceType();
          if (space_type == "NPC")
               game_end = action.npcSpace();
          else if (space_type == "Room")
               game_end = action.roomSpace();
          else if (space_type == "Free")
               game_end = action.normalSpace();
          game_end = action.misfortunes();

     } while (game_end != true);

     action.printStatistics();
     
     cout << "The game has ended. Thank you for playing!" << endl << endl
     << "+----------------+" << endl << "|   STATISTICS   |" << endl << "+----------------+" << endl;
     ifstream in_file;
     in_file.open("statistics.txt");
     if (!in_file.eof())
     {
          string line;
          while (getline(in_file, line))
          {
               cout << line << endl;
          }   
     }
}