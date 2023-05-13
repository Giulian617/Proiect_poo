#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <string>

class Train
{
private:
    static int no_of_trains;
    int number;
    std::string color;
public:
    explicit Train(int _number=1,std::string _color=""): number(_number), color(std::move(_color)) ///initialization constructor
    {
        no_of_trains++;
    }
    Train(const Train&) = default;
    Train& operator =(const Train& other);
    [[maybe_unused]] static int get_no_of_trains();
    friend std::istream& operator >>(std::istream&,Train&);
    friend std::ostream& operator <<(std::ostream&,const Train&);
    ~Train()
    {
        no_of_trains--;
    }
};

#endif