#include "Monster.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// default constructor
Monster::Monster() {}

// return sorcerer's anger level
int Monster::getSorcererAnger() const
{
    return sorcerer_anger_;
}

/** Paremeter: level (int)
 * set sorcerer_anger_ += level
 */
void Monster::setSorcererAnger(int level)
{
    sorcerer_anger_ += level;
}

/** included to support other member functions
 * Splits a line into pieces of information with a specific seperator and stores them in an array.
 * Parameters: input_string (string), seperator (char), arr[] (string), arr_size (int)
 * If the input_string is an empty string, return 0.
 * Otherwise, define an empty string str and initialize curr_size to 0 as int.
 * Use a for loop to loop through every character of the input_string until it reaches the end of the string:
 * Pass the characters to empty string str till a character matches the separator.
 * If a character matches a separator and curr_size less than arr_size (the capacity size of arr[]), insert 
   whatever is in str to the array with the index curr_size, cur_size increments, str is set back to empty string.
 * If curr_size is greater or equals to arr_size, return -1.
 * After the last separator, pass whatever is left to str and insert it to arr[], curr_size increments.
 * Return the value of curr_size.
 */
int Monster::split(string input_string, char separator, string arr[], int arr_size)
{
    if (input_string == "")
        return 0;
    string str;
    int curr_size = 0;
    for (int i = 0; i < input_string.length(); i++)
    {
        if (input_string[i] != separator)
        {
            str += input_string[i];
        }
        else
        {
            if (curr_size < arr_size)
            {
                arr[curr_size] = str;
                curr_size++;
                str = "";
            }
            else
            {
                return -1;
            }
        }
    }
    arr[curr_size] = str;
    curr_size++;
    return curr_size;
}

/** Parameters: level (int), monster (string vector, reference)
 * open monsters.txt file
 * If file opens
 *      define line (string)
 *      while using getline to pass each line form in_file to line
 *          if split function is working and save information in arr[]
 *              if stoi(arr[1]) == level
 *                  add arr[0] to monster vector
 */
void Monster::monster(int level, vector<string> &monster)
{
    ifstream in_file;
    in_file.open("monsters.txt");
    string arr[2];
    if (in_file.is_open())
    {
        string line;
        while (getline(in_file, line))
        {
            if (split(line, ',', arr, 2) == 2)
            {
                if (stoi(arr[1]) == level)
                    monster.push_back(arr[0]);
            }
        }
    }
}

/** Algorithm:
 * define monster_name_ (string)
 * use monster() to save all the monsters with challenging level 1
 * random = random number from 0 to monster1_ vector current size
 * monster_name = monster1_[random]
 * erase the monster1_[random] from monster1_
 * Return: monster_name (string)
 */
string Monster::monsterOne()
{
    string monster_name;
    monster(1, monster1_);

    srand((unsigned int)time(0));
    int random = rand() % monster1_.size();

    monster_name = monster1_[random];
    monster1_.erase(monster1_.begin() + random);
    return monster_name;
}

/** Algorithm:
 * define monster_name_ (string)
 * use monster() to save all the monsters with challenging level 2
 * random = random number from 0 to monster2_ vector current size
 * monster_name = monster2_[random]
 * erase the monster2_[random] from monster2_
 * Return: monster_name (string)
 */
string Monster::monsterTwo()
{
    string monster_name;
    monster(2, monster2_);
    srand((unsigned int)time(0));
    int random = rand() % monster2_.size();
    monster_name = monster2_[random];
    monster2_.erase(monster2_.begin() + random);
    return monster_name;
}

/** Algorithm:
 * define monster_name_ (string)
 * use monster() to save all the monsters with challenging level 3
 * random = random number from 0 to monster3_ vector current size
 * monster_name = monster3_[random]
 * erase the monster3_[random] from monster3_
 * Return: monster_name (string)
 */
string Monster::monsterThree()
{
    string monster_name;
    monster(3, monster3_);
    srand((unsigned int)time(0));
    int random = rand() % monster3_.size();
    monster_name = monster3_[random];
    monster3_.erase(monster3_.begin() + random);
    return monster_name;
}

/** Algorithm:
 * define monster_name_ (string)
 * use monster() to save all the monsters with challenging level 4
 * random = random number from 0 to monster4_ vector current size
 * monster_name = monster4_[random]
 * erase the monster4_[random] from monster4_
 * Return: monster_name (string)
 */
string Monster::monsterFour()
{
    string monster_name;
    monster(4, monster4_);
    srand((unsigned int)time(0));
    int random = rand() % monster4_.size();

    monster_name = monster4_[random];
    monster4_.erase(monster4_.begin() + random);

    return monster_name;
}

/** Algorithm:
 * define monster_name_ (string)
 * use monster() to save all the monsters with challenging level 5
 * random = random number from 0 to monster5_ vector current size
 * monster_name = monster5_[random]
 * erase the monster5_[random] from monster5_
 * Return: monster_name (string)
 */
string Monster::monsterFive()
{
    string monster_name;
    monster(5, monster5_);
    srand((unsigned int)time(0));
    int random = rand() % monster5_.size();

    monster_name = monster5_[random];
    monster5_.erase(monster5_.begin() + random);

    return monster_name;
}

// return 0 if ties, 1 if wins, 2 if loses
/** Parameter: option (string)
 * random = random number from 1 - 3
 * if random = 1, shoot = rock
 * else if random = 2, shoot = paper
 * else if random = 3, shoot = scissors
 * if shoot = option, returns 0 (ties)
 * else if shoot = rock and option = paper, return 1 (win)
 *      else, return 2 (lose)
 * else if shoot = paper and option = scissors, return 1
 *      else, return 2
 * else if shoot = scissors and option = rock, return 1
 *      else, return 2
 * Return int
 */
int Monster::doorPuzzle(string option) 
{
    srand((unsigned int)time(0));
    int random = rand() % 3 + 1; //randomly pick between 1-3
    string shoot;
    if (random == 1)
    {
        shoot = "rock";
        cout << "rock!" << endl
             << endl;
    }
    else if (random == 2)
    {
        shoot = "paper";
        cout << "paper!" << endl
             << endl;
    }
    else if (random == 3)
    {
        shoot = "scissors";
        cout << "scissors!" << endl
             << endl;
    }

    if (shoot == option)
        return 0;
    else if (shoot == "rock")
    {
        if (option == "paper")
            return 1;
        else
            return 2;
    }
    else if (shoot == "paper")
    {
        if (option == "scissors")
            return 1;
        else
            return 2;
    }
    else if (shoot == "scissors")
    {
        if (option == "rock")
            return 1;
        else
            return 2;
    }
    return 2;
}

bool Monster::npcPuzzle() // return true if any riddle is solved
{
    ifstream in_file;
    in_file.open("riddles.txt");
    if (in_file.is_open())
    {
        string line;
        while (getline(in_file, line))
        {
            string arr[2];
            if (split(line, '~', arr, 2) == 2)
            {
                npc_riddle_.push_back(arr[0]);    // question
                riddle_answer_.push_back(arr[1]); // answer
            }
        }
        srand((unsigned int)time(0));
        string answer;
        int random;
        random = rand() % npc_riddle_.size();
        cout << "Here's the puzzle: " << npc_riddle_[random] << endl
             << endl
             << "You have one try. Please insert your answer: ";
        cin >> answer;
        if (answer == riddle_answer_[random])
        {
            cout << "CORRECT!" << endl
                 << endl;
            return true;
        }
        else
        {
            cout << "That's incorrect and I AM MAD. I'm going to summon a monster!" << endl
                 << endl;
            return false;
        }
    }
    else
        cout << "Out of riddles." << endl
             << endl;

    return false;
}
