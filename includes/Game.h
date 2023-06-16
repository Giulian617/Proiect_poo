#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include "World.h"
#include "Human.h"
#include "AI.h"
#include "Troller.h"

class Game
{
private:
    std::vector<World>worlds;
    std::array<std::shared_ptr<Player>,2>players;
    void play(Level&);
public:
    Game():players({std::make_shared<Human>(),std::make_shared<AI>()}) {};
    void swap_players();
    void set_world();
    void menu();
};

#endif