#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <iostream>
using namespace std;

//base class
class Inventory
{
public:
    Inventory(); //default constructor

    //getters and setters of cookwares
    void setCeramicPot(int amount);
    void setFryingPan(int amount);
    void setCauldron(int amount);
    int getCeramicPot() const;
    int getFryingPan() const;
    int getCauldron() const;

    //getter and setter for ingredients
    void setIngredients(int kg);
    int getIngredients() const;

    //getters and setters for weapons
    void setStoneClub(int amount);
    void setIronSpear(int amount);
    void setMythrilRapier(int amount);
    void setFlamingBattleAxe(int amount);
    void setVorpalLongsword(int amount);
    int getNumWeapons() const; // unsure
    int getStoneClub() const;
    int getIronSpear() const;
    int getMythrilRapier() const;
    int getFlamingBattleAxe() const;
    int getVorpalLongsword() const;

    //getters and setters for treasures
    int getRing() const;
    int getNecklace() const;
    int getBracelet() const;
    int getCirclet() const;
    int getGoblet() const;
    void setRing(int amount);
    void setNecklace(int amount);
    void setBracelet(int amount);
    void setCirclet(int amount);
    void setGoblet(int amount);

    // getters and setters for armor
    void setArmor(int armor);
    int getArmor();

    //getters and setters for gold
    int getGold() const;
    void setGold(int gold);

    //others
    void printInventoryStatus();
    bool difWeapons();


private:
    //ingredient
    int ingredients_ = 0;
    // cookwares
    int ceramic_pot_ = 0;
    int frying_pan_ = 0;
    int cauldron_ = 0;
    // weapons
    int stone_club_ = 0;
    int iron_spear_ = 0;
    int mythril_rapier_ = 0;
    int flaming_battleaxe_ = 0;
    int vorpal_longsword_ = 0;
    int num_weapons_; // maximun of 5 weapons
    vector<int> weapons_ = {stone_club_, iron_spear_, mythril_rapier_, flaming_battleaxe_, vorpal_longsword_};
    //armor
    int armor_ = 0;
    // treasures
    int ring_ = 0;
    int necklace_ = 0;
    int bracelet_ = 0;
    int circlet_ = 0;
    int goblet_ = 0;
    //gold
    int gold_ = 100;
};


//devired class
class Menu : public Inventory
{
public:
    Menu(); // default parameter

    //getter
    int getPrice(int cleared_room, int quantity, string item);

    //other
    void makePurchase(int cleared_room, int quantity, string item);
    void printIngredientMenu(int cleared_room);
    void printCookwareMenu(int cleared_room);
    void printWeaponsMenu(int cleared_room);
    void printArmorMenu(int cleared_room);
    void sellTreasure();

private:
    int static const items_size_ = 15; // all the items from inventory
    // prices_ stores the price of each item that its name stores in items with the same index
    int prices_[items_size_] = {1, 2, 2, 2, 10, 20, 5, 5, 15, 50, 10, 20, 30, 40, 50};
    string items_[items_size_] = {"Ingredient", "Ceramic Pot", "Stone Club", "Iron Spear", "Frying Pan", "Cauldron",
                                  "Mythril Rapier", "Armor", "Flaming Battle-Axe", "Vorpal Longsword", "Ring", "Necklace", "Bracelet", "Circlet", "Goblet"};
};

#endif