#include "../includes/Game.h"

void Game::play(Level& level)
{
    Level level_copy(level);
    while(true)
    {
        std::pair<int,int> p=this->players[0]->get_move(level);
        level.set_rail_matrix(p.first,p.second);
        char decision;
        AI* ai_ptr=dynamic_cast<AI*>(this->players[0].get());
        if(ai_ptr!=nullptr)
        {
            AI::solution(level);
            std::cout<<"Do you want to try this level again?";
            std::cin>>decision;
            if(decision=='y')
            {
                level=level_copy;
                swap_players();
            }
            else
                break;
        }
        else
        {
            int finished=level.game_over();
            if(finished==1)
            {
                std::cout<<"Congrats, you cleared this level!!";
                break;
            }
            else if(finished==-1)
            {
                level=level_copy;
                std::cout<<"You ran out of rails :(\n";
                std::cout<<"Do you want to try this level again?[y/n]"; ///option for yes or no
                std::cin>>decision;
                if(decision=='n')
                {
                    std::cout<<"Do you want the AI to help?[y/n]";///option for yes or no
                    std::cin>>decision;
                    if(decision=='y')
                        swap_players();
                    else
                        break;
                }
            }
        }
    }
}

void Game::swap_players()
{
    std::shared_ptr<Player> aux{this->players[0]->clone()};
    players[0]=std::move(players[1]);
    players[1]=std::move(aux);
}

void Game::set_world()
{
    World w;
    std::cin>>w;
    this->worlds.push_back(w);
}

void Game::menu()
{
    int decision;
    rlutil::cls();
    std::cout<<"[1] Play a preselected level"<<'\n';
    std::cout<<"[0] Exit"<<'\n';
    std::cin>>decision;
    if(decision==1)
    {
        Level level=this->worlds[0].get_level(0);
        play(level);
    }
    else
        return;
}