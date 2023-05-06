#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <queue>
#include "Level.h"
using namespace std;

class World
{
private:
    vector<Level> levels;
public:
    World() = default;
    void correct_order_per_level();
    friend istream& operator >>(istream&,World&);
    friend ostream& operator <<(ostream&,const World&);
};

#endif