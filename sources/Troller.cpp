#include "../includes/Troller.h"

std::pair<int,int> Troller::get_move([[maybe_unused]] const Level& level) const
{
    std::cout<<"HAHA I ain't giving you a valid move."<<'\n';
    return {-1,-1};
}

std::string Troller::get_solution() const
{
    return "HAHA I ain't giving you the solution as well.";
}

void Troller::print_solution() const
{
    std::cout<<"HAHA I ain't giving you the solution as well."<<'\n';
}