#include <stdio.h>
#include <stdbool.h>

#define DEPTH 5
#define ROW 5
#define COL 5

// Function to check if a given cell (depth, row, col) can be visited or not
bool isSafe(int maze[DEPTH][ROW][COL], int depth, int row, int col) {
    // if the cell is within the maze bounds and not blocked, it is safe
    if (depth >= 0 && row >= 0 && col >= 0 && depth < DEPTH && row < ROW && col < COL && maze[depth][row][col] == 1)
        return true;
    return false;
}

// Recursive function to solve the maze using depth-first search
bool solveMazeUtil(int maze[DEPTH][ROW][COL], int depth, int row, int col, int sol[DEPTH][ROW][COL]) {
    // if the current cell is the destination, we have reached the end
    if (depth == DEPTH - 1 && row == ROW - 1 && col == COL - 1) {
        sol[depth][row][col] = 1;
        return true;
    }

    // Check if the current cell is safe to move
    if (isSafe(maze, depth, row, col)) {
        // mark the cell as part of the solution path
        sol[depth][row][col] = 1;

        // Move down
        if (solveMazeUtil(maze, depth + 1, row, col, sol))
            return true;

        // Move right
        if (solveMazeUtil(maze, depth, row, col + 1, sol))
            return true;

        // If no move works, backtrack and mark the current cell as not part of the solution path
        sol[depth][row][col] = 0;
        return false;
    }

    return false;
}

// Function to solve the maze
bool solveMaze(int maze[DEPTH][ROW][COL]) {
    int sol[DEPTH][ROW][COL] = {0};

    if (!solveMazeUtil(maze, 0, 0, 0, sol)) {
        printf("Solution does not exist\n");
        return false;
    }

    // Print the solution
    printf("Solution path:\n");
    for (int d = 0; d < DEPTH; d++) {
        printf("Depth %d:\n", d);
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                printf("%d ", sol[d][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return true;
}

int main() {
    int maze[DEPTH][ROW][COL] = { { {1, 0, 0, 0, 0},
                                    {1, 1, 0, 1, 0},
                                    {0, 1, 1, 1, 0},
                                    {0, 0, 0, 1, 0},
                                    {0, 0, 0, 1, 1} },

                                  { {1, 1, 1, 1, 1},
                                    {0, 0, 0, 0, 1},
                                    {1, 1, 1, 1, 1},
                                    {1, 0, 0, 0, 0},
                                    {1, 1, 1, 1, 1} },

                                  { {1, 1, 1, 1, 1},
                                    {1, 0, 0, 0, 0},
                                    {1, 1, 1, 1, 1},
                                    {1, 0, 0, 0, 1},
                                    {1, 1, 1, 1, 1} },

                                  { {1, 1, 1, 1, 1},
                                    {1, 0, 0, 0, 1},
                                    {1, 1, 1, 1, 1},
                                    {1, 0, 0, 0, 0},
                                    {1, 1, 1, 1, 1} },

                                  { {1, 1, 1, 1, 1},
                                    {1, 0, 0, 0, 1},
                                    {1, 1, 1, 1, 1},
                                    {1, 0, 0, 0, 1},
                                    {1, 1, 1, 1, 1} } };

    solveMaze(maze);

    return 0;
}
