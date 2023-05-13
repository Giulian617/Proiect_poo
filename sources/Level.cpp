#include "../includes/Level.h"

// void Level::set_rail_matrix(int row,int column,bool used)
//{
//    rail_matrix[row][column]=used;
//}
//
// void Level::set_train_matrix(int row,int column,bool used)
//{
//    train_matrix[row][column]=used;
//}

void Level::lee(std::queue<std::pair<int,int>>& q,std::array<std::array<int,15>,15>& road_matrix) const
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

void Level::reset_road_matrix(std::array<std::array<int,15>,15>&road_matrix) const
{
    ///this function resets the road matrix between calculating the distance for each train
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            road_matrix[i][j]=0;
}

void Level::generate_distances(std::vector<int>&distances) const
{
    ///this function generates the distance from each train to the end
    std::queue<std::pair<int,int>>q;
    std::array<std::array<int,15>,15> road_matrix={};
    for(const std::pair<Train,std::pair<int,int>>& train:trains)
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
    std::vector<int>distances;
    generate_distances(distances);
    for(int i=1; i<(int)distances.size(); i++)
        if(distances[i]<=distances[i-1])///the trains arrive at the station in incorrect order
            return false;
    return true;
}

std::istream& operator >>(std::istream& in,Level& l)
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

std::ostream& operator <<(std::ostream& out,const Level& l)
{
    for(int i=0; i<l.n; i++)
    {
        for(int j=0; j<l.m; j++)
            out<<l.rail_matrix[i][j]<<' ';
        out<<'\n';
    }
    out<<'\n';
    for(const std::pair<Train,std::pair<int,int>>& train:l.trains)
        out<<train.second.first<<' '<<train.second.second<<' '<<train.first;
    out<<'\n';
    return out;
}