#include "../includes/AI.h"

std::pair<int,int> AI::get_move([[maybe_unused]] const Level& level) const
{
    std::cout<<"HAHA I'm way too smart for you little human, I don't stress myself with simple moves, I only provide the full solution."<<'\n';
    return {0,0};
}

std::string AI::get_solution() const
{
    return this->solution;
}

void AI::print_solution() const
{
    for(char rail:solution)
        if(rail=='0')
        {
            rlutil::setColor(15);
            std::cout<<rail;
        }
        else if(rail=='R')
        {
            rlutil::setColor(8);
            std::cout<<rail;
        }
        else if(rail=='U')
        {
            rlutil::setColor(5);
            std::cout<<rail;
        }
        else if(rail=='I')
        {
            rlutil::setColor(4);
            std::cout<<rail;
        }
        else if(rail=='F')
        {
            rlutil::setColor(14);
            std::cout<<rail;
        }
        else if(rail=='T')
        {
            rlutil::setColor(1);
            std::cout<<rail;
        }
        else
            std::cout<<rail;
    std::cout<<'\n';
    rlutil::setColor(15);
}


void AI::update_score([[maybe_unused]] double change,[[maybe_unused]] int type)
{
    this->score=this->score*0.1;//the change is irrelevant here and so is the type
}