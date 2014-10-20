#include "gamepairs.hpp"
#include "gamepairstextdisplay.hpp"

int main()
{
    std::list<Player> players = { Player("Szymon"), Player() };
    GamePairsDisplay *displayDelegate = new GamePairsTextDisplay();

    GamePairs(players, displayDelegate).play();

    return 0;
}
