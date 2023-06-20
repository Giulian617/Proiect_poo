#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include "World.h"
#include "Human.h"
#include "AI.h"
#include "Troller.h"

template<bool Hard> ///game mode:0-casual,1-hardcore(only one life, no AI support)
class Game
{
private:
    std::vector<World>worlds;
    std::array<std::shared_ptr<Player>,2>players;
public:
    Game():players({std::make_shared<Human>(),std::make_shared<AI>()}){};
    Game(const Game& other): worlds(other.worlds), players(other.players) {};
    Game& operator=(const Game&);
    ~Game()=default;
    void play(Level&);
    void swap_players();
    void set_world();
    [[nodiscard]] World get_world(int) const;
};

#include "../sources/Game.tpp"
#endif