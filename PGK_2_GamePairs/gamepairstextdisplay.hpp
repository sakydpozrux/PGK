#ifndef GAMEPAIRSTEXTDISPLAY_HPP
#define GAMEPAIRSTEXTDISPLAY_HPP

#include "gamepairsdisplay.hpp"

class GamePairsTextDisplay : public GamePairsDisplay
{
public:
    GamePairsTextDisplay() {};
    virtual ~GamePairsTextDisplay() {};

    void gameBegin();
    void showRound(const unsigned int round,
                   Player *currentPlayer,
                   const Board& board);
    void showBoard(const Board& board);
    Card& letUserChooseCard(std::vector<Card>& cards);
    void showCurrentPlayerSuccess(const Player *currentPlayer);
    void showCurrentPlayerFail(const Player *currentPlayer);
    void showScores(const std::list<Player>& players);
    void gameEnd();

private:
    void printableRowToStream(const std::vector<Card>& horizontalRow, std::stringstream& stream) const;
};

#endif // GAMEPAIRSTEXTDISPLAY_HPP
