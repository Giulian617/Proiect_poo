#include "../includes/Game.h"

template<bool Hard>
Game<Hard>& Game<Hard>::operator=(const Game<Hard>&other)
{
    if(this!=&other)
    {
        this->worlds=other.worlds;
        this->players=other.players;
    }
    return *this;
}

template<bool Hard>
void Game<Hard>::play(Level& level,int world_no,int level_no)
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
            {
                this->players[0]=std::make_shared<Troller>();
                this->players[0]->print_solution();
            }
            else
            {
                std::shared_ptr<Player> new_player=std::make_shared<AI>();
                if(world_no==0)///this part is just to express the reason why the factory is created, right now only world 0 level 0 is available
                {
                    if(level_no==0)
                        new_player=AIFactory::world0_level0();
                    else if(level_no==1)
                        new_player=AIFactory::world0_level1();
                    else if(level_no==2)
                        new_player=AIFactory::world0_level2();
                    else
                        new_player=AIFactory::world0_level3();
                }
                else
                    new_player=AIFactory::world1_level0();
                new_player->print_solution();
            }
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
                if(Hard)
                    this->players[0]->update_score(200,0);
                else
                    this->players[0]->update_score(100,0);
                rlutil::cls();
                std::cout<<level;
                std::cout<<"Congrats, you cleared this level!!\n";
                std::cout<<"Your current score is: "<<this->players[0]->get_score()<<'\n';
                std::cout<<"Thanks for playing!!"<<'\n';
                /* when adding new levels this option will become available,
                 * but for now it's just a comment to show the purpose of the factory
                std::cout<<"Do you want to play the next level?[y/n]"<<'\n';
                std::cin>>decision;
                if(decision=='y')
                {
                    if(world_no==0)
                    {
                        if(level_no<=2)
                            level_no++;
                        else
                        {
                            world_no=1;
                            level_no=0;
                        }
                    }
                    else
                    {
                        std::cout<<"This was the last level of the game! Congrats, you've completed it!!!\n";
                        std::cout<<"Thanks for playing!!\n"
                    }
                }
                */
                break;
            }
            else if(finished==-1)///if Hard is true then the player should not have the option to play again
            {
                std::cout<<"You ran out of rails :(\n";
                if(Hard)
                {
                    std::cout<<"Because you chose hardcore game mode, this is the end of the game for you, thanks for playing!!"<<'\n';
                    break;
                }
                std::cout<<"Do you want to try this level again?[y/n]\n"; ///option for yes or no
                std::cin>>decision;
                level=level_copy;
                if(decision=='n')
                {
                    std::cout<<"Do you want to use a cheat code and then retry the level? Be careful, this will modify your score.[y/n]\n";
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
                        std::cout<<"Do you want to use another cheat code? Be careful, this will also modify your score.[y/n]\n";
                        std::cin>>decision;
                        cheat_code="y";
                    }
                    if(cheat_code=="y")
                    {
                        std::cout<<"Your current score is: "<<this->players[0]->get_score()<<'\n';
                        level=level_copy;
                        swap_players();
                    }
                    std::cout<<"Do you want the AI to help? Be careful, this will modify your score.[y/n]\n";///option for yes or no
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

template<bool Hard>
void Game<Hard>::swap_players()
{
    std::shared_ptr<Player> aux{this->players[0]->clone()};
    players[0]=std::move(players[1]);
    players[1]=std::move(aux);
}

template<bool Hard>
void Game<Hard>::set_world()
{
    World w;
    std::cin>>w;
    this->worlds.push_back(w);
}

template<bool Hard>
World Game<Hard>::get_world(int n) const
{
    return this->worlds[n];
}