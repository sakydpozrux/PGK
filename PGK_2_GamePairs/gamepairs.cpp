#include "gamepairs.hpp"

GamePairs::GamePairs(std::list<Player> players,
                     GamePairsDisplay *aDisplayDelegate,
                     std::vector<Card> cards)
    : players(players), board(cards), displayDelegate(aDisplayDelegate) {}

GamePairs::~GamePairs()
{
    delete displayDelegate;
}

void GamePairs::play()
{
    displayDelegate->gameBegin();

    while (board.enoughCardsForNextRound())
    {
        nextRound();
        displayDelegate->showRound(round, currentPlayer, board);

        if (tryTakeCards(displayDelegate->letUserChooseCard(cards()),
                         displayDelegate->letUserChooseCard(cards())))
        {
            displayDelegate->showCurrentPlayerSuccess(currentPlayer);
        } else {
            displayDelegate->showCurrentPlayerFail(currentPlayer);
        }
    }

    displayDelegate->showScores(players);
    displayDelegate->gameEnd();
}

void GamePairs::nextPlayer()
{
    static std::list<Player>::iterator it = players.end();

    if (++it == players.end()) it = players.begin();

    currentPlayer = &*it; // REVIEW: Better idea anybody?
}

std::vector<Card>& GamePairs::cards()
{
    return board.cards;
}

std::vector<Card> GamePairs::frequentCards()
{
    static const std::vector<Card> frequentCards = {
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

inline void GamePairs::nextRound()
{
    ++round;
    nextPlayer();
}

bool GamePairs::tryTakeCards(Card& card1, Card& card2)
{
    if (!validChoice(card1, card2))
        return false;

    currentPlayer->incrementScore();

    card1.presentOnBoard = card2.presentOnBoard = false;
    board.decrementPresentCardsCounter();
    board.decrementPresentCardsCounter();

    return true;
}

bool GamePairs::cardsArePresent(const Card& card1, const Card& card2) const
{
    return card1.presentOnBoard && card2.presentOnBoard;
}

bool GamePairs::validChoice(const Card& card1, const Card& card2) const
{
    return card1.hasSameColorAs(card2) && !card1.isSameCard(card2) && cardsArePresent(card1, card2);
}
