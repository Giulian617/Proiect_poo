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