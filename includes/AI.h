#ifndef AI_H
#define AI_H

#include "Player.h"

class AI:public Player
{
private:
    std::string solution;
public:
    explicit AI(std::string solution_="1"):Player(),solution(std::move(solution_)){}
    [[nodiscard]] Player* clone() const override {return new AI(*this);}
    [[nodiscard]] std::pair<int,int> get_move([[maybe_unused]] const Level&) const override;
    void print_solution() const override;
    void update_score(double,int) override;
};

#endif