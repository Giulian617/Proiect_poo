#include <iostream>
#include "includes/World.h"
using namespace std;
int main()
{
    World w1{};
    cin>>w1;
    w1.correct_order_per_level();
    cout<<w1;
    return 0;
}