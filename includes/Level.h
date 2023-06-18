#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <array>
#include <queue>
#include "Train.h"

class Level
{
private:
    const static int MAX_DIM=15; /// if initialized outside of the class (as it should be) then the declaration of the array doesn't work
    std::array<std::array<bool,MAX_DIM>,MAX_DIM>rail_matrix={},solution={};
    int n,m,available_rails,train_no,finish_row,finish_column;
    std::vector<std::pair<Train,std::pair<int,int>>>trains;
    void lee(std::queue<std::pair<int,int>>&,std::array<std::array<int,MAX_DIM>,MAX_DIM>&) const;
    void reset_road_matrix(std::array<std::array<int,MAX_DIM>,MAX_DIM>&) const;
    void generate_distances(std::vector<int>&) const;
public:
    explicit Level(int dim_row=0,int dim_col=0,int rails=0,int number=1,int row=0,int column=0):
            n(dim_row),m(dim_col),available_rails(rails),train_no(number),finish_row(row),finish_column(column)
            {
                if(dim_row<0 || dim_col<0 || number<1)
                    throw value_error("This level cannot be created. Please introduce valid information.");
            }
    void set_rail_matrix(int,int);
    void add_rails(int);
    [[nodiscard]] bool free(int,int) const;
    [[nodiscard]] bool correct_order() const;
    [[nodiscard]] int game_over() const;
    void print_solution() const;
    friend std::istream& operator >>(std::istream&,Level&);
    friend std::ostream& operator <<(std::ostream&,const Level&);
};

#endif