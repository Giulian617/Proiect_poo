#ifndef AIFACTORY_H
#define AIFACTORY_H

#include "AI.h"
#include <memory>

class AIFactory
{
public:
    static std::shared_ptr<Player>world0_level0();
    static std::shared_ptr<Player>world0_level1();
    static std::shared_ptr<Player>world0_level2();
    static std::shared_ptr<Player>world0_level3();
    static std::shared_ptr<Player>world1_level0();
};

#endif