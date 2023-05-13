#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <array>
#include <queue>
#include "Train.h"

class Level
{
private:
    std::array<std::array<bool,15>,15>rail_matrix={};
    int n,m,available_rails,train_no,finish_row,finish_column;
    std::vector<std::pair<Train,std::pair<int,int>>>trains;
public:
    explicit Level(int dim_row=0,int dim_col=0,int rails=0,int number=0,int row=0,int column=0):
            n(dim_row),m(dim_col),available_rails(rails),train_no(number),finish_row(row),finish_column(column) {}
    /// void set_rail_matrix(int,int,bool); ///going to use them in a future version
    /// void set_train_matrix(int,int,bool); ///going to use them in a future version
    void lee(std::queue<std::pair<int,int>>&,std::array<std::array<int,15>,15>&) const;
    void reset_road_matrix(std::array<std::array<int,15>,15>&) const;
    void generate_distances(std::vector<int>&) const;
    [[nodiscard]] bool correct_order() const;
    friend std::istream& operator >>(std::istream&,Level&);
    friend std::ostream& operator <<(std::ostream&,const Level&);
};

#endif