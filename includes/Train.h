#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <string>
#include <set>
#include "Exceptions.h"

class Train
{
private:
    static std::set<std::string> good_colors;
    int number;
    std::string color;
public:
    explicit Train(int _number=1,std::string _color="red"): number(_number), color(std::move(_color)) ///initialization constructor
    {
        if(number<1)
            throw value_error("A train must have a positive natural number.");
        if(!good_colors.contains(color))
            throw not_a_valid_color_error("This isn't an appropriate color.");
    }
    Train(const Train&)=default;
    Train& operator =(const Train& other);
    friend std::istream& operator >>(std::istream&,Train&);
    friend std::ostream& operator <<(std::ostream&,const Train&);
    ~Train()=default;
};

#endif