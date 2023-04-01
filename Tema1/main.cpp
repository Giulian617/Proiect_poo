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
    void increase_number();
    friend istream& operator >>(istream&,Train&);
    friend ostream& operator <<(ostream&,const Train&);
    ~Train()
    {
        delete[] color; ///not necessary to check if it is a nullptr
    }
};

void Train::increase_number()
{
    number++;
}

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
    bool rail_matrix[15][15]={},train_matrix[15][15]={};
    int road_matrix[15][15]={},distance[15];
    int n,available_rails,finish_row,finish_column;
    vector<Train>trains;
public:
    explicit Level(int dim=0,int rails=0,int row=0,int column=0):n(dim),available_rails(rails),finish_row(row),finish_column(column){}
    [[maybe_unused]] void set_rail_matrix(int,int,bool); ///going to use them in a future version
    [[maybe_unused]] void set_train_matrix(int,int,bool); ///going to use them in a future version
/// bool path_to_finish(int,int);
/// bool if_collision(); /// also creates road_matrix;
/// void generate_distances()
/// bool correct_order();
    friend istream& operator >>(istream&,Level&);
    friend ostream& operator <<(ostream&,const Level&);
};

[[maybe_unused]] void Level::set_rail_matrix(int row,int column,bool used)
{
    rail_matrix[row][column]=used;
}

[[maybe_unused]] void Level::set_train_matrix(int row,int column,bool used)
{
    train_matrix[row][column]=used;
}

//bool Level::path_to_finish(int row, int column)
//{
//
//}
//int Level::if_collision()
//{
//
//}
//void Level::generate_distances()
//{
//
//}
//bool Level::correct_order()
//{
//
//}

istream& operator >>(istream& in,Level& l)
{
    in>>l.n>>l.available_rails>>l.finish_row>>l.finish_column;
    for(int i=0;i<l.n;i++)
        for(int j=0;j<l.n;j++)
            in>>l.rail_matrix[i][j];
    for(int i=0;i<l.n;i++)
        for(int j=0;j<l.n;j++)
            in>>l.train_matrix[i][j];
    Train t;
    int m;
    in>>m;
    for(int i=0; i<m; i++)
    {
        in>>t;
        l.trains.push_back(t);
    }
    return in;
}

ostream& operator <<(ostream& out,const Level& l)
{
    for(int i=0;i<l.n;i++)
    {
        for(int j=0;j<l.n;j++)
            out<<l.rail_matrix[i][j]<<' ';
        out<<'\n';
    }
    out<<'\n';
    for(int i=0;i<l.n;i++)
    {
        for(int j=0;j<l.n;j++)
            out<<l.train_matrix[i][j]<<' ';
        out<<'\n';
    }
    out<<'\n';
    for(const Train& train : l.trains)
        out<<train;
    return out;
}

class World
{
private:
    vector<Level> levels;
public:
    World() = default;
    friend istream& operator >>(istream&,World&);
    friend ostream& operator <<(ostream&,const World&);
};

istream& operator >>(istream& in,World& w)
{
    int m;
    Level l;
    in>>m;
    for(int i=0;i<m;i++)
    {
        in>>l;
        w.levels.push_back(l);
    }
    return in;
}

ostream& operator <<(ostream& out,const World& w)
{
    for(const Level& level:w.levels)
        out<<level;
    return out;
}

int main()
{
    Train t1(1,"green"), t2(2,"red"),t3(t2);
    t3.increase_number();
    World w1{};
    cin>>w1;
    cout<<w1;
    return 0;
}
