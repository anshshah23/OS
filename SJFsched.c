#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, p;
    printf("Enter the number of processes: ");
    scanf("%d", &p);

    int bt[p], at[p], wt[p], tat[p], ct[p], temp;
    float avg_wait = 0.0, avg_turn = 0.0;
    printf("Enter the arrival time and the burst time: \n");
    for (i = 0; i < p; i++) {
        printf(" P[%d]: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }
    printf("\n");
    printf("The AT and BT are: \n");
    for (i = 0; i < p; i++) {
        printf("for P[%d]: AT[%d] & BT[%d]\n", i + 1, at[i], bt[i]);
    }

    // Sort processes based on burst time, maintaining corresponding arrival times
    for (i = 0; i < p - 1; i++) {
        for (j = 0; j < p - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;
            }
        }
    }

    printf("\n");
    printf("The Sorted AT and BT are: \n");
    for (i = 0; i < p; i++) {
        printf("for P[%d]: AT[%d] & BT[%d]\n", i + 1, at[i], bt[i]);
    }

    // Calculate completion time
    for (i = 0; i < p; i++) {
        if (i == 0) {
            ct[i] = at[i] + bt[i];
        } else if (at[i] > ct[i - 1]) {
            ct[i] = at[i] + bt[i];
        } else {
            ct[i] = ct[i - 1] + bt[i];
        }
    }

    // Calculate turnaround time and waiting time
    for (i = 0; i < p; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        printf("P[%d] - WT[%d] and TAT[%d]\n", i + 1, wt[i], tat[i]);
    }

    // Calculate average waiting time and average turnaround time
    for (i = 0; i < p; i++) {
        avg_wait += wt[i];
        avg_turn += tat[i];
    }

    avg_wait /= p;
    avg_turn /= p;

    printf("The Average Waiting Time: %f\n", avg_wait);
    printf("The Average Turnaround Time: %f\n", avg_turn);
    return 0;
}
