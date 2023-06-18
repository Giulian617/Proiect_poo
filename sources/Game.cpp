#include "../includes/Game.h"

void Game::play(Level& level)
{
    srand(time(nullptr));
    Level level_copy(level);
    while(true)
    {
        std::pair<int,int> p=this->players[0]->get_move(level);
        level.set_rail_matrix(p.first,p.second);
        char decision;
        AI* ai_ptr=dynamic_cast<AI*>(this->players[0].get());
        if(ai_ptr!=nullptr)
        {
            int troller_chance=rand()%10;
            if(troller_chance==9)
                this->players[0]=std::make_shared<Troller>();
            ai_ptr->solution(level);
            std::cout<<"Your current score is: "<<this->players[0]->get_score()<<'\n';
            std::cout<<"Do you want to try this level again?[y/n]";
            std::cin>>decision;
            if(decision=='y')
            {
                level=level_copy;
                this->players[1]->update_score(-this->players[1]->get_score()+this->players[0]->get_score(),0);
                ///basically sets the score for the human as the score from the AI
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
                this->players[0]->update_score(100,0);
                rlutil::cls();
                std::cout<<level;
                std::cout<<"Congrats, you cleared this level!!\n";
                std::cout<<"Your current score is: "<<this->players[0]->get_score();
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
                    std::cout<<"Do you want to use a cheat code and then retry the level? Be careful, this will modify your score.[y/n]";
                    std::cin>>decision;
                    std::string cheat_code;
                    while(decision=='y')
                    {
                        std::cout<<"Introduce the code you want to use: ";
                        std::cin>>cheat_code;
                        if(cheat_code=="ILovePuzzles")
                        {
                            level.add_rails(2);
                            this->players[0]->update_score(0,1);///the first parameter is irrelevant in this case
                        }
                        else if(cheat_code=="ILikePuzzles")
                        {
                            level.add_rails(1);
                            this->players[0]->update_score(0,1);///the first parameter is irrelevant in this case
                        }
                        else
                            std::cout<<"This is not a valid cheat_code.\n";
                        std::cout<<"Your current score is: "<<this->players[0]->get_score()<<'\n';
                        std::cout<<"Do you want to use another cheat code? Be careful, this will also modify your score.[y/n]";
                        std::cin>>decision;
                        cheat_code="y";
                    }
                    if(cheat_code=="y")
                    {
                        std::cout<<"Your current score is: "<<this->players[0]->get_score()<<'\n';
                        level=level_copy;
                        swap_players();
                    }
                    std::cout<<"Do you want the AI to help? Be careful, this will modify your score.[y/n]";///option for yes or no
                    std::cin>>decision;
                    if(decision=='y')
                    {
                        swap_players();
                        this->players[0]->update_score(0,0);///the parameters are irrelevant in this case
                    }
                    else
                        break;
                }
                else
                {
                    level=level_copy;
                    swap_players();
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