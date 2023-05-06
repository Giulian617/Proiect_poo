#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <string>
using namespace std;

class Train
{
private:
    int number;
    string color;
public:
    explicit Train(int _number=1,string _color=""): number(_number), color(std::move(_color)) {}///initialization constructor
    Train(const Train&) = default;
    Train& operator =(const Train& other);
    friend istream& operator >>(istream&,Train&);
    friend ostream& operator <<(ostream&,const Train&);
    ~Train()
    {
        cout<<"~Train"<<'\n';
    }
};

#endif