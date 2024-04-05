#ifndef BNB_H
#define BNB_H

class BNB {
private:
    Maze& maze;
    std::vector<int> tempPath;
    std::vector<int> path;
    std::vector<Cell*> fastest_path;
    void backtrack(Cell* current, std::vector<Cell*>& tempPath);
    int distanceFromStart = -1;

public:
    BNB(Maze& maze);
    ~BNB();
    void run();
    std::vector<int> get_path();
};


#endif