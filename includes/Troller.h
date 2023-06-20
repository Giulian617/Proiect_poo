#ifndef TROLLER_H
#define TROLLER_H

#include "AI.h"

class Troller:public AI
{
public:
    Troller():AI() {}
    [[nodiscard]] Player* clone() const override {return new Troller(*this);}
    [[nodiscard]] std::pair<int,int> get_move([[maybe_unused]] const Level&) const override;
    void print_solution() const override;
};

#endif