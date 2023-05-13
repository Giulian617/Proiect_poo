#include "../includes/Train.h"

int Train::no_of_trains=0;

Train& Train::operator=(const Train& other)
{
    if(this==&other)
        return *this;
    number=other.number;
    color=other.color;
    return *this;
}

[[maybe_unused]] int Train::get_no_of_trains()
{
    return Train::no_of_trains;
}

std::istream& operator >>(std::istream& in,Train& t)
{
    in>>t.color;
    return in;
}

std::ostream& operator <<(std::ostream& out,const Train& t)
{
    return out<<t.number<<' '<<t.color<<'\n';
}