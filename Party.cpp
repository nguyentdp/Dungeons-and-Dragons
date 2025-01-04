#include "Party.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// default constructor
Party::Party() {} 

// parametized constructor
Party::Party(string name, int fullness)
{
    names_ = name;
    fullness_ = fullness;
}

// return name
string Party::getName() const
{
    return names_;
}

// return fullness level
int Party::getFullnessLevel() const
{
    return fullness_;
}

/** Parameter: level (int)
 * Algorithm:
 * Set fullness_ += level
 * If fulness_ is less than or equal 0
 *      set fullness_ = 0
 */
void Party::setFullnessLevel(int level)
{
    fullness_ += level;
    if (fullness_ <= 0)
        fullness_ = 0;
}

/** Parameters: chance (int), level (int)
 * Algorithm:
 * random = a random number from 1 - 100
 * if random less than or equal chance
 *      fulness_ += level
 *      if calculated fullness_ greater or equal to 50
 *          fullness_ = 50
 *          print notification
 *      else if fullness_ > 0 and less than or equal 10
 *          print warning
 *      else if fullness_ less than or equal 0
 *          print notification
 */
void Party::fullnessChange(int chance, int level) // return true if leader dies
{
    srand((unsigned int)time(0));
    int random = rand() % 100 + 1;
    if (random <= chance)
    {
        fullness_ += level;
        if (fullness_ >= 50) // 50 is max
        {
            fullness_ = 50;
            cout << names_ << "'s fullness level has been maximized." << endl
                 << endl;
        }
        else if (fullness_ > 0 && fullness_ <= 10)
            cout << "Warning: " << names_ << " is on the brink of starvation! You should cook and eat some food!" << endl
                 << endl;
        else if (fullness_ <= 0)
            cout << "OH NO! " << names_ << " has died of hunger!" << endl
                 << endl;
    }
}