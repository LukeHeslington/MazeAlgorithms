#include "maze.h"
#include "cell.h"
#include "astar.h"

#include <iostream>
#include <vector>

AStar::AStar(Maze& maze) : maze(maze) 
{
}

AStar::~AStar() 
{
}

void AStar::run() 
{
    std::cout << "AStar run" << std::endl;

    Cell* start = &maze.flat_maze[0];
    Cell* end = &maze.flat_maze[maze.flat_maze.size() - 1];

    std::vector<Cell*> open;
    std::vector<Cell*> closed;
    open.push_back(start);
    int cells_visited = 0;
    while (!open.empty()) 
    {
        Cell* current = open.front();
        for (auto& node : open) 
        {
            if (node->f + node->h < current->f + current->h) 
            {
                current = node;
            }
        }

        open.erase(std::remove(open.begin(), open.end(), current), open.end());
        closed.push_back(current);
        cells_visited++;
        current->visit_during_algorithm();

        if (current == end) 
        {
            break;
        }

        std::vector<Cell*>& neighbours = current->getAccessNeighbours();
        for (auto& neighbour : neighbours) 
        {
            if (std::find(closed.begin(), closed.end(), neighbour) != closed.end()) 
            {
                continue;
            }

            int tentative_g = current->g + 1;
            if (std::find(open.begin(), open.end(), neighbour) == open.end() || tentative_g < neighbour->g) 
            {
                neighbour->parent = current;
                neighbour->g = tentative_g;
                neighbour->h = neighbour->manhattan_distance(end);
                neighbour->f = neighbour->g + neighbour->h;

                if (std::find(open.begin(), open.end(), neighbour) == open.end()) 
                {
                    open.push_back(neighbour);
                }
            }
        }
    }
    
    //Print the path backtracking from the end to the start using the parent.
    if (end->parent == nullptr) 
    {
        std::cout << "No path found!" << std::endl;
        return;
    }
    
    Cell* current = end;
    while (current != start) 
    {
        path.push_back(current->getID());
        current = current->parent;
    }
    path.push_back(start->getID());
}


std::vector<int> AStar::get_path() 
{
    return path;
}