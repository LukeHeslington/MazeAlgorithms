#ifndef MAZE_H
#define MAZE_H

#include "cell.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class Maze {
private:
    int seed;

public:
    // Constructor
    Maze(int rows, int cols, unsigned int seed);

    //Destructor
    ~Maze();

    //Generate the maze
    void generate();
    void calculate_neighbours();
    void turn_map_into_maze();
    void display(std::vector<int> path);
    bool isValid(int row, int col) const;
    void remove_random_walls();

    std::vector<Cell> flat_maze;
    int numRows;
    int numCols;

};

#endif /* MAZE_H */