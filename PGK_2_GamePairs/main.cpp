#include <iostream>
#include "gamepairs.hpp"

int main()
{
    std::list<Player> players = { Player("Szymon"), Player() };

    GamePairs pairs(players);
    pairs.play();

    return 0;
}
