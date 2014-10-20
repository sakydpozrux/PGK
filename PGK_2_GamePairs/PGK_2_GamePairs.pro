CONFIG += c++11
CONFIG += -Wall
CONFIG += -Weffc++
CONFIG += -O2

SOURCES += \
    main.cpp \
    gamepairs.cpp \
    board.cpp \
    player.cpp \
    card.cpp \
    color.cpp \
    gamepairsdisplay.cpp \
    gamepairstextdisplay.cpp \
    gamepairsopengldisplay.cpp

HEADERS += \
    gamepairs.hpp \
    board.hpp \
    player.hpp \
    card.hpp \
    color.hpp \
    gamepairsdisplay.hpp \
    gamepairstextdisplay.hpp \
    gamepairsopengldisplay.hpp
