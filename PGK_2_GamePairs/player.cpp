#include "player.hpp"
#include <sstream>

unsigned int Player::uniquePlayerCounter = 1;

Player::Player(std::string aName, unsigned int aScore)
    : name(aName), score(aScore) {}

void Player::incrementScore()
{
    ++score;
}

std::string Player::generateNextName()
{
    std::stringstream newName;
    newName << "Player" << Player::uniquePlayerCounter;

    return newName.str();
}
