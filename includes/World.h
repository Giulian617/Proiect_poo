#ifndef WORLD_H
#define WORLD_H

#include "Level.h"

class World
{
private:
    std::vector<Level> levels;
public:
    ///[[maybe_unused]] void correct_order_per_level(); pt ca pica pe cppcheck si nu o mai folosesc momentan
    Level get_level(int);
    friend std::istream& operator >>(std::istream&,World&);
    friend std::ostream& operator <<(std::ostream&,const World&);
};

#endif