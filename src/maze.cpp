#include "maze.h"
#include "cell.h"
#include "bfs.h"
#include "dfs.h"
#include "astar.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>


Maze::Maze(int rows, int cols, unsigned int seed, unsigned int removePercentage) : numRows(rows), numCols(cols), seed(seed), removePercentage(removePercentage) {

    flat_maze.resize(numRows * numCols);
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            flat_maze[i * numCols + j] = Cell(i * numCols + j,i,j);
        }
    }

}

Maze::~Maze() {
}

void Maze::generate() 
{
    std::cout << "Calculating Neighbours" << std::endl;
    calculate_neighbours();
    std::cout << "Creating Maze" << std::endl;
    turn_map_into_maze();
}

bool Maze::isValid(int row, int col) const 
{
    return (row >= 0 && col >= 0 && row < numRows && col < numCols);
}

void Maze::calculate_neighbours()
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

    for (int i = 0; i < numRows; ++i) 
    {
        for (int j = 0; j < numCols; ++j) 
        {
            for (int k = 0; k < 4; ++k) 
            {
                int newRow = i + directions[k][0];
                int newCol = j + directions[k][1];
                if (isValid(newRow, newCol)) {
                    flat_maze[i * numCols + j].getNeighbours().push_back(&flat_maze[newRow * numCols + newCol]);
                }
            }
        }
    }
}

void Maze::turn_map_into_maze()
{
    srand(seed); //Use with rand() % 4 to get a value between 0 and 3

    //Use recursive backtracking to generate the maze
    std::vector<Cell*> stack;
    stack.push_back(&flat_maze[0]);
    flat_maze[0].visit_during_creation();
    
    //Create the maze.
    while (!stack.empty()) 
    {
        Cell* current = stack.back();
        std::vector<Cell*> neighbours = current->getNeighbours();
        std::vector<Cell*> unvisitedNeighbours;
        for (int i = 0; i < neighbours.size(); ++i) 
        {
            if (!neighbours[i]->been_visited_during_creation()) 
            {
                unvisitedNeighbours.push_back(neighbours[i]);
            }
        }
        if (!unvisitedNeighbours.empty()) 
        {
            Cell* next = unvisitedNeighbours[rand() % unvisitedNeighbours.size()];
            current->getAccessNeighbours().push_back(next);
            next->getAccessNeighbours().push_back(current);
            stack.push_back(next);
            next->visit_during_creation();
        } 
        else 
        {
            stack.pop_back();
        }
    }    

    std::cout << "Removing walls" << std::endl;
    if (removePercentage > 0)
    {
        remove_random_walls_version_2();
    }
}

int Maze::squared(int num)
{
    return num * num;
}

void Maze::remove_random_walls_version_2()
{
    int maximum = std::max(numRows, numCols);
    int minimum = std::min(numRows, numCols);
    int totalWalls = squared(maximum - 1) - ((maximum - 1) * (maximum - minimum));
    int wallsToRemove = totalWalls * removePercentage / 100;

    int count = 0;
    while (count < wallsToRemove)
    {
        int randomRow = (rand() % numRows);
        int randomCol = (rand() % numCols);
        int randomNeighbour = rand() % 4;

        std::vector<Cell*> neighbours = flat_maze[randomRow * numCols + randomCol].getNeighbours();
        if (neighbours.size() < randomNeighbour + 1)
        {
            continue;
        }   

        if (std::find(flat_maze[randomRow * numCols + randomCol].getAccessNeighbours().begin(), flat_maze[randomRow * numCols + randomCol].getAccessNeighbours().end(), neighbours[randomNeighbour]) == flat_maze[randomRow * numCols +randomCol].getAccessNeighbours().end()) {
        
            flat_maze[randomRow * numCols + randomCol].getAccessNeighbours().push_back(neighbours[randomNeighbour]);
            neighbours[randomNeighbour]->getAccessNeighbours().push_back(&flat_maze[randomRow * numCols + randomCol]);
            count++;
        
        }
    }
}

void Maze::display(std::vector<int> path)
{
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maze");
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }
        window.clear(sf::Color::White);

        int width = window.getSize().x;
        int height = window.getSize().y;
        int cell_width = (width - 10) / numCols;
        int cell_height = (height - 10) / numRows;
        int cell_size = std::min(cell_width, cell_height);

        for(int i = 0; i < numRows; ++i)
        {
            for(int j = 0; j < numCols; ++j)
            {
                sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
                cell.setOutlineThickness(0.5);
                //cell.setOutlineColor(sf::Color::Black);
                cell.setFillColor(sf::Color::White);
                float cellPosX = (width / 2) - (numCols * cell_size / 2) + (j * cell_size);
                float cellPosY = (height / 2) - (numRows * cell_size / 2) + (i * cell_size);
                cell.setPosition(cellPosX, cellPosY);
    
                if (std::find(path.begin(), path.end(), i * numCols + j) != path.end()) 
                {
                    //cell.setFillColor(sf::Color::Blue);
                    //Draw another red squre on top of the blue square but slightly smaller
                    sf::RectangleShape pathCell(sf::Vector2f(cell_size - (cell_size/2), cell_size - (cell_size/2)));
                    pathCell.setOutlineThickness(0.5);
                    pathCell.setOutlineColor(sf::Color::Blue);
                    pathCell.setFillColor(sf::Color::Blue);
                    pathCell.setPosition(cellPosX + (cell_size/4), cellPosY + (cell_size/4));
                    window.draw(pathCell);
                    

                }
                else
                {
                    window.draw(cell);
                }



                std::vector<Cell*> neighbours = flat_maze[i * numCols + j].getAccessNeighbours();
                sf::VertexArray borderLines(sf::Lines, 8);                
                int cell_id = flat_maze[i * numCols + j].getID();
                
                if (std::find(neighbours.begin(), neighbours.end(), &flat_maze[cell_id - numCols]) == neighbours.end()) {
                    //Cell above
                    borderLines[0].position = sf::Vector2f(cellPosX, cellPosY);
                    borderLines[1].position = sf::Vector2f(cellPosX + cell_size, cellPosY);
                }
                if (std::find(neighbours.begin(), neighbours.end(), &flat_maze[cell_id + numCols]) == neighbours.end()) {
                    //Cell below
                    borderLines[2].position = sf::Vector2f(cellPosX + cell_size, cellPosY + cell_size);
                    borderLines[3].position = sf::Vector2f(cellPosX, cellPosY + cell_size);
                }
                if (std::find(neighbours.begin(), neighbours.end(), &flat_maze[cell_id - 1]) == neighbours.end()) {
                    //Cell left
                    borderLines[4].position = sf::Vector2f(cellPosX, cellPosY + cell_size);
                    borderLines[5].position = sf::Vector2f(cellPosX, cellPosY);
                }
                if (std::find(neighbours.begin(), neighbours.end(), &flat_maze[cell_id + 1]) == neighbours.end()) {
                    //Cell right
                    borderLines[6].position = sf::Vector2f(cellPosX + cell_size, cellPosY);
                    borderLines[7].position = sf::Vector2f(cellPosX + cell_size, cellPosY + cell_size);
                }

                // Set color for all lines
                for (int k = 0; k < 8; k += 2) 
                {
                    borderLines[k].color = sf::Color::Red;
                    borderLines[k + 1].color = sf::Color::Red;
                }
                window.draw(borderLines);
            }
        }
        window.display();
    }
}

