#ifndef BFS_H
#define BFS_H

class BFS 
{
private:
    Maze& maze;
    std::vector<int> path;

public:
    BFS(Maze& maze);
    ~BFS();
    void run();
    std::vector<int> get_path();
};


#endif