#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include "maze.h"
#include "bfs.h"
#include "dfs.h"
#include "astar.h"
#include "bnb.h"


//Arguments will be -d 
int main(int argc, char *argv[]) 
{

    std::vector<std::string> algorithms = {"bfs", "BFS", "dfs", "DFS", "dijkstra", "Dijkstra", "a*", "A*", "BNB", "bnb","Tremaux","tremaux"};

    if (argc < 4) 
    {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }
    std::cout << "INFORMATION: " << std::endl;
    if (std::find(algorithms.begin(), algorithms.end(), argv[1]) != algorithms.end()) 
    {
        std::cout << "Algorithm: " << argv[1] << std::endl;
    } else 
    {
        std::cout << "Invalid algorithm" << std::endl;
        return 1;
    }

    int rows = 0;
    int cols = 0;
    if (argc > 3) 
    {
        rows = atoi(argv[2]);
        cols = atoi(argv[3]);
    }

    //need to make the seed random based on srand
    int seed = 0;
    if (argc > 4) 
    {
        seed = atoi(argv[4]);
    }
    std::cout << "Seed value: " << seed << std::endl;

    int removePercentage = atoi(argv[5]);
    std::cout << "Remove " << removePercentage << "% of the walls\n" << std::endl;

    bool displayGraphics = false;
    for (int i = 1; i < argc; ++i) 
    {
        if (std::string(argv[i]) == "-d") 
        {
            displayGraphics = true;
            break;
        }
    }

    //call the maze class with the arguments rows, cols, seed.
    Maze maze(rows, cols, seed, removePercentage);
    std::cout << "CURRENT STEP: " << std::endl;
    maze.generate();

    //Run the algorithm function based on the argument
    std::vector<int> path;

    std::cout << "Running the algorithm" << std::endl;
    //start timing
    auto start = std::chrono::high_resolution_clock::now();

    
    if (std::string(argv[1]) == "bfs" || std::string(argv[1]) == "BFS") {BFS bfs(maze); bfs.run(); path = bfs.get_path();}
    else if (std::string(argv[1]) == "dfs" || std::string(argv[1]) == "DFS") {DFS dfs(maze); dfs.run(); path = dfs.get_path();}
    else if (std::string(argv[1]) == "astar" || std::string(argv[1]) == "A*") {AStar AStar(maze); AStar.run(); path = AStar.get_path();}
    else if (std::string(argv[1]) == "bnb" || std::string(argv[1]) == "BNB") {BNB BNB(maze); BNB.run(); path = BNB.get_path();}


    //end timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "\nSTATISTICS:" << std::endl;
    std::cout << "Cells visited: " << maze.cells_visited << std::endl;
    std::cout << "Time taken: " << elapsed_seconds.count() << "s\n";
    std::cout << "Path length: " << path.size() << std::endl;


    if (displayGraphics) 
    {
        maze.display(path);
    }

















    return 0;
}