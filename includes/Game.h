#ifndef GAME_H
#define GAME_H

#include <memory>
#include "World.h"
#include "Human.h"
#include "AI.h"

class Game
{
private:
    std::vector<World>worlds;
    std::shared_ptr<Player>player;
    void play(Level&);
public:
    Game():player(std::make_shared<Human>()) {};
    void set_world();
    void menu();
};

#endif