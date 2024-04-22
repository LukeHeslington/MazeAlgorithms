#!/bin/bash

dimensions=(10 25 50 100 250 500 750 1000)
seed=10
algorithms=("dfs" "bfs" "bnb" "A*")
remove=0

# Determine what to run once vs multiple times based on $remove.
if [ $remove -eq 0 ]; then
    run_multiple=("dfs" "bnb" "bfs" "A*")
else
    run_once=("dfs" "bnb")
    run_multiple=("bfs" "A*") 
fi

# Clear output file before appending new data
> output.csv

# Add CSV header
echo "Algorithm,Seed,Dimension,Cells Visited,Time Taken,Path Length" > output.csv

# Run DFS and BNB only once
for algorithm in "${run_once[@]}"; do
    dimension="${dimensions[0]}"
    echo "Running algorithm $algorithm with dimensions $dimension (Seed: $seed)"
    output=$(../build/MazeSolver $algorithm $dimension $dimension $seed $remove)
    cells_visited=$(echo "$output" | awk '/^Cells visited:/ {print $3}')
    time_taken=$(echo "$output" | awk '/^Time taken:/ {print $3}')
    path_length=$(echo "$output" | awk '/^Path length:/ {print $3}')
    echo "$algorithm,$seed,$dimension,$cells_visited,$time_taken,$path_length" >> output.csv
done

# Run other algorithms for all dimensions
for dimension in "${dimensions[@]}"; do
    for algorithm in "${run_multiple[@]}"; do
        echo "Running algorithm $algorithm with dimensions $dimension (Seed: $seed)"
        output=$(../build/MazeSolver $algorithm $dimension $dimension $seed $remove)
        cells_visited=$(echo "$output" | awk '/^Cells visited:/ {print $3}')
        time_taken=$(echo "$output" | awk '/^Time taken:/ {print $3}')
        path_length=$(echo "$output" | awk '/^Path length:/ {print $3}')
        echo "$algorithm,$seed,$dimension,$cells_visited,$time_taken,$path_length" >> output.csv
    done
done
