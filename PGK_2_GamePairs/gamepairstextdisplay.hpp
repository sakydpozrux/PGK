#ifndef GAMEPAIRSTEXTDISPLAY_HPP
#define GAMEPAIRSTEXTDISPLAY_HPP

#include "gamepairsdisplay.hpp"

class GamePairsTextDisplay : public GamePairsDisplay
{
public:
    GamePairsTextDisplay() {}
    virtual ~GamePairsTextDisplay() {}

    void gameBegin();
    void showRound(const unsigned int round);
    void showBoard();
    Card& letUserChooseCard(std::vector<Card>& cards);
    void showCurrentPlayerSuccess();
    void showCurrentPlayerFail();
    void showScore();
    void gameEnd();

private:
    void printableRowToStream(const std::vector<Card>& horizontalRow, std::stringstream& stream) const;
};

#endif // GAMEPAIRSTEXTDISPLAY_HPP
