#include <iostream>
#include "gamepairs.hpp"

int main()
{
    std::list<Player> players = { Player() };

    std::list<Card> cards;
    GamePairs pairs(players, cards);
    pairs.play();

    return 0;
}
