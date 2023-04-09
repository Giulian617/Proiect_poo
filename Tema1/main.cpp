#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <queue>
using namespace std;

class Train
{
private:
    int number;
    string color;
public:
    explicit Train(int _number=1,string _color=""): number(_number),color(std::move(_color)) {}///initialization constructor
    Train(const Train &other): number(other.number), color(other.color) {}///copy constructor
    Train& operator =(const Train& other)
    {
        if(this==&other)
            return *this;
        number=other.number;
        color=other.color;
        return *this;
    }
    friend istream& operator >>(istream&,Train&);
    friend ostream& operator <<(ostream&,const Train&);
    ~Train()
    {
        cout<<"~Train"<<'\n';
    }
};

istream& operator >>(istream& in,Train& t)
{
    in>>t.color;
    return in;
}

ostream& operator <<(ostream& out,const Train& t)
{
    return out<<t.number<<' '<<t.color<<'\n';
}

class Level
{
private:
    array<array<bool,15>,15>rail_matrix={};
    int n,m,available_rails,train_no,finish_row,finish_column;
    vector<pair<Train,pair<int,int>>>trains;
public:
    explicit Level(int dim_row=0,int dim_col=0,int rails=0,int number=0,int row=0,int column=0):
            n(dim_row),m(dim_col),available_rails(rails),train_no(number),finish_row(row),finish_column(column) {}
    /// void set_rail_matrix(int,int,bool); ///going to use them in a future version
    /// void set_train_matrix(int,int,bool); ///going to use them in a future version
    void lee(queue<pair<int,int>>&,array<array<int,15>,15>&) const;
    void reset_road_matrix(array<array<int,15>,15>&) const;
    void generate_distances(vector<int>&) const;
    [[nodiscard]] bool correct_order() const;
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

void Level::lee(queue<pair<int,int>>& q,array<array<int,15>,15>& road_matrix) const
{
    ///this functions runs a Lee algorithm on the given road matrix in order to generate the minimum distance
    ///from the starting point to the every other point in the matrix
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

void Level::reset_road_matrix(array<array<int,15>,15>&road_matrix) const
{
    ///this function resets the road matrix between calculating the distance for each train
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            road_matrix[i][j]=0;
}

void Level::generate_distances(vector<int>&distances) const
{
    ///this function generates the distance from each train to the end
    queue<pair<int,int>>q;
    array<array<int,15>,15> road_matrix={};
    for(const pair<Train,pair<int,int>>& train:trains)
        {
            reset_road_matrix(road_matrix);
            q.emplace(train.second.first,train.second.second);
            lee(q,road_matrix);
            distances.push_back(road_matrix[finish_row][finish_column]);
        }
}

bool Level::correct_order() const
{
    ///this function checks if the trains arrive in the correct order at the end
    vector<int>distances;
    generate_distances(distances);
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
            cout<<"Level is valid, it is possible for all trains to reach the end in order."<<'\n';
        else
            cout<<"Oops, this level is not doable with the given constraints."<<'\n';
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