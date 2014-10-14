#include "gamepairs.hpp"
#include <iostream>

GamePairs::GamePairs(std::list<Player> players, std::list<Card> cards)
    : players(players), board(cards), numberOfPlayers(players.size()) {}

void GamePairs::play()
{
    std::cout << "Starting game" << std::endl;
    if (cards().size() <= 2) return;

    // TODO: Everything is missing here.

    std::cout << "Game has just finished" << std::endl;
}

Player *GamePairs::nextPlayer()
{
    static std::list<Player>::iterator it = players.begin();
    Player *player = &*it; // REVIEW: Better idea anybody?

    if (++it == players.end()) it = players.begin();

    return player;
}

std::list<Card>& GamePairs::cards()
{
    return board.cards;
}
