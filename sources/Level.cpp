#include "../includes/Level.h"

void Level::set_rail_matrix(int row,int column)
{
    rail_matrix[row][column]='R';
    available_rails--;
}

void Level::unset_rail_matrix(int row,int column)
{
    rail_matrix[row][column]='0';
    available_rails++;
}

void Level::add_rails(int add)
{
    available_rails+=add;
}

int Level::get_available_rails() const
{
    return this->available_rails;
}

bool Level::free(int row,int column) const
{
    if(0<=row && row<=this->n && 0<=column && column<=this->m)
        return rail_matrix[row][column]=='0'; ///checks if this cell is free
    else
        return false;
}

/*void Level::lee(std::queue<std::pair<int,int>>& q,std::array<std::array<int,MAX_DIM>,MAX_DIM>& road_matrix) const
{
    ///this functions runs a Lee algorithm on the given road matrix in order to generate the minimum distance
    ///from the starting point to every other point in the matrix
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

void Level::reset_road_matrix(std::array<std::array<int,MAX_DIM>,MAX_DIM>&road_matrix) const
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
        if(road_matrix[finish_row][finish_column]==0 && train.second.first!=finish_row && train.second.second!=finish_column)
            distances.push_back(-1);///the train cannot reach the end with the given level configuration
        else
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
        else if(distances[i]==-1)///the train cannot reach the destination
            return false;
    return true;
}*/

std::string Level::get_solution() const
{
    std::string solution;
    for(int i=0; i<this->n; i++)
    {
        solution+=rail_matrix[i][0];
        for(int j=1; j<this->m; j++)
        {
            solution+=" ";
            solution+=rail_matrix[i][j];
        }
        solution+="\n";
    }
    return solution;
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
        Train t(i+1);
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
            if(l.rail_matrix[i][j]=='0')
            {
                rlutil::setColor(15);
                out<<l.rail_matrix[i][j]<<' ';
            }
            else if(l.rail_matrix[i][j]=='R')
            {
                rlutil::setColor(8);
                out<<l.rail_matrix[i][j]<<' ';
            }
            else if(l.rail_matrix[i][j]=='U')
            {
                rlutil::setColor(5);
                out<<l.rail_matrix[i][j]<<' ';
            }
            else if(l.rail_matrix[i][j]=='I')
            {
                rlutil::setColor(4);
                out<<l.rail_matrix[i][j]<<' ';
            }
            else if(l.rail_matrix[i][j]=='F')
            {
                rlutil::setColor(14);
                out<<l.rail_matrix[i][j]<<' ';
            }
            else if(l.rail_matrix[i][j]=='T')
            {
                rlutil::setColor(1);
                out<<l.rail_matrix[i][j]<<' ';
            }
        out<<'\n';
    }
    rlutil::setColor(15);
    out<<'\n';
    out<<"x="<<l.n<<" y="<<l.m<<"\n\n"<<"Number of available rails: "<<l.available_rails<<"\n\n";
    out<<"Train positions, number and color: \n";
    for(const std::pair<Train,std::pair<int,int>>& train:l.trains)
        out<<train.second.first<<' '<<train.second.second<<' '<<train.first;
    out<<'\n';
    return out;
}