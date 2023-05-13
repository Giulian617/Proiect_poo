#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human:public Player
{
public:
    Human():Player() {}
    [[nodiscard]] Player* clone() const override {return new Human(*this);}
    [[nodiscard]] std::pair<int,int> get_move(const Level&) const override;
};

#endif