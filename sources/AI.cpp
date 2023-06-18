#include "../includes/AI.h"

std::pair<int,int> AI::get_move([[maybe_unused]] const Level& level) const
{
    std::cout<<"HAHA I'm way too smart for you little human, I don't stress myself with simple moves, I only provide the full solution."<<'\n';
    return {-1,-1};
}

void AI::solution(const Level& level) const
{
    level.print_solution();
}

void AI::update_score([[maybe_unused]] double change,[[maybe_unused]] int type)
{
    this->score=this->score*0.1;//the change is irrelevant here and so is the type
}