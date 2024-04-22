#include "maze.h"
#include "cell.h"
#include "dfs.h"

#include <iostream>
#include <vector>
#include <stack>
#include <limits>

DFS::DFS(Maze& maze) : maze(maze) {
}

DFS::~DFS() {
}

void DFS::run() {
    Cell* start = &maze.flat_maze[0];
    Cell* end = &maze.flat_maze[maze.flat_maze.size() - 1];
    int min_distance = std::numeric_limits<int>::max();
    int cells_visited = 0;

    
    std::stack<Cell*> stack;
    stack.push(start);
    while(!stack.empty()){
        Cell* current = stack.top();
        current->in_stack = true;

        if (current == end) {
            Cell* backtrack = end;
            int count = 0;
            while (backtrack != start) {
                count++;
                tempPath.push_back(backtrack->getID());
                backtrack = backtrack->parent;
            }
            tempPath.push_back(start->getID());
            if (tempPath.size() < min_distance) {
                min_distance = tempPath.size();
                path = tempPath;
            }
            tempPath.clear();
        }

        cells_visited++;
        std::vector<Cell*> neighbours = current->getAccessNeighbours();
        bool pop = true;

        for (int i = 0; i < neighbours.size(); ++i) {
            if (!neighbours[i]->in_stack) {
                current->neighbours_added_to_stack.push_back(neighbours[i]);
                neighbours[i]->parent = current;
                pop = false;
                stack.push(neighbours[i]);
                neighbours[i]->in_stack = true;
            }
        }

        if (pop) {
            stack.pop();
            for (int i = 0; i < current->neighbours_added_to_stack.size(); ++i) {
                current->neighbours_added_to_stack[i]->in_stack = false;
                current->neighbours_added_to_stack[i]->parent = nullptr;
            }
            current->neighbours_added_to_stack.clear();    
        }
    }
    maze.cells_visited = cells_visited;
}

std::vector<int> DFS::get_path() {
    return path;
}
