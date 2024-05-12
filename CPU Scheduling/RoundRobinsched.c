#include<stdio.h>  
#include<conio.h>  

int main() {
    // Initialize variables
    int i, n, sum = 0, count = 0, y, quantum, wt = 0, tat = 0;
    float avg_wt, avg_tat;
    printf("Enter the total number of processes in the system: ");
    scanf("%d", &n);
    y = n; // Assign the number of processes to variable y

    // Declare arrays to store arrival time, burst time, and temporary burst time
    int at[n], bt[n], temp[n];

    // Use a loop to enter the details of each process: Arrival time and Burst time
    for (i = 0; i < n; i++) {
        printf("\nEnter the Arrival and Burst time of Process[%d]:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
        temp[i] = bt[i]; // Store the burst time in temp array
    }

    // Accept the Time Quantum
    printf("Enter the Time Quantum for the process: ");
    scanf("%d", &quantum);

    // Display the process No., burst time, Turn Around Time, and the waiting time
    printf("\n Process No \t Burst Time \t TAT \t Waiting Time\n");

    for (sum = 0, i = 0; y != 0; ) {
        if (temp[i] <= quantum && temp[i] > 0) {  
            sum += temp[i];  
            temp[i] = 0;  
            count = 1;  
        } else if (temp[i] > 0) {  
            temp[i] -= quantum;  
            sum += quantum;    
        }  
        if (temp[i] == 0 && count == 1) {  
            y--; // Decrement the process number  
            printf("P[%d] \t\t %d \t\t %d \t\t %d\n", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);  
            wt += sum - at[i] - bt[i];  
            tat += sum - at[i];  
            count = 0;     
        }  
        if (i == n - 1)  
            i = 0;  
        else if (at[i + 1] <= sum)  
            i++;  
        else  
            i = 0;  
    }  

    // Calculate the average waiting time and Turn Around time
    avg_wt = wt * 1.0 / n;
    avg_tat = tat * 1.0 / n;

    // Display the average waiting time and Turn Around time
    printf("\n Average Turn Around Time: \t%f", avg_wt);  
    printf("\n Average Waiting Time: \t%f", avg_tat);  

    getch(); // Wait for user input
    return 0; // Indicate successful program termination
}
