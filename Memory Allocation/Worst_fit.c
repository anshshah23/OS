#include <stdio.h>

int process[3] = {1, 2, 3};
int incoming[3] = {120,30,99};
int memory[3] = {100,150,200};
int remaining[3] = {100,150,200};
int visited[3] = {0};
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                temp = memory[j];
                memory[j] = memory[j + 1];
                memory[j + 1] = temp;
            }
        }
    }
}

void worstfit()
{
    bubbleSort(remaining,3);
    printf("P\tIncoming\tMemory Block\n");
    for (int i = 0; i < 3; i++)
    {
        printf("P%d\t%d\t", process[i], incoming[i]);
        for(int j=0;j<3;j++)
        {
            if(incoming[i]<=remaining[j])
            {
                printf("%d",memory[j]);
                printf("\n");
                remaining[j]-=incoming[i];
                bubbleSort(remaining,3);
                break;
            }
        }
    }
}

int main()
{
    
    worstfit();
    return 0;
}