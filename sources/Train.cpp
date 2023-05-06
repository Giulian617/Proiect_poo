#include "../includes/Train.h"
Train& Train::operator=(const Train& other)
{
    if(this==&other)
        return *this;
    number=other.number;
    color=other.color;
    return *this;
}
istream& operator >>(istream& in,Train& t)
{
    in>>t.color;
    return in;
}
ostream& operator <<(ostream& out,const Train& t)
{
    return out<<t.number<<' '<<t.color<<'\n';
}