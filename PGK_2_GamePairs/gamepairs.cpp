#include "gamepairs.hpp"
#include <iostream>
#include <algorithm>

GamePairs::GamePairs(std::list<Player> players, std::list<Card> cards)
    : players(players), board(cards) {}

void GamePairs::play()
{
    gameBegin();

    while (enoughCardsForNextRound())
    {
        nextRound();
        showRound();

        tryTakeCards(cards().front(), cards().front());

    }

    showScores();

    gameEnd();
}

void GamePairs::nextPlayer()
{
    static std::list<Player>::iterator it = players.end();

    ++it;
    if (it == players.end()) it = players.begin();

    currentPlayer = &*it; // REVIEW: Better idea anybody?
}

std::list<Card>& GamePairs::cards()
{
    return board.cards;
}

std::list<Card> GamePairs::frequentCards()
{
    const std::list<Card> frequentCards = {
        Card(RED),    Card(RED),
        Card(YELLOW), Card(YELLOW),
        Card(GREEN),  Card(GREEN),
        Card(BLUE),   Card(BLUE),
        Card(PURPLE), Card(PURPLE),
        Card(BLACK),  Card(BLACK),
        Card(WHITE),  Card(WHITE),
        Card(ORANGE), Card(ORANGE)
    };

    return frequentCards;
}

void GamePairs::gameBegin()
{
    std::cout << "Starting game" << std::endl;
}

inline bool GamePairs::enoughCardsForNextRound()
{
    return cards().size() >= 2;
}

inline void GamePairs::nextRound()
{
    ++round;
    nextPlayer();
}

void GamePairs::tryTakeCards(Card& card1, Card& card2)
{
    if (!card1.hasSameColorAs(card2))
    {
        // TODO: virtual method
        //*showCurrentPlayerFail();
        return;
    }

    currentPlayer->incrementScore();
    std::cout << "Player " << currentPlayer->name << " correctly chosen two cards" << std::endl;
    // WARN: In line below I assume that for each present color exactly 2 instances exist in cards().
    //       If there is more of them it will remove all instances of the color. Not only selected two.
    cards().remove_if([&] (Card& card)->bool { return card.hasSameColorAs(card1); });

    // TODO: virtual method
    //showurrentPlayerSuccess();
}

void GamePairs::showRound()
{
    std::cout << "Round: " << round << "\t Turn: " << currentPlayer->name << " (" << currentPlayer->score << ")" << std::endl;
}

void GamePairs::showScores()
{
    for (const Player& player : players)
    {
        std::cout << player.name << ":\t" << player.score << std::endl;
    }
}

void GamePairs::gameEnd()
{
    std::cout << "Game has just finished" << std::endl;
}
