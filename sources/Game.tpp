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
    char decision;
    while(true)
    {
        AI* ai_ptr=dynamic_cast<AI*>(this->players[0].get());
        if(ai_ptr!=nullptr)
        {
            [[maybe_unused]] std::pair<int,int> p=this->players[0]->get_move(level);
            int troller_chance=rand()%10;
            if(troller_chance==9)
            {
                this->players[0]=std::make_shared<Troller>();
                this->players[0]->print_solution();
            }
            else
            {
                std::shared_ptr<Player> new_player=std::make_shared<AI>();
                if(world_no==0)
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
            if(Hard)
            {
                std::pair<int,int> p=this->players[0]->get_move(level);
                level.set_rail_matrix(p.first, p.second);
            }
            else
            {
                rlutil::cls();
                decision='c';
                if(!moves.empty())
                {
                    std::cout<<level;
                    std::cout<<"If you want to undo, introduce u, else introduce c\n";
                    std::cin>>decision;
                }
                if(decision=='u')
                {
                    level.unset_rail_matrix(moves.top().first,moves.top().second);
                    moves.pop();
                    continue;
                }
                else
                {
                    std::pair<int,int> p=this->players[0]->get_move(level);
                    level.set_rail_matrix(p.first, p.second);
                    moves.emplace(p.first,p.second);
                    if(level.get_available_rails()==0)
                    {
                        rlutil::cls();
                        std::cout<<level;
                        std::cout<<"If you want to undo, introduce u, else introduce c\n";
                        std::cin>>decision;
                        if(decision=='u')
                        {
                            level.unset_rail_matrix(moves.top().first,moves.top().second);
                            moves.pop();
                            continue;
                        }
                    }
                }
            }
            int finished=this->game_over(level,world_no,level_no);
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
                std::cout<<"Do you want to play the next level?[y/n]"<<'\n';
                std::cin>>decision;
                if(decision=='y')
                {
                    while(!moves.empty())
                        moves.pop();
                    if(world_no==0)
                    {
                        if(level_no<=2)
                        {

                            Level new_level=this->worlds[0].get_level(level_no+1);
                            play(new_level,world_no,level_no+1);
                            break;
                        }
                        else
                        {
                            Level new_level=this->worlds[1].get_level(0);
                            play(new_level,1,0);
                            break;
                        }
                    }
                    else
                    {
                        std::cout<<"This was the last level of the game! Congrats, you've completed it!!!\n";
                        std::cout<<"Thanks again for playing!!\n";
                        break;
                    }
                }
                else
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
int Game<Hard>::game_over(const Level& level,int world_no,int level_no)
{
    std::shared_ptr<Player> new_player=std::make_shared<AI>();
    if(world_no==0)
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
    if(level.get_solution()==new_player->get_solution())
        return 1;
    else if(level.get_available_rails()==0)
        return -1;
    return 0;
}

template<bool Hard>
void Game<Hard>::set_world(World& w)
{
    this->worlds.push_back(w);
}

template<bool Hard>
World Game<Hard>::get_world(int n) const
{
    return this->worlds[n];
}