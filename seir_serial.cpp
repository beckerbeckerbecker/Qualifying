// Refactored version of finalproject_ser.cpp from 6330 repository
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define GRID_SIZE 100 // Define the population grid size
#define MAX_ITERATIONS 1000 // Maximum number of simulation iterations

using namespace std;

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

int main() {
    char Population[GRID_SIZE][GRID_SIZE];

    // Initialize the population grid
    initPopGrid(Population);

    // Run the simulation
    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        simulateStep(Population);
        cout << "Iteration " << iter + 1 << " completed." << endl;
    }

    return 0;
}