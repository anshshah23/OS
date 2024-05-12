#include <stdio.h>

void Pri_Preemptive(int processes[], int n, int bt[], int wt[], int tat[], int priority[])
{
    int remaining_time[n];
    for (int i = 0; i < n; i++)
        remaining_time[i] = bt[i];

    int complete = 0, t = 0, min_priority = 99999, shortest = 0, finish_time;
    int check = 0;

    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((remaining_time[j] > 0) && (priority[j] < min_priority))
            {
                shortest = j;
                min_priority = priority[j];
                check = 1;
            }
        }

        if (check == 0)
        {
            t++;
            continue;
        }

        remaining_time[shortest]--;

        if (remaining_time[shortest] == 0)
        {
            complete++;
            check = 0;
            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest];
            tat[shortest] = finish_time;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
        min_priority = 99999;
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
    printf("\n--- Priority (preemptive) ---\n");
    int priority[] = {2, 1, 3};
    Pri_Preemptive(processes, n, bt, wt, tat, priority);
    return 0;
}
