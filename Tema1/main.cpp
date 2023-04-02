#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

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
    bool rail_matrix[15][15]={};
    int n,m,available_rails,train_no,finish_row,finish_column,road_matrix[15][15]={};
    vector<int>distances;
    vector<pair<Train,pair<int,int>>>trains;
public:
    explicit Level(int dim_row=0,int dim_col=0,int rails=0,int number=0,int row=0,int column=0):
            n(dim_row),m(dim_col),available_rails(rails),train_no(number),finish_row(row),finish_column(column) {}
    /// void set_rail_matrix(int,int,bool); ///going to use them in a future version
    /// void set_train_matrix(int,int,bool); ///going to use them in a future version
    void lee(queue<pair<int,int>>&);
    void reset_road_matrix();
    void generate_distances();
    bool correct_order();
    friend istream& operator >>(istream&,Level&);
    friend ostream& operator <<(ostream&,const Level&);
};

// void Level::set_rail_matrix(int row,int column,bool used)
//{
//    rail_matrix[row][column]=used;
//}
//
// void Level::set_train_matrix(int row,int column,bool used)
//{
//    train_matrix[row][column]=used;
//}

void Level::lee(queue<pair<int,int>>& q)
{
    const int dx[]= {0,-1,0,1},dy[]= {-1,0,1,0};
    road_matrix[q.front().first][q.front().second]=1;
    while(!q.empty())
    {
        int x=q.front().first,y=q.front().second;
        q.pop();
        for(int k=0; k<4; k++)
        {
            int nx=x+dx[k],ny=y+dy[k];
            if(0<=nx && nx<n && 0<=ny && ny<=m && rail_matrix[nx][ny]==1 && road_matrix[nx][ny]==0)
            {
                road_matrix[nx][ny]=road_matrix[x][y]+1;
                q.emplace(nx,ny);
            }
        }
    }
}

void Level::reset_road_matrix()
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            road_matrix[i][j]=0;
}

void Level::generate_distances()
{
    queue<pair<int,int>>q;
    for(const pair<Train,pair<int,int>>& train:trains)
        {
            reset_road_matrix();
            q.emplace(train.second.first,train.second.second);
            lee(q);
            distances.push_back(road_matrix[finish_row][finish_column]);
        }
}

bool Level::correct_order()
{
    generate_distances();
    for(int i=1; i<(int)distances.size(); i++)
        if(distances[i]<=distances[i-1])///the trains arrive at the station in incorrect order
            return false;
    return true;
}

istream& operator >>(istream& in,Level& l)
{
    in>>l.n>>l.m;
    for(int i=0; i<l.n; i++)
        for(int j=0; j<l.m; j++)
            in>>l.rail_matrix[i][j];
    in>>l.available_rails>>l.train_no>>l.finish_row>>l.finish_column;
    int x,y;
    for(int i=0; i<l.train_no; i++)
    {
        Train t(i);
        in>>t>>x>>y;
        l.trains.push_back({t,{x,y}});
    }
    return in;
}

ostream& operator <<(ostream& out,const Level& l)
{
    for(int i=0; i<l.n; i++)
    {
        for(int j=0; j<l.m; j++)
            out<<l.rail_matrix[i][j]<<' ';
        out<<'\n';
    }
    out<<'\n';
    for(const pair<Train,pair<int,int>>& train:l.trains)
        out<<train.second.first<<' '<<train.second.second<<' '<<train.first;
    out<<'\n';
    return out;
}

class World
{
private:
    vector<Level> levels;
public:
    World() = default;
    void correct_order_per_level();
    friend istream& operator >>(istream&,World&);
    friend ostream& operator <<(ostream&,const World&);
};

void World::correct_order_per_level()
{
    for(Level& level:levels)
        if(level.correct_order())
            cout<<"Level is valid, there is possible for all trains to reach the end in order."<<'\n';
        else
            cout<<"Oops, this level is not doable with the given constrains."<<'\n';
}

istream& operator >>(istream& in,World& w)
{
    int m;
    in>>m;
    for(int i=0; i<m; i++)
    {
        Level l;
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
    World w1{};
    cin>>w1;
    w1.correct_order_per_level();
    cout<<w1;
    return 0;
}