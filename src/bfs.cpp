#include "maze.h"
#include "cell.h"
#include "bfs.h"

#include <iostream>
#include <vector>
#include <queue>

BFS::BFS(Maze& maze) : maze(maze) 
{
}

BFS::~BFS() 
{
}

void BFS::run() 
{
    Cell* start = &maze.flat_maze[0];
    Cell* end = &maze.flat_maze[maze.flat_maze.size() - 1];
    std::queue<Cell*> queue;
    queue.push(start);
    int cells_visited = 0;

    while(!queue.empty()) 
    {
        Cell* current = queue.front();
        queue.pop();
        current->been_visited_during_algorithm();

        if (current == end) 
        {
            break;
        }

        cells_visited++;
        std::vector<Cell*> neighbours = current->getAccessNeighbours();
        for (int i = 0; i < neighbours.size(); ++i) 
        {
            if (!neighbours[i]->been_visited_during_algorithm() && neighbours[i]->parent == nullptr) 
            {
                neighbours[i]->parent = current;
                queue.push(neighbours[i]);
            }
        }
    }

    Cell* current = end;
    while (current != start) 
    {
        path.push_back(current->getID());
        current = current->parent;
    }
    path.push_back(start->getID());

    maze.cells_visited = cells_visited;
}

std::vector<int> BFS::get_path() 
{
    return path;
}

