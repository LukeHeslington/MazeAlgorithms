#include "maze.h"
#include "cell.h"
#include "astar.h"

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class CompareF {
public:
    bool operator()(const Cell* a, const Cell* b) const {
        return a->f > b->f;
    }
};

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
    std::priority_queue<Cell*, std::vector<Cell*>, CompareF> open;
    std::vector<Cell*> closed;
    open.push(start);
    start->in_open = true;
    int cells_visited = 0;
    
    while (!open.empty()) 
    {
        Cell* q = open.top();
        open.pop();
        q->in_open = false;

        std::vector<Cell*>& neighbours = q->getAccessNeighbours();

        for (auto& neighbour : neighbours) 
        {
            if (neighbour == end) 
            {
                std::cout << "Goal found!" << std::endl;
                end->parent = q;
                closed.push_back(q);

                Cell* current = end;
                int counter = 0;
                while (current != start) 
                {   
                    counter++;
                    path.push_back(current->getID());
                    current = current->parent;
                }
                path.push_back(start->getID());
                
                std::cout << "Cells visited: " << cells_visited << std::endl;
                return;
            }

            int tentative_g = q->g + 1;
            int tentative_h = neighbour->manhattan_distance(end);
            int tentative_f = tentative_g + tentative_h;

            if (neighbour->in_open == true && tentative_f >= neighbour->f) 
            {
                continue;
            }
            else if (neighbour->in_closed == true && tentative_f >= neighbour->f) 
            {
                continue;
            }
            else
            {
                neighbour->parent = q;
                neighbour->g = tentative_g;
                neighbour->h = tentative_h;
                neighbour->f = tentative_f;
                open.push(neighbour);
                neighbour->in_open = true;
            }
        }

        cells_visited++;
        closed.push_back(q);
        q->in_closed = true;
    }

}

std::vector<int> AStar::get_path() 
{
    return path;
}