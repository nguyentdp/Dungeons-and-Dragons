#include "Inventory.h"
#include <iostream>

using namespace std;

Inventory::Inventory() {}

//getters and setters for cookwares
void Inventory::setCeramicPot(int amount)
{
    ceramic_pot_ = amount;
    if (ceramic_pot_ < 0)
        ceramic_pot_ = 0;
}
void Inventory::setFryingPan(int amount)
{
    frying_pan_ = amount;
    if (frying_pan_ < 0)
        frying_pan_ = 0;
}
void Inventory::setCauldron(int amount)
{
    cauldron_ = amount;
    if (cauldron_ < 0)
        cauldron_ = 0;
}
int Inventory::getCeramicPot() const
{
    return ceramic_pot_;
}
int Inventory::getFryingPan() const
{
    return frying_pan_;
}
int Inventory::getCauldron() const
{
    return cauldron_;
}

//Getter and setter for treasures
int Inventory::getRing() const
{
    return ring_;
}
int Inventory::getNecklace() const
{
    return necklace_;
}
int Inventory::getBracelet() const
{
    return bracelet_;
}
int Inventory::getCirclet() const
{
    return circlet_;
}
int Inventory::getGoblet() const
{
    return goblet_;
}
void Inventory::setRing(int amount)
{
    ring_ += amount;
}
void Inventory::setNecklace(int amount)
{
    necklace_ += amount;
}
void Inventory::setBracelet(int amount)
{
    bracelet_ += amount;
}
void Inventory::setCirclet(int amount)
{
    circlet_ += amount;
}
void Inventory::setGoblet(int amount)
{
    goblet_ += amount;
}

//getter and setter for ingredients
void Inventory::setIngredients(int kg)
{
    ingredients_ += kg;
    if (ingredients_ < 0)
        ingredients_ = 0;
}
int Inventory::getIngredients() const
{
    return ingredients_;
}

//getters and setters for armor
void Inventory::setArmor(int amount)
{
    armor_ += amount;
    if (armor_ < 0)
        armor_ = 0;
}
int Inventory::getArmor()
{
    return armor_;
}

//getters and setters for weapons
void Inventory::setStoneClub(int amount)
{
    stone_club_ += amount;
    if (stone_club_ < 0)
        stone_club_ = 0;
}
void Inventory::setIronSpear(int amount)
{
    iron_spear_ += amount;
    if (iron_spear_ < 0)
        iron_spear_ = 0;
}
void Inventory::setMythrilRapier(int amount)
{
    mythril_rapier_ += amount;
    if (mythril_rapier_ < 0)
        mythril_rapier_ = 0;
}
void Inventory::setFlamingBattleAxe(int amount)
{
    flaming_battleaxe_ += amount;
    if (flaming_battleaxe_ < 0)
        flaming_battleaxe_ = 0;
}
void Inventory::setVorpalLongsword(int amount)
{
    vorpal_longsword_ += amount;
    if (vorpal_longsword_ < 0)
        vorpal_longsword_ = 0;
}
int Inventory::getNumWeapons() const
{
    return stone_club_ + iron_spear_ + mythril_rapier_ + flaming_battleaxe_ + vorpal_longsword_;
}
int Inventory::getStoneClub() const
{
    return stone_club_;
}
int Inventory::getIronSpear() const
{
    return iron_spear_;
}
int Inventory::getMythrilRapier() const
{
    return mythril_rapier_;
}
int Inventory::getFlamingBattleAxe() const
{
    return flaming_battleaxe_;
}
int Inventory::getVorpalLongsword() const
{
    return vorpal_longsword_;
}

bool Inventory::difWeapons()
{
    int count = 0;
    for (int i = 0; i < weapons_.size(); i++)
    {
        if (weapons_[i] > 0)
            count++;
    }
    if (count >= 2)
        return true;
    else
        return false;
}


//getter and setter for gold
int Inventory::getGold() const
{
    return gold_;
}

/** insert the amount of gold
 * if the amount is greater than the current golds, return false
 * else, golds += the amount. return true
 */
void Inventory::setGold(int price)
{
    if ((gold_ + price) < 0)
        gold_ = 0;    
    else
        gold_ += price;
}

void Inventory::printInventoryStatus()
{
    cout << "+-------------+" << endl
         << "| INVENTORY   |" << endl
         << "+-------------+" << endl
         << "| Gold        | " << getGold() << endl // using function and object of Inventory class
         << "| Ingredients | " << getIngredients() << endl
         << "| Cookware    | P: " << getCeramicPot() << " | F: " << getFryingPan() << " | C: " << getCauldron() << endl
         << "| Weapons     | C: " << getStoneClub() << " | S: " << getIronSpear() << " | R: " << getMythrilRapier() << " | B: " << getFlamingBattleAxe() << " | L: " << getVorpalLongsword() << endl
         << "| Armor       | " << getArmor() << endl
         << "| Treasures   | R: " << getRing() << " | N: " << getNecklace() << " | B: " << getBracelet() << " | C: " << getCirclet() << " | G: " << getGoblet() << endl;
}

