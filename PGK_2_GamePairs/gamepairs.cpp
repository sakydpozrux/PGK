#include "gamepairs.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

GamePairs::GamePairs(std::list<Player> players, std::vector<Card> cards)
    : players(players), board(cards) {}

void GamePairs::play()
{
    gameBegin();

    while (board.enoughCardsForNextRound())
    {
        nextRound();
        showRound();

        tryTakeCards(letUserChooseCard(), letUserChooseCard()) ? showCurrentPlayerSuccess()
                                                               : showCurrentPlayerFail();
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

std::vector<Card>& GamePairs::cards()
{
    return board.cards;
}

std::vector<Card> GamePairs::frequentCards()
{
    const std::vector<Card> frequentCards = {
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

inline void GamePairs::nextRound()
{
    ++round;
    nextPlayer();
}

bool GamePairs::tryTakeCards(Card& card1, Card& card2)
{
    if (!card1.hasSameColorAs(card2) || card1.isSameCard(card2) || !card1.presentOnBoard || !card2.presentOnBoard) return false;

    currentPlayer->incrementScore();

    board.decrementPresentCardsCounter();
    board.decrementPresentCardsCounter();

    card1.presentOnBoard = card2.presentOnBoard = false;

    return true;
}

Card& GamePairs::letUserChooseCard()
{
    std::cout << "Choose card: ";

    unsigned int id;
    std::cin >> id;

    Card& card = *std::find_if(cards().begin(),
                               cards().end(),
                               [&](const Card card)->bool { return card.uniqueId == id; });
    //Card& card = board.cardsInRows().at(y).at(x);
    return card;
}

void GamePairs::showCurrentPlayerSuccess()
{
    std::stringstream stream;

    stream << "Player " << currentPlayer->name;
    stream << " successfuly chooses two identical cards." << std::endl;

    std::cout << stream.str();
}

void GamePairs::showCurrentPlayerFail()
{
    std::stringstream stream;

    stream << "Player " << currentPlayer->name;
    stream << " fails at choosing identical cards." << std::endl;

    std::cout << stream.str();
}

void GamePairs::showRound()
{
    std::cout << "Round: " << round << "\t Turn: " << currentPlayer->name << " (" << currentPlayer->score << ")" << std::endl;

    showBoard();
}

void GamePairs::showBoard()
{
    for (const std::vector<Card>& horizontalRow : board.cardsInRows())
    {
        for (const Card& card : horizontalRow)
        {
            if (card.presentOnBoard)
            {
                std::cout << "[" << card.uniqueId << "](" << card.color.r << "," << card.color.g << "," << card.color.b << "), ";
            }
            else
            {
                std::cout << "(NOTHING), ";
            }
        }
        std::cout << std::endl;
    }
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
