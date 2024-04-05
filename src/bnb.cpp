#include "maze.h"
#include "cell.h"
#include "bnb.h"

#include <iostream>
#include <vector>
#include <stack>

BNB::BNB(Maze& maze) : maze(maze) {
}

BNB::~BNB() {
}

void BNB::run() {
    Cell* start = &maze.flat_maze[0];
    Cell* end = &maze.flat_maze[maze.flat_maze.size() - 1];
    int min_distance = 1000;
    
    std::stack<Cell*> stack;
    stack.push(start);
    int cells_visited = 0;
    while(!stack.empty()){
        Cell* current = stack.top();
        current->in_stack = true;

        if (current == end) {
            Cell* current = end;
            int count = 0;
            while (current != start) {
                count++;
                tempPath.push_back(current->getID());
                current = current->parent;
            }
            tempPath.push_back(start->getID());
            if (tempPath.size() < min_distance) {
                min_distance = tempPath.size();
                path = tempPath;
            }
            tempPath.clear();
        }

        std::vector<Cell*> neighbours = current->getAccessNeighbours();
        bool pop = true;
        std::stack<Cell*> temp_stack = stack;
        while (!temp_stack.empty()) {
            temp_stack.pop();
        }

        for (int i = 0; i < neighbours.size(); ++i) {
            if (!neighbours[i]->in_stack) {
                current->neighbours_added_to_stack.push_back(neighbours[i]);
                neighbours[i]->parent = current;
                stack.push(neighbours[i]);
                neighbours[i]->in_stack = true;

                // Update path_length of the neighbor
                neighbours[i]->path_length = current->path_length + 1;

                // Check if the current path length exceeds min_distance
                if (neighbours[i]->path_length >= min_distance) {
                    pop = true; // Set pop flag to true to stop further pushing
                    break; // Exit the loop
                }
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
}

std::vector<int> BNB::get_path() {
    return path;
}
