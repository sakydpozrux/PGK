#include "gamepairs.hpp"
#include "gamepairsopengldisplay.hpp"
#include "gamepairstextdisplay.hpp"

#define DISPLAY_GL true

int main()
{
    GamePairsDisplay *displayDelegate;

    if (DISPLAY_GL)
        displayDelegate = new GamePairsOpenGLDisplay();
    else
        displayDelegate = new GamePairsTextDisplay();

    GamePairs("Player", displayDelegate).play();

    return 0;
}
