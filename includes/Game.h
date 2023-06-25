#ifndef GAME_H
#define GAME_H

#include <stack>
#include <memory>
#include <random>
#include "World.h"
#include "Human.h"
#include "AI.h"
#include "Troller.h"
#include "AIFactory.h"

template<bool Hard> ///game mode:0-casual,1-hardcore(only one life, no AI support)
class Game
{
private:
    std::vector<World>worlds;
    std::array<std::shared_ptr<Player>,2>players;
    std::stack<std::pair<int,int>>moves;
public:
    Game():players({std::make_shared<Human>(),std::make_shared<AI>()}){};
    Game(const Game& other): worlds(other.worlds), players(other.players) {};
    Game& operator=(const Game&);
    ~Game()=default;
    void play(Level&,int,int);
    void swap_players();
    int game_over(const Level&,int,int);
    void set_world(World&);
    [[nodiscard]] World get_world(int) const;
};

#include "../sources/Game.tpp"
#endif