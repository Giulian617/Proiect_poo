#include "../includes/Interface.h"

void Interface::menu()
{
    int decision;
    std::cout<<"[1] Start the game"<<'\n';
    std::cout<<"[0] Exit"<<'\n';
    std::cin>>decision;
    if(decision==1)
    {
        rlutil::cls();
        std::cout<<"[1] Play on casual game mode(You have multiple chances(with the option to undo your moves) and you can also use the AI or cheat codes for help)"<<'\n';
        std::cout<<"[2] Play on hardcore game mode(You only get one chance(no undo) and no AI or cheat codes, but you will get a higher score if you succeed)"<<'\n';
        std::cout<<"[0] Exit"<<'\n';
        std::cin>>decision;
        if(decision==1)
        {
            Game<false> game;
            play_game<false>(game);
        }
        else if(decision==2)
        {
            Game<true> game;
            play_game<true>(game);
        }
        else
            return;
    }
    else
        return;
}

template<bool Hard>
void Interface::add_worlds(Game<Hard>& game)
{
    World w,w1;
    std::ifstream f0("worlds/world_0.txt");
    f0>>w;
    f0.close();
    game.set_world(w);

    std::ifstream f1("worlds/world_1.txt");
    f1>>w1;
    f1.close();
    game.set_world(w1);
}

template<bool Hard>
void Interface::play_game(Game<Hard>& game)
{
    int decision;
    rlutil::cls();
    add_worlds(game);
    std::cout<<"[1] Play a level from World 1"<<'\n';
    std::cout<<"[2] Play a level from World 2"<<'\n';
    std::cout<<"[0] Exit"<<'\n';
    std::cin>>decision;
    if(decision==1)
    {
        rlutil::cls();
        std::cout<<"[1] Play level 1"<<'\n';
        std::cout<<"[2] Play level 2"<<'\n';
        std::cout<<"[3] Play level 3"<<'\n';
        std::cout<<"[4] Play level 4"<<'\n';
        std::cout<<"[0] Exit"<<'\n';
        std::cin>>decision;
        Level level;
        if(decision==1)
        {
            level=game.get_world(0).get_level(0);
            game.play(level,0,0);
        }
        else if(decision==2)
        {
            level=game.get_world(0).get_level(1);
            game.play(level,0,1);
        }
        else if(decision==3)
        {
            level=game.get_world(0).get_level(2);
            game.play(level,0,2);
        }
        else if(decision==4)
        {
            level=game.get_world(0).get_level(3);
            game.play(level,0,3);
        }
        else
            return;
    }
    else if(decision==2)
    {
        rlutil::cls();
        std::cout<<"[1] Play level 1"<<'\n';
        std::cout<<"[0] Exit"<<'\n';
        std::cin>>decision;
        Level level;
        if(decision==1)
        {
            level=game.get_world(1).get_level(0);
            game.play(level,1,0);
        }
        else
            return;
    }
}