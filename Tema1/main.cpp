#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
class Train
{
private:
    int number;
    char* color;
public:
    explicit Train(int _number=1,const char* _color=nullptr): number(_number) ///initialization constructor
    {
        if(_color==nullptr)
            color=nullptr;
        else
        {
            color=new char[strlen(_color)+1];
            strcpy(color,_color);
        }
    }
    Train(const Train &other) ///copy constructor
    {
        number=other.number;
        if(other.color==nullptr)
            color=nullptr;
        else
        {
            color=new char[strlen(other.color)+1];
            strcpy(color,other.color);
        }
    }
    Train& operator =(const Train& other)
    {
        if(this==&other)
            return *this;
        number=other.number;
        delete[] color;
        if(other.color==nullptr)
            color=nullptr;
        else
        {
            color=new char[strlen(other.color)+1];
            strcpy(color,other.color);
        }
        return *this;
    }
    friend istream& operator >>(istream&,Train&);
    friend ostream& operator <<(ostream&,const Train&);
    ~Train()
    {
        delete[] color; ///not necessary to check if it is a nullptr
    }
};

istream& operator >>(istream& in,Train& t)
{
    in>>t.number;
    char aux[256];
    in>>aux;
    delete[] t.color; ///not necessary to check if it is a nullptr
    t.color=new char[strlen(aux)+1];
    strcpy(t.color,aux);
    return in;
}

ostream& operator <<(ostream& out,const Train& t)
{
    return out<<t.number<<' '<<t.color<<'\n';
}

class Level
{
private:
    int matrix[15][15]={};
    vector<Train>trains;
public:
    explicit Level() {};
    friend istream& operator >>(istream&,Level&);
    friend ostream& operator <<(ostream&,const Level&);
};

istream& operator >>(istream& in,Level& l)
{
    for(int i=0;i<=14;i++)
        for(int j=0;j<=14;j++)
            in>>l.matrix[i][j];

}
//class World
//{
//private:
//    vector<Level> levels;
//
//};
int main()
{
    Train t1(1,"green"), t2(2,"red"),t3(t2);
    t3=t1;
    cout<<t3;
    Level l1(), l2();
//    World w1();
    return 0;
}
