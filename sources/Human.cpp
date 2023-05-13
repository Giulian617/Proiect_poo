#include "../Includes/Human.h"

std::pair<int,int> Human::get_move(const Level& level) const
{
    int row=-1,column=-1;
    while(row==-1)
    {
        rlutil::cls();
        std::cout<<level<<'\n';
        std::cout<<"Please enter the row and column where you want to place the rail."<<'\n';
        std::cout<<"Please choose a row and a column in the intervals shown above and beside the matrix."<<'\n';
        std::cin>>row>>column;
        if(!level.free(row,column))
            row=-1;
    }
    return {row,column};
}