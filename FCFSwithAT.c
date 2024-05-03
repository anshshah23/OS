#include <stdio.h>
#include <stdlib.h>

int main(){
    int i,p;
    printf("Enter the number of processes: ");
    scanf("%d",&p);

    int at[p],bt[p], wt[p], ct[p], tat[p];
    float avgWt = 0, avgTAT = 0;
    
    printf("Enter the the arrival time and the burst time: \n");
    for( i = 0; i < p ; i++)
    {
        printf(" P[%d]: ",i+1);
        scanf("%d %d",&at[i], &bt[i]);
    }

    printf("The AT and BT are: \n");
    for( i = 0; i < p ; i++)
    {
        printf("for P[%d]: AT[%d] & BT[%d]\n",i+1,at[i],bt[i]);
    }

    //calculate the completion time
    ct[0]=at[0]+bt[0];
    for( i = 0 ; i < p ; i++)
    {
        ct[i+1]=bt[i+1]+ct[i];
        printf("CT of P[%d] is %d \n",i+1,ct[i]);
    }
     for( i = 0 ; i < p ; i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        printf("WT[%d] and TAT[%d]\n",wt[i],tat[i]);
    }

    for( i = 0 ; i < p ; i++)
    {
        avgWt+=wt[i];
        avgTAT+=tat[i];
    }
    avgTAT/=p;
    avgWt/=p;
    printf("The average waiting time is %.1f\n",avgWt);
    printf("The average turnaround time is %.1f\n",avgTAT);
    return 0;
}