#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <array>
#include <queue>
#include "Train.h"
using namespace std;

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

#endif