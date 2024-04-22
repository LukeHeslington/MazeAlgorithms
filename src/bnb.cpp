#include "maze.h"
#include "cell.h"
#include "bnb.h"

#include <iostream>
#include <vector>
#include <stack>
#include <limits>

BNB::BNB(Maze& maze) : maze(maze) {
}

BNB::~BNB() {
}

void BNB::run() {
    Cell* start = &maze.flat_maze[0];
    Cell* end = &maze.flat_maze[maze.flat_maze.size() - 1];
    int min_distance = std::numeric_limits<int>::max();
    int cells_visited = 0;

    
    std::stack<Cell*> stack;
    stack.push(start);
    while(!stack.empty()){
        Cell* current = stack.top();
        current->in_stack = true;
        current->distanceFromStart = current->parent ? current->parent->distanceFromStart + 1 : 0;
        
        //std::cout << "Current: " << current->getID() << "Distance from start: " << current->distanceFromStart << std::endl;

        



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

        //Given the current cell index, calculate how far it is from the end cell.
        //std::cout << "Current: " << current->getID() << " Distance from start: " << current->distanceFromStart << " Min distance: " << min_distance << std::endl;
        int current_i_index = current->getID() % maze.numCols;
        int current_j_index = current->getID() / maze.numCols;
        //std::cout << "Current i index: " << current_i_index << " Current j index: " << current_j_index << std::endl;
        
        int end_i_index = end->getID() % maze.numCols;
        int end_j_index = end->getID() / maze.numCols;
        //std::cout << "End i index: " << end_i_index << " End j index: " << end_j_index << std::endl;

        int distance = abs(current_i_index - end_i_index) + abs(current_j_index - end_j_index);
        //std::cout << "Distance: " << distance << std::endl;

        //break;

        if (current->distanceFromStart < min_distance){//&& (current->distanceFromStart + distance + 1) < min_distance) {
            //std::cout << "Distance from start: " << current->distanceFromStart << " Min distance: " << min_distance << std::endl;
            for (int i = 0; i < neighbours.size(); ++i) {
                if (!neighbours[i]->in_stack) {
                    current->neighbours_added_to_stack.push_back(neighbours[i]);
                    neighbours[i]->parent = current;
                    pop = false;
                    stack.push(neighbours[i]);
                    neighbours[i]->in_stack = true;
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
    maze.cells_visited = cells_visited;
}

std::vector<int> BNB::get_path() {
    return path;
}
