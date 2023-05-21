#include "../includes/Human.h"

std::pair<int,int> Human::get_move(const Level& level) const
{
    int row=-1,column=-1;
    while(row==-1)
    {
        rlutil::cls();
        std::cout<<level;
        std::cout<<"Please enter the row and column where you want to place the rail."<<'\n';
        std::cout<<"Please choose a row and a column in the intervals [0,x],[0,y] where x and y are the two numbers shown above the matrix"<<'\n';
        std::cin>>row>>column;
        if(!level.free(row,column))
            row=-1;
    }
    return {row,column};
}