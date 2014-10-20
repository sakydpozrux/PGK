#include "gamepairs.hpp"
#include "gamepairsopengldisplay.hpp"

int main()
{
    std::list<Player> players = { Player("Szymon"), Player() };
    GamePairsDisplay *displayDelegate = new GamePairsOpenGLDisplay();

    GamePairs(players, displayDelegate).play();

    return 0;
}
