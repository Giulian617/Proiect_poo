#include "includes/Game.h"
using namespace std;
int main()
{
    try
    {
        Game game;
        game.set_world();
        game.menu();
        cout<<'\n';
    }
    catch(value_error &err)
    {
        cout<<err.what();
    }
    catch(not_a_valid_color_error &err)
    {
        cout<<err.what();
    }
    catch(...)
    {
        cout<<"This is unexpected, oops =(.";
    }
    return 0;
}