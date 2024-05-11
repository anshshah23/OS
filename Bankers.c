#include <stdio.h>

// Number of processes
#define P 5

// Number of resources
#define R 3

// Available instances of each resource
int available[R] = {3, 3, 2};

// Maximum demand of each process
int maximum[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// Allocated resources for each process
int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// Need matrix (maximum - allocation) for each process
int need[P][R];

// Function to initialize the need matrix
void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the current state is safe
int isSafe(int processes[], int available[], int need[][R]) {
    int work[R];
    int finish[P];

    // Initialize work and finish arrays
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < P; i++) {
        finish[i] = 0;
    }

    int count = 0;
    while (count < P) {
        int found = 0;
        
        for (int i = 0; i < P; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    processes[count++] = i;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            break;
        }
    }

    if (count < P) {
        return 0; // Unsafe state
    } else {
        return 1; // Safe state
    }
}

int main() {
    int processes[P];
    calculateNeed();

    printf("Initial Allocation Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Available resources: ");
    for (int i = 0; i < R; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    // Check if the initial state is safe
    if (isSafe(processes, available, need)) {
        printf("System is in a safe state.\n");
        printf("Safe sequence is: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", processes[i]);
        }
        printf("\n");
    } else {
        printf("System is in an unsafe state.\n");
    }

    return 0;
}
