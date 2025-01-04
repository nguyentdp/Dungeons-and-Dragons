#ifndef MONSTER_H
#define MONSTER_H
#include <string>
#include <vector>

using namespace std;

class Monster
{
public:
    Monster(); //default constructor

    //setters
    void setSorcererAnger(int level);

    //getters
    int getSorcererAnger() const;

    //others
    int split(string input_string, char separator, string arr[], int arr_size);
    void monster(int level, vector<string> &monster);
    string monsterOne();
    string monsterTwo();
    string monsterThree();
    string monsterFour();
    string monsterFive();
    int doorPuzzle(string option);
    bool npcPuzzle();

private:
    int sorcerer_anger_ = 0;       // sorcerer's anger
    vector<string> monster1_;      // store monster with challenging rate 1
    vector<string> monster2_;      // store monster with challenging rate 2
    vector<string> monster3_;      // store monster with challenging rate 3
    vector<string> monster4_;      // store monster with challenging rate 4
    vector<string> monster5_;      // store monster with challenging rate 5
    vector<string> npc_riddle_;    //store NPC riddles
    vector<string> riddle_answer_; // store riddles' answers
};

#endif