#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Include limits.h for INT_MAX

int main() {
    int i, j, p, current_time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &p);

    int bt[p], at[p], wt[p], tat[p], rt[p], temp;
    float avg_wait = 0.0, avg_turn = 0.0;

    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < p; i++) {
        printf("P[%d]: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i]; // Remaining time initially equals burst time
    }

    // Sort processes based on arrival time
    for (i = 0; i < p ; i++) {
        for (j = 0; j < p - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = rt[j];
                rt[j] = rt[j + 1];
                rt[j + 1] = temp;
            }
        }
    }

    printf("\nGantt Chart:\n");
    printf("--------------------------------------------------\n");
    printf("Time | Process\n");
    printf("--------------------------------------------------\n");

    // Run the scheduling algorithm
    while (completed < p) {
        int shortest_job = -1;
        int shortest_burst = INT_MAX;

        for (i = 0; i < p; i++) {
            if (at[i] <= current_time && rt[i] < shortest_burst && rt[i] > 0) {
                shortest_job = i;
                shortest_burst = rt[i];
            }
        }

        if (shortest_job == -1) {
            current_time++;
            continue;
        }

        // Execute the shortest job for one unit
        rt[shortest_job]--;
        current_time++;

        // Check if the process is completed
        if (rt[shortest_job] == 0) {
            completed++;
            int finish_time = current_time;
            int turnaround_time = finish_time - at[shortest_job];
            tat[shortest_job] = turnaround_time;
            wt[shortest_job] = turnaround_time - bt[shortest_job];

            // Print process completion
            printf("%3d  |  P[%d]\n", current_time, shortest_job + 1);
            printf("     |  TAT: %d, WT: %d\n", tat[shortest_job], wt[shortest_job]);
        }
    }

    printf("--------------------------------------------------\n");

    // Calculate average waiting time and average turnaround time
    for (i = 0; i < p; i++) {
        avg_wait += wt[i];
        avg_turn += tat[i];
    }

    avg_wait /= p;
    avg_turn /= p;

    printf("Average Waiting Time: %.2f\n", avg_wait);
    printf("Average Turnaround Time: %.2f\n", avg_turn);

    return 0;
}
