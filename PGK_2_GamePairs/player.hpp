#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>


class Player
{
public:
    static std::string generateNextName();
    Player(std::string aName = generateNextName(), unsigned int aScore = 0);

    std::string name;
    unsigned int score;

    void incrementScore();

private:
    static unsigned int uniquePlayerCounter;
};

#endif // PLAYER_HPP
