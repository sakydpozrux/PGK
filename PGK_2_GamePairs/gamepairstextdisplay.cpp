#include "gamepairstextdisplay.hpp"
#include "player.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

void GamePairsTextDisplay::gameBegin()
{
    std::cout << "Starting game" << std::endl;
}

void GamePairsTextDisplay::showRound(const unsigned int round)
{
    std::cout << "Round: " << round
              << "\t Turn: " << player->name
              << " (" << player->score << ")" << std::endl;

    showBoard();
}

void GamePairsTextDisplay::showBoard()
{
    std::stringstream stream;

    for (const std::vector<Card>& horizontalRow : board->cardsInRows())
        printableRowToStream(horizontalRow, stream);

    std::cout << stream.str();
}

Card& GamePairsTextDisplay::letUserChooseCard(std::vector<Card>& cards)
{
    std::cout << "Choose card: ";

    unsigned int id;
    std::cin >> id;

    Card& card = *std::find_if(cards.begin(),
                               cards.end(),
                               [&](const Card card)->bool { return card.uniqueId == id; });

    return card;
}

void GamePairsTextDisplay::showCurrentPlayerSuccess()
{
    std::stringstream stream;

    stream << "Player " << player->name;
    stream << " successfuly chooses two identical cards." << std::endl;

    std::cout << stream.str();
}

void GamePairsTextDisplay::showCurrentPlayerFail()
{
    std::stringstream stream;

    stream << "Player " << player->name;
    stream << " fails at choosing identical cards." << std::endl;

    std::cout << stream.str();
}

void GamePairsTextDisplay::showScore()
{
    std::cout << player->name << ":\t" << player->score << std::endl;
}

void GamePairsTextDisplay::gameEnd()
{
    std::cout << "Game has just finished" << std::endl;
}

void GamePairsTextDisplay::printableRowToStream(const std::vector<Card>& horizontalRow,
                                     std::stringstream& stream) const
{
    for (const Card& card : horizontalRow)
        stream << card.toString();

    stream << std::endl;
}
