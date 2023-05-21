#ifndef AI_H
#define AI_H

#include "Player.h"

class AI:public Player
{
public:
    AI():Player() {}
    [[nodiscard]] Player* clone() const override {return new AI(*this);}
    [[nodiscard]] std::pair<int,int> get_move([[maybe_unused]] const Level&) const override;
    void solution(const Level&);
};

#endif