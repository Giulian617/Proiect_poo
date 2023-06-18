#include "../includes/Player.h"

Player::Player(const Player &other): curr_world(other.curr_world), curr_level(other.curr_level) {}

Player& Player::operator=(const Player& other)
{
    if(this!=&other)
    {
        this->curr_world=other.curr_world;
        this->curr_level=other.curr_level;
    }
    return *this;
}

double Player::get_score() const
{
    return this->score;
}