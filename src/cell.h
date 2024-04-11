#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell {
private:
    int id;
    int row;
    int col;
    bool dead_end = false;
    std::vector<Cell*> cellsNeighbours;
    std::vector<Cell*> accessNeighbours;
    bool visitedDuringCreation = false;
    bool visitedDuringAlgorithm = false;

public:
    // Constructor
    //Cell(int id = -1);
    Cell(int id = -1, int row = -1, int col = -1);

    // Destructor
    ~Cell();

    int getID() const;
    void setNeighbours(std::vector<Cell*>&& neighbours);
    std::vector<Cell*>& getNeighbours();
    bool been_visited_during_creation();
    void visit_during_algorithm();
    std::vector<Cell*>& getAccessNeighbours();
    bool been_visited_during_algorithm();
    void visit_during_creation();
    void unvisit_during_algorithm();
    
    //BFS
    Cell* parent = nullptr;

    //AStar
    int g = 0;
    int h = 0;
    int f = 0;
    int manhattan_distance(Cell* end);

    //DFS
    bool in_stack = false;
    std::vector<Cell*> neighbours_added_to_stack;

    //BNB
    int path_length = 0;
    int distanceFromStart = 0;


};

#endif /* CELL_H */
