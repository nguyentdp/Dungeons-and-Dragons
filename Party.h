#ifndef PARTY_H
#define PARTY_H
#include <string>
#include <vector>

using namespace std;

class Party
{

public:
    Party();                          // default constructor
    Party(string name, int fullness); // paramertized constructor

    //setters
    void setFullnessLevel(int level);

    //getters
    int getFullnessLevel() const;
    int getPartySize();
    string getName() const;

    //others
    void printFullnessStatus();
    void fullnessChange(int chance, int level);

private:
    string names_;     // name of member
    int fullness_ = 0; // member's fullness level
};

#endif