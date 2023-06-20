#include "includes/Interface.h"
using namespace std;
int main()
{
    try
    {
        Interface::menu();
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