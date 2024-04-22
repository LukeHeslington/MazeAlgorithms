#ifndef MAZE_H
#define MAZE_H

#include "cell.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class Maze {
private:
    int seed;
    int removePercentage;

public:
    // Constructor
    Maze(int rows, int cols, unsigned int seed, unsigned int removePercentage);

    //Destructor
    ~Maze();

    //Generate the maze
    void generate();
    void calculate_neighbours();
    void turn_map_into_maze();
    void display(std::vector<int> path);
    bool isValid(int row, int col) const;
    void remove_random_walls();
    void remove_random_walls_version_2();
    int squared(int x);

    std::vector<Cell> flat_maze;
    int numRows;
    int numCols;
    int cells_visited;
    int total_walls = (numRows - 1) * numCols + (numCols - 1) * numRows;
    double removed_walls = 0;

};

#endif /* MAZE_H */