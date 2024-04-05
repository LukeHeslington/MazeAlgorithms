#include "cell.h"
#include <iostream>

// Constructor
Cell::Cell(int cellID, int row, int col) : id(cellID), row(row), col(col) {}

// Destructor
Cell::~Cell() {}

int Cell::getID() const {
    return id;
}

void Cell::setNeighbours(std::vector<Cell*>&& neighbours) {
    cellsNeighbours = std::move(neighbours);
}

std::vector<Cell*>& Cell::getNeighbours() {
    return cellsNeighbours;
}

bool Cell::been_visited_during_creation() {
    return visitedDuringCreation;
}

void Cell::visit_during_creation() {
    visitedDuringCreation = true;
}

std::vector<Cell*>& Cell::getAccessNeighbours(){
    return accessNeighbours;
}

bool Cell::been_visited_during_algorithm() {
    return visitedDuringAlgorithm;
}

void Cell::visit_during_algorithm() {
    visitedDuringAlgorithm = true;
}

void Cell::unvisit_during_algorithm() {
    visitedDuringAlgorithm = false;
}

int Cell::manhattan_distance(Cell* end) {
    return abs(row - end->row) + abs(col - end->col);
}
