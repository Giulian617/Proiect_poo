#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <queue>
#include "Level.h"

class World
{
private:
    std::vector<Level> levels;
public:
    World() = default;
    void correct_order_per_level();
    friend std::istream& operator >>(std::istream&,World&);
    friend std::ostream& operator <<(std::ostream&,const World&);
};

#endif