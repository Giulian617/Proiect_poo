#include "../includes/World.h"

void World::correct_order_per_level()
{
    for(Level& level:levels)
        if(level.correct_order())
            cout<<"Level is valid, it is possible for all trains to reach the end in order."<<'\n';
        else
            cout<<"Oops, this level is not doable with the given constraints."<<'\n';
}

istream& operator >>(istream& in,World& w)
{
    int m;
    in>>m;
    for(int i=0; i<m; i++)
    {
        Level l;
        in>>l;
        w.levels.push_back(l);
    }
    return in;
}

ostream& operator <<(ostream& out,const World& w)
{
    for(const Level& level:w.levels)
        out<<level;
    return out;
}
