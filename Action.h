#ifndef ACTION_H
#define ACTION_H
#include "Party.h"
#include "Monster.h"
#include "Inventory.h"
#include "Map.h"
using namespace std;

class Action
{
    public:
        Action();

        //setters

        // getters
        int getClearedRoom() const;
        int getKey() const;

        bool endGame();

        bool fightMonster();
        bool attack(int challenge_rate);

        void printMerchantMenu();

        void printActionStatus();

        void setNames(string name);

        void createRoom();
        void creatNPC();
        void PrintMap();

        bool normalSpace();
        bool npcSpace();
        bool roomSpace();

        void speakToNpc();
        void openDoor();

        void move();
        void investigate();
        bool giveup();
        void cookAndEat();

        bool misfortunes();

        string spaceType();

        void printStatistics();

    private:
        bool open_door_ = false;
        int cleared_room_ = 0;
        int key_ = 0;
        Monster monster_;
        int static const CAPACITY = 5;
        Party party_[CAPACITY];
        int party_size_ = 0;
        Menu menu_;
        Map map_;
        int explored_space_ = 0;
        int monster_defeated_ = 0;
        int turns_ = 0;
};
#endif