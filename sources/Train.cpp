#include "../includes/Train.h"

std::set<std::string> Train::good_colors={"red","green","purple","blue","white","orange","yellow"};

Train& Train::operator=(const Train& other)
{
    if(this==&other)
        return *this;
    number=other.number;
    color=other.color;
    return *this;
}

std::istream& operator >>(std::istream& in,Train& t)
{
    in>>t.color;
    if(!Train::good_colors.contains(t.color))
        throw not_a_valid_color_error("This isn't an appropriate color.");
    return in;
}

std::ostream& operator <<(std::ostream& out,const Train& t)
{
    return out<<t.number<<' '<<t.color<<'\n';
}