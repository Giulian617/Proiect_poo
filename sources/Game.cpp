#include "../includes/Game.h"

void Game::play(Level& level)
{
    Level level_copy(level);
    while(true)
    {
        std::pair<int,int> p=this->player->get_move(level);
        level.set_rail_matrix(p.first,p.second);
        char decision;
        AI* ai_ptr=dynamic_cast<AI*>(this->player.get());
        if(ai_ptr!=nullptr)
        {
            ai_ptr->solution(level);
            std::cout<<"Do you want to try this level again?";
            std::cin>>decision;
            if(decision=='y')
            {
                level=level_copy;
                this->player=std::make_shared<Human>();
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
                std::cout<<"You ran out of rails :(";
                std::cout<<"Do you want to try this level again?"; ///option for yes or no
                std::cin>>decision;
                if(decision=='n')
                {
                    std::cout<<"Do you want the AI to help?";///option for yes or no
                    if(decision=='y')
                        this->player=std::make_shared<AI>();
                    else
                        break;
                }
            }
        }
    }
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