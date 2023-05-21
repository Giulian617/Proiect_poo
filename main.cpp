#include "includes/Game.h"
using namespace std;
int main()
{
    Game game;
    game.set_world();
    game.menu();
    cout<<'\n';
    cout<<"Number of train objects: "<<Train::get_no_of_trains();
    return 0;
}