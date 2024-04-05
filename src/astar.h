#ifndef ASTAR_H
#define ASTAR_H

class AStar 
{
private:
    Maze& maze;
    std::vector<int> path;

public:
    AStar(Maze& maze);
    ~AStar();
    void run();
    std::vector<int> get_path();
};

#endif