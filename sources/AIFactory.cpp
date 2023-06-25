#include "../includes/AIFactory.h"

std::shared_ptr<Player> AIFactory::world0_level0()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("U R R R F\n");
    return ai;
}

std::shared_ptr<Player> AIFactory::world0_level1()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("R R R F\nR I I I\nR R R U\n");
    return ai;
}

std::shared_ptr<Player> AIFactory::world0_level2()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("R R R I R F\nR I R I R I\nU I R R R I\n");
    return ai;
}

std::shared_ptr<Player> AIFactory::world0_level3()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("U R R 0\nI I R 0\n0 0 U I\n0 0 U F\n");
    return ai;
}

std::shared_ptr<Player> AIFactory::world1_level0()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("0 0 0 R F\n0 0 0 R 0\nT U 0 U T\n0 R 0 0 0\nU R 0 0 0\n");
    return ai;
}
