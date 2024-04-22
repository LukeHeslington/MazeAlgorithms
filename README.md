# MazeAlgorithms

This repository contains various maze solving algorithms implemented in C++.

## Prerequisites

Before using this repository, ensure you have the following dependencies installed:

- **CMake**: A cross-platform build system generator. Install it using your package manager or download it from [cmake.org](https://cmake.org/download/).
- **C++ Compiler**: Make sure you have a C++ compiler installed. For example, you can use GCC or Clang.
- **SFML Graphics** You can install this by doing: `sudo apt-get install libsfml-dev`

## Installation

To build and run the MazeAlgorithms, follow these steps:

1. Clone this repository to your local machine:

```
git clone https://github.com/yourusername/MazeAlgorithms.git
cd MazeAlgorithms
```

2. Create a build directory:

```
mkdir build
cd build
```
  
3. Generate build files using CMake and build the project:

```
cmake ..
make
```

## Usage

Once you've built the project, you can use the executable to generate and solve mazes. Here's how to run it with arguments:

- **algorithm**: Specify the algorithm to use for maze generation.
- **row**: Number of rows in the maze.
- **col**: Number of columns in the maze.
- **seed**: Seed for random number generation.
- **removal**: Percentage of walls to remove after geneation to increase difficulty.
- **-d**: Enable display mode.

### Example:

`./MazeSolver A* 20 30 12345 50 -d`

This command will generate a maze of size 20x30 using the A* algorithm with a seed of 12345. It will also remove 50% of the walls and enable the display.

### Available Algorithms and how to input them:

- A* (A* or astar)
- Breadth First Search (BFS or bfs)
- Depth First Search (DFS or dfs)
- Branch and Bound (BNB or BnB)


