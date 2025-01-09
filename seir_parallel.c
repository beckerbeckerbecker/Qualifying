// Refactored version of finalproject.c from 6330 repository
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#define GRID_SIZE 100 // Define the population grid size
#define MAX_ITERATIONS 1000 // Maximum number of simulation iterations

// Function to initialize the population grid
void initPopGrid(char Population[GRID_SIZE][GRID_SIZE]) {
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int randState = rand() % 4; // 0: Susceptible, 1: Exposed, 2: Infected, 3: Recovered
            switch (randState) {
                case 0:
                    Population[i][j] = 'S';
                    break;
                case 1:
                    Population[i][j] = 'E';
                    break;
                case 2:
                    Population[i][j] = 'I';
                    break;
                case 3:
                    Population[i][j] = 'R';
                    break;
            }
        }
    }
}

// Function to simulate one step of the SEIR model
void simulateStep(char Population[GRID_SIZE][GRID_SIZE]) {
    char tempGrid[GRID_SIZE][GRID_SIZE];
    memcpy(tempGrid, Population, GRID_SIZE * GRID_SIZE * sizeof(char));

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            switch (Population[i][j]) {
                case 'S':
                    // Susceptible -> Exposed with a probability
                    if ((rand() % 100) < 10) {
                        tempGrid[i][j] = 'E';
                    }
                    break;
                case 'E':
                    // Exposed -> Infected with a probability
                    if ((rand() % 100) < 20) {
                        tempGrid[i][j] = 'I';
                    }
                    break;
                case 'I':
                    // Infected -> Recovered with a probability
                    if ((rand() % 100) < 30) {
                        tempGrid[i][j] = 'R';
                    }
                    break;
                default:
                    break;
            }
        }
    }

    memcpy(Population, tempGrid, GRID_SIZE * GRID_SIZE * sizeof(char));
}

int main(int argc, char *argv[]) {
    int rank, size;
    char Population[GRID_SIZE][GRID_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        initPopGrid(Population); // Initialize grid on the root process
    }

    MPI_Bcast(Population, GRID_SIZE * GRID_SIZE, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        simulateStep(Population);

        // Gather results from all processes (if required for analysis)
        MPI_Gather(MPI_IN_PLACE, GRID_SIZE * GRID_SIZE / size, MPI_CHAR,
                   Population, GRID_SIZE * GRID_SIZE / size, MPI_CHAR, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            printf("Iteration %d completed.\n", iter);
        }
    }

    MPI_Finalize();
    return 0;
}