#ifndef DFS_H
#define DFS_H

class DFS {
private:
    Maze& maze;
    std::vector<int> tempPath;
    std::vector<int> path;
    std::vector<Cell*> fastest_path;
    void backtrack(Cell* current, std::vector<Cell*>& tempPath);

public:
    DFS(Maze& maze);
    ~DFS();
    void run();
    std::vector<int> get_path();
};


#endif