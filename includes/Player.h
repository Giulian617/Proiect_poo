#ifndef PLAYER_H
#define PLAYER_H

#include <rlutil.h>
#include "Level.h"

class Player
{
protected:
    int curr_world=0,curr_level=0;
    double score=5;
    //the score is initialized with 5 just so that changes can be observed in case of a cheat code or if AI is used,
    //normally it would be 0
public:
    [[maybe_unused]] [[nodiscard]] virtual Player* clone() const = 0;
    Player() = default;
    Player(const Player& other);
    Player& operator=(const Player& other);
    virtual ~Player() = default;
    [[nodiscard]] virtual std::pair<int,int> get_move(const Level&) const = 0;
    [[nodiscard]] double get_score() const;
    virtual void update_score(double,int) = 0;
};

#endif