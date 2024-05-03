#include <stdio.h>
#include <stdlib.h>


int main(){
    int i,j,p;
    printf("Enter the number of processes: ");
    scanf("%d",&p);

    int bt[p],wt[p],tat[p];
    float avgwt=0,avgtat=0;

    printf("Enter the burst time for each process: ");
    for(i=0;i<p;i++){
        printf("P[%d]: ",i+1);
        scanf("%d",&bt[i]);
    }
    wt[0]=0;
    tat[0]=bt[0];
    for(i=1;i<p;i++){
        wt[i]=wt[i-1]+bt[i-1];
        tat[i]=wt[i]+bt[i];
    }

    for(i=0;i<p;i++){
        avgwt+=wt[i];
        avgtat+=tat[i];
    }

    avgwt/=p;
    avgtat/=p;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0;i<p;i++){
        printf("P[%d]\t%d\t\t%d\t\t%d\n",i+1,bt[i],wt[i],tat[i]);
    }

    printf("Average Waiting Time: %f\n",avgwt);
    printf("Average Turnaround Time: %f\n",avgtat);

    return 0;
}
