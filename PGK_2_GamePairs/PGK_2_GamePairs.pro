CONFIG += c++11
CONFIG += -Wall
CONFIG += -Weffc++
CONFIG += -O2

# WARN: Line below is probably not cross-platform compatible:
LIBS += -lglfw3 -pthread -lGLEW -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11

SOURCES += \
    main.cpp \
    gamepairs.cpp \
    board.cpp \
    player.cpp \
    card.cpp \
    color.cpp \
    gamepairsdisplay.cpp \
    gamepairstextdisplay.cpp \
    gamepairsopengldisplay.cpp \
    shaders.cpp

HEADERS += \
    gamepairs.hpp \
    board.hpp \
    player.hpp \
    card.hpp \
    color.hpp \
    gamepairsdisplay.hpp \
    gamepairstextdisplay.hpp \
    gamepairsopengldisplay.hpp \
    shaders.hpp \
    shaderssourcecodes.hpp
