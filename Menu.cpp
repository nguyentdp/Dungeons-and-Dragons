// #include "Menu.h"
#include "Inventory.h"
#include <string>
#include <iostream>
using namespace std;

//use number of room cleared to increase prices

// Default constructor, prices will be set to initial prices when called
Menu::Menu() {}

/** Parameters: quantiy (int), item (string)
 * Agorithm: 
 * taking the quanity and the name of the item
 * loop throught the items_[] that contains the names of all items
 * if the name matches item, find the price of the item saved in prices_[] at same index
 * multiply the price to quantity and return the result
 */
int Menu::getPrice(int cleared_room, int quantity, string item)
{
    int price;
    for (int i = 0; i < items_size_; i++)
    {
        if (item == items_[i])
            if (cleared_room == 0)
                price = prices_[i] * quantity;
            else if (cleared_room == 1)
                price = prices_[i] * 1.25 * quantity;
            else if (cleared_room == 2)
                price = prices_[i] * 1.5 * quantity;
            else if (cleared_room == 3)
                price = prices_[i] * 1.75 * quantity;
            else if (cleared_room == 4)
                price = prices_[i] * 2 * quantity;
            else if (cleared_room == 5)
                price = prices_[i] * 2.25 * quantity;
    }
    return price;
}

/** prices_ array contains 15 elements with the following indexes represent different items' prices:
 * 0: Ingredient 
 * 1: Ceramic Pot 
 * 2: Stone Club
 * 3: Iron Spear
 * 4: Frying Pan
 * 5: Cauldron
 * 6: Mythril Rapier 
 * 7: Armor
 * 8: Flaming Battle-Axe
 * 9: Vorpal Longsword
 * 10: Ring
 * 11: Necklace
 * 12: Bracelet
 * 13: Circlet
 * 14: Goblet

 * Agorithm:
 * put in object and quality
 * get the object price * quality
 * gold - the calculation
 * if >= 0, print sucessfully purchased
 * else, print not enough gold
 */
void Menu::makePurchase(int cleared_room, int quantity, string item)
{
    int price = getPrice(cleared_room, quantity, item);
    int index = 0;
    for (int i = 0; i < items_size_; i++)
    {
        if (item == items_[i])
            index = i;
    }
    if (getGold() >= price) // current gold is greater or equal to the price
    {
        setGold(-price);
        cout << "Thank you for your patronage! What else can I get for you?" << endl << endl;
        if (index == 0)
            setIngredients(quantity); // inventory_ has been updated
        else if (index == 1)
            setCeramicPot(quantity);
        else if (index == 2)
            setStoneClub(quantity);
        else if (index == 3)
            setIronSpear(quantity);
        else if (index == 4)
            setFryingPan(quantity);
        else if (index == 5)
            setCauldron(quantity);
        else if (index == 6)
            setMythrilRapier(quantity);
        else if (index == 7)
            setArmor(quantity);
        else if (index == 8)
            setFlamingBattleAxe(quantity);
        else if (index == 9)
            setVorpalLongsword(quantity);
    }
    else
        cout << "Not enough gold. Please choose another quantity." << endl << endl;
}

void Menu::printIngredientMenu(int cleared_room)
{
    int quantity;
    char confirm;
    do
    {
        cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl
             << endl
             << "> ";
        cin >> quantity;
        cout << endl;
        if (quantity == 0)
            break;
        else if (quantity % 5 == 0)
        {
            cout << "You want to buy " << quantity << " kg of ingredients for " << getPrice(cleared_room, quantity, "Ingredient") << " Gold? (y/n)" << endl
                 << endl
                 << "> ";
            cin >> confirm;
            cout << endl;
            if (confirm == 'y')
                makePurchase(cleared_room, quantity, "Ingredient");
        }
        else // includes negative case
            cout << "Please enter a positive mulitple of 5" << endl << endl;
    } while ((quantity % 5 != 0) || confirm != 'y');
}

void Menu::printCookwareMenu(int cleared_room)
{
    cout << "I have a several types of cookware, which one would you like?" << endl
         << "Each type has a different probability of breaking when used, marked with (XX%)." << endl
         << endl;
    int option, quantity;
    char confirm;
    do
    {
        cout << "Choose one of the following:" << endl
             << " 1. (25%) Ceramic Pot [2 Gold]" << endl
             << " 2. (10%) Frying Pan [10 Gold]" << endl
             << " 3. ( 2%) Cauldron [20 Gold]" << endl
             << " 4. Cancel" << endl
             << endl
             << "> ";
        cin >> option;
        cout << endl;
        if (option == 4)
            break;
        else
        {
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl
                 << endl
                 << "> ";
            cin >> quantity;
            cout << endl;
            if (quantity > 0)
            {
                if (option == 1)
                {
                    cout << "You want to buy " << quantity << " Ceramic Pot(s) for " << getPrice(cleared_room, quantity, "Ceramic Pot") << " Gold? (y/n)" << endl
                         << endl
                         << "> ";
                    cin >> confirm;
                    cout << endl;
                    if (confirm == 'y')
                        makePurchase(cleared_room, quantity, "Ceramic Pot");
                }
                else if (option == 2)
                {
                    cout << "You want to buy " << quantity << " Frying Pan(s) for " << getPrice(cleared_room, quantity, "Frying Pan") << " Gold? (y/n)" << endl
                         << endl
                         << "> ";
                    cin >> confirm;
                    cout << endl;
                    if (confirm == 'y')
                        makePurchase(cleared_room, quantity, "Frying Pan");
                }
                else
                {
                    cout << "You want to buy " << quantity << " Cauldron(s) for " << getPrice(cleared_room, quantity, "Cauldron") << " Gold? (y/n)" << endl
                         << endl
                         << "> ";
                    cin >> confirm;
                    cout << endl;
                    if (confirm == 'y')
                        makePurchase(cleared_room, quantity, "Cauldron");
                }
            }
            else if (quantity < 0) //include invalid values
                cout << "Please enter a positive integer." << endl
                     << endl;
        }
    } while (quantity <= 0 && confirm != 'y');
}

void Menu::printWeaponsMenu(int cleared_room)
{
    cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl
         << "Note that some of them provide you a special bonus in combat, marked by a(+X)." << endl << endl;
    int option, quantity;
    char confirm;
    do
    {
        cout << "Choose one of the following:" << endl
             << " 1. Stone Club[2 Gold]" << endl
             << " 2. Iron Spear[2 Gold]" << endl
             << " 3.(+1) Mythril Rapier [5 Gold]" << endl
             << " 4.(+2) Flaming Battle-Axe [15 Gold]" << endl
             << " 5.(+3) Vorpal Longsword [50 Gold]" << endl
             << " 6. Cancel" << endl
             << endl
             << "> ";
        cin >> option;
        cout << endl;

        if (option == 6)
            break;
        else
        {
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl
                 << endl
                 << "> ";
            cin >> quantity;
            cout << endl;
            if (quantity > 0)
            {
                if (option == 1)
                {
                    cout << "You want to buy " << quantity << " Stone Club(s) for " << getPrice(cleared_room, quantity, "Stone Club") << " Gold? (y/n)" << endl
                         << endl
                         << "> ";
                    cin >> confirm;
                    cout << endl;
                    if (confirm == 'y')
                        makePurchase(cleared_room, quantity, "Stone Club");
                }
                else if (option == 2)
                {
                    cout << "You want to buy " << quantity << " Iron Spear(s) for " << getPrice(cleared_room, quantity, "Iron Spear") << " Gold? (y/n)" << endl
                         << endl
                         << "> ";
                    cin >> confirm;
                    cout << endl;
                    if (confirm == 'y')
                        makePurchase(cleared_room, quantity, "Iron Spear");
                }
                else if (option == 3)
                {
                    cout << "You want to buy " << quantity << " (+1) Mythril Rapier(s) for " << getPrice(cleared_room, quantity, "Mythril Rapier") << " Gold? (y/n)" << endl
                         << endl
                         << "> ";
                    cin >> confirm;
                    cout << endl;
                    if (confirm == 'y')
                        makePurchase(cleared_room, quantity, "Mythril Rapier");
                }
                else if (option == 4)
                {
                    cout << "You want to buy " << quantity << " (+2) Flaming Battle-Axe(s) for " << getPrice(cleared_room, quantity, "Flaming Battle-Axe") << " Gold? (y/n)" << endl
                         << endl
                         << "> ";
                    cin >> confirm;
                    cout << endl;
                    if (confirm == 'y')
                        makePurchase(cleared_room, quantity, "Flaming Battle-Axe");
                }
                else
                {
                    cout << "You want to buy " << quantity << " (+3) Vorpal Longsword(s) for " << getPrice(cleared_room, quantity, "Vorpal Longsword") << " Gold? (y/n)" << endl
                         << endl
                         << "> ";
                    cin >> confirm;
                    cout << endl;
                    if (confirm == 'y')
                        makePurchase(cleared_room, quantity, "Vorpal Longsword");
                }
            }
            else if (quantity < 0) // for negative value
                cout << "Enter a positive integer" << endl;
        }

    } while (quantity <= 0 && confirm != 'y');
}

void Menu::printArmorMenu(int cleared_room)
{
    int quantity;
    char confirm;
    do
    {
        cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)" << endl
             << endl
             << "> ";
        cin >> quantity;
        cout << endl;
        if (quantity == 0)
            break;
        else if (quantity < 0) // for negative values
            cout << "Enter a positive integer" << endl;
        else
        {
            cout << "You want to buy " << quantity << " suit(s) of armor for " << getPrice(cleared_room, quantity, "Armor") << " Gold? (y/n)" << endl
                 << endl
                 << "> ";
            cin >> confirm;
            cout << endl;
            if (confirm == 'y')
                makePurchase(cleared_room, quantity, "Armor");
        }
    } while (confirm != 'y');
}

void Menu::sellTreasure()
{
    int option, quantity;
    do
    {
        cout << "Choose one of the following you'd like to sell:" << endl
             << " 1. Silver ring (R) - 10 gold pieces each" << endl
             << " 2. Ruby necklace (N) - 20 gold pieces each" << endl
             << " 3. Emerald bracelet (B) - 30 gold pieces each" << endl
             << " 4. Diamond circlet (C) - 40 gold pieces each" << endl
             << " 5. Gem-encrusted goblet (G) - 50 gold pieces each" << endl
             << " 6. Cancel" << endl
             << endl
             << "> ";
        cin >> option;
        cout << endl;
        if (option == 6)
            return;
        char confirm;
        do
        {
            cout << "How many pieces of treasures would you like to sell? (Enter a positive integer, or 0 to cancel)" << endl
                 << endl
                 << "> ";
            cin >> quantity;
            cout << endl;
            if (quantity == 0)
                break;
            else if (quantity < 0) // for negative values
                cout << "Enter a positive integer" << endl << endl; 
            else
            {
                int price = 0;
                if (option == 1)
                {
                    if (getRing() < quantity)
                        cout << "You have less than " << quantity << " Silver ring(s). Please choose another quantity." << endl << endl;
                    else
                    {
                        price = getPrice(0, quantity, "Ring");
                        cout << "You want to sell " << quantity << " Silver ring(s) for " << price << " Gold? (y/n)" << endl << endl;
                        cin >> confirm;
                        cout << endl;
                        if (confirm == 'y')
                        {
                            setGold(price);     // adding price to total gold
                            setRing(-quantity); // taking out quantity amount from the number of owned ring
                            cout << "You have successfully sold your treasure(s). What else can I get for you?" << endl << endl;
                        }
                    }
                }
                if (option == 2)
                {
                    if (getNecklace() < quantity)
                        cout << "You have less than " << quantity << " Ruby necklace(s). Please choose another quantity." << endl << endl;
                    else
                    {
                        price = getPrice(0, quantity, "Necklace");
                        cout << "You want to sell " << quantity << " Ruby necklace(s) for " << price << " Gold? (y/n)" << endl << endl;
                        cin >> confirm;
                        cout << endl;
                        if (confirm == 'y')
                        {
                            setGold(price);         // adding price to total gold
                            setNecklace(-quantity); // taking out quantity amount from the number of owned necklace
                            cout << "You have successfully sold your treasure(s). What else can I get for you?" << endl << endl;
                        }
                    }
                }
                if (option == 3)
                {
                    if (getBracelet() < quantity)
                        cout << "You have less than " << quantity << " Emerald bracelet(s). Please choose another quantity." << endl << endl;
                    else
                    {
                        price = getPrice(0, quantity, "Bracelet");
                        cout << "You want to sell " << quantity << " Emerald bracelet(s) for " << price << " Gold? (y/n)" << endl << endl;
                        cin >> confirm;
                        cout << endl;
                        if (confirm == 'y')
                        {
                            setGold(price);         // adding price to total gold
                            setBracelet(-quantity); // taking out quantity amount from the number of owned bracelet
                            cout << "You have successfully sold your treasure(s). What else can I get for you?" << endl << endl;
                        }
                    }
                }
                if (option == 4)
                {
                    if (getCirclet() < quantity)
                        cout << "You have less than " << quantity << " Diamond circlet(s). Please choose another quantity." << endl << endl;
                    else
                    {
                        price = getPrice(0, quantity, "Circlet");
                        cout << "You want to sell " << quantity << " Diamond circlet(s) for " << price << " Gold? (y/n)" << endl << endl;
                        cin >> confirm;
                        cout << endl;
                        if (confirm == 'y')
                        {
                            setGold(price);        // adding price to total gold
                            setCirclet(-quantity); // taking out quantity amount from the number of owned circlet
                            cout << "You have successfully sold your treasure(s). What else can I get for you?" << endl << endl;
                        }
                    }
                }
                if (option == 5)
                {
                    if (getGoblet() < quantity)
                        cout << "You have less than " << quantity << " Gem-encrusted goblet(s). Please choose another quantity." << endl << endl;
                    else
                    {
                        price = getPrice(0, quantity, "Goblet");
                        cout << "You want to sell " << quantity << " Gem-encrusted goblet(s) for " << price << " Gold? (y/n)" << endl << endl;
                        cin >> confirm;
                        cout << endl;
                        if (confirm == 'y')
                        {
                            setGold(price);       // adding price to total gold
                            setGoblet(-quantity); // taking out quantity amount from the number of owned goblet
                            cout << "You have successfully sold your treasure(s). What else can I get for you?" << endl << endl;
                        }
                    }
                }
            }
        } while (confirm != 'y');

    } while (quantity <= 0);
}
