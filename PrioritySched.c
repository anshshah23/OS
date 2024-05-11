#include <stdio.h>

void Pri(int processes[], int n, int bt[], int wt[], int tat[], int priority[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (priority[j] > priority[j + 1]) // Sort based on priority
            {
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;

                temp = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp;
            }
        }
    }

    wt[0] = 0;

    for (int i = 1; i < n; i++)
    {
        wt[i] = bt[i - 1] + wt[i - 1];
        tat[i] = bt[i] + wt[i];
    }

    float avg_wt = 0, avg_tat = 0;

    for (int i = 0; i < n; i++)
    {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("P \tBT \tPriority \tWT \tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P[%d]\t%d\t%d\t\t%d\t%d\n", processes[i], bt[i], priority[i], wt[i], tat[i]);
    }

    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

int main()
{

    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[0];

    int bt[] = {10, 5, 8};
    int wt[n], tat[n];
    printf("\n--- Priority (non pre-emptive) ---\n");
    int priorit[] = {0, 1, 2};
    Pri(processes, n, bt, wt, tat, priorit);
    return 0;
}
