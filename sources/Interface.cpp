#include "../includes/Interface.h"

void Interface::menu()
{
    int decision;
    std::cout<<"[1] Play a preselected level"<<'\n';
    std::cout<<"[0] Exit"<<'\n';
    std::cin>>decision;
    if(decision==1)
    {
        rlutil::cls();
        std::cout<<"[1] Play on casual game mode(You have multiple chances and you can also use the AI or cheat codes for help)"<<'\n';
        std::cout<<"[2] Play on hardcore game mode(You only get one chance and no AI or cheat codes, but you will get a higher score if you succeed)"<<'\n';
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
void Interface::play_game(Game<Hard>& game)
{
    rlutil::cls();
    std::cout<<"Sorry, this is still under construction, would you be kind enough to enter the level from the file tastatura.txt please?\n";
    game.set_world();
    Level level=game.get_world(0).get_level(0);
    game.play(level,0,0);
}