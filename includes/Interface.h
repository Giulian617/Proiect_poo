#ifndef INTERFACE_H
#define INTERFACE_H

#include <fstream>
#include "Game.h"

class Interface
{
private:
    Interface()=default;
public:
    Interface(const Interface&)=delete;
    Interface& operator=(const Interface&)=delete;
    [[maybe_unused]] static Interface& get_interface()
    {
        static Interface game_interface;
        return game_interface;
    }
    static void menu();
    template<bool Hard>
    static void add_worlds(Game<Hard>&);
    template<bool Hard>
    static void play_game(Game<Hard>&);
};

#endif