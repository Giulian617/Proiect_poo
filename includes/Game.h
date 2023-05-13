#ifndef GAME_H
#define GAME_H

#include <memory>
#include "World.h"
#include "Player.h"

class Game
{
private:
    std::vector<World>worlds;
    std::shared_ptr<Player>player;
public:
};

#endif