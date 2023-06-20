#include "../includes/AIFactory.h"

std::shared_ptr<Player> AIFactory::world0_level0()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("0 0 0 0\n0 0 0 1\n1 1 1 1\n1 0 1 1\n");
    return ai;
}

std::shared_ptr<Player> AIFactory::world0_level1()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("Level not available yet\n");
    return ai;
}

std::shared_ptr<Player> AIFactory::world0_level2()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("Level not available yet\n");
    return ai;
}

std::shared_ptr<Player> AIFactory::world0_level3()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("Level not available yet\n");
    return ai;
}

std::shared_ptr<Player> AIFactory::world1_level0()
{
    std::shared_ptr<Player> ai=std::make_shared<AI>("Level not available yet\n");
    return ai;
}
