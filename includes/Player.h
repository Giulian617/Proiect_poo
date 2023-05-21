#ifndef PLAYER_H
#define PLAYER_H

#include <rlutil.h>
#include "Level.h"

class Player
{
protected:
    int curr_world=0,curr_level=0;
public:
    [[maybe_unused]] [[nodiscard]] virtual Player* clone() const = 0;
    Player() = default;
    Player(const Player& other);
    Player& operator=(const Player& other);
    virtual ~Player() = default;
    [[nodiscard]] virtual std::pair<int,int> get_move(const Level&) const = 0;
};

#endif