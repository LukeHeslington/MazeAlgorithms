#ifndef TREMAUX_H
#define TREMAUX_H

class Tremaux {
private:
    Maze& maze;
    std::vector<int> tempPath;
    std::vector<int> path;
    std::vector<Cell*> fastest_path;
    void backtrack(Cell* current, std::vector<Cell*>& tempPath);

public:
    Tremaux(Maze& maze);
    ~Tremaux();
    void run();
    std::vector<int> get_path();
};


#endif