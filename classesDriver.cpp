/* Ignore this file. For testing purposes only */

#include "Action.h"
#include "Items.h"
#include "Misfortunes.h"
#include "Monsters.h"
#include "Map.h"
#include "Party.h"
#include <cassert>

using namespace std;

int main()
{
    // Action class
    Action action = Action();
    assert(action.FoundKey() == false);

    // Items class (getCookware)
    // expect output: P: 2 | F: 0 | C: 0
    Items item = Items();
    item.setCeramicPot(2);
    item.getCookware();
    item.setIngredients(10);
    assert(item.getIngredients() == 10);

    // Party class
    Party member = Party();
    assert(member.getLeaderFullness() == 50);
    assert(member.getGold() == 100);
}