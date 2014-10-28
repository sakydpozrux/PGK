#include "gamepairs.hpp"
#include <chrono>
#include <thread>

const std::chrono::milliseconds kPauseDuration(500);
const std::chrono::milliseconds kBeforeQuitDuration(5000);

GamePairs::GamePairs(std::string playerName,
                     GamePairsDisplay *aDisplayDelegate,
                     std::vector<Card> cards)
    : player(playerName), board(cards), displayDelegate(aDisplayDelegate)
{
    displayDelegate->setPlayer(&player);
    displayDelegate->setBoard(&board);
}

GamePairs::~GamePairs()
{
    delete displayDelegate;
}

void GamePairs::mainGameLoop()
{
    displayDelegate->showRound(round);
    displayDelegate->showBoard();

    Card& cardFirst  = displayDelegate->letUserChooseCard(cards());
    Card& cardSecond = displayDelegate->letUserChooseCard(cards());

    if (cardFirst.isSameCard(cardSecond))
        return cancelSelection(cardFirst, cardSecond);

    if (tryTakeCards(cardFirst, cardSecond))
    {
        displayDelegate->showCurrentPlayerSuccess();
    } else {
        displayDelegate->showCurrentPlayerFail();
        nextRound();
    }
}

void GamePairs::play()
{
    displayDelegate->gameBegin();

    while (board.enoughCardsForNextRound())
        mainGameLoop();

    displayDelegate->showScore();

    std::this_thread::sleep_for(kBeforeQuitDuration);
    displayDelegate->gameEnd();
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

void GamePairs::cancelSelection(Card& cardFirst, Card& cardSecond)
{
    cardFirst.setVisible(false);
    cardSecond.setVisible(false);
}

inline void GamePairs::nextRound()
{
    ++round;
}

bool GamePairs::tryTakeCards(Card& card1, Card& card2)
{
    card1.setVisible(true);
    card2.setVisible(true);
    displayDelegate->showBoard();

    std::this_thread::sleep_for(kPauseDuration);
    cancelSelection(card1, card2);

    if (!validChoice(card1, card2))
        return false;

    player.incrementScore();

    board.decreaseVisibleCardsCounter();
    card1.removeFromBoard();
    card2.removeFromBoard();

    return true;
}

bool GamePairs::cardsArePresent(const Card& card1, const Card& card2) const
{
    return card1.isPresent() && card2.isPresent();
}

bool GamePairs::validChoice(const Card& card1, const Card& card2) const
{
    return card1.hasSameColorAs(card2) && !card1.isSameCard(card2) && cardsArePresent(card1, card2);
}
