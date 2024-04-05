#include "maze.h"
#include "cell.h"
#include "tremaux.h"

#include <iostream>
#include <vector>
#include <stack>

Tremaux::Tremaux(Maze& maze) : maze(maze) {
}

Tremaux::~Tremaux() {
}

void Tremaux::run() {
    Cell* start = &maze.flat_maze[0];
    Cell* end = &maze.flat_maze[maze.flat_maze.size() - 1];
    
    //Implementing the tremaux algorithm
    
}

std::vector<int> Tremaux::get_path() {
    return path;
}
