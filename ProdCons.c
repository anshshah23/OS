#include <time.h>;
#include <stdio.h>;
#include <stdlib.h>;

int sem = 1;
int crit[20];
int front = -1;
int rear = -1;
void producer(int a, int s)
{
    if ((rear + 1) % s == front)
    {
        printf("The critical section is full.\n");
    }
    else if (front == -1)
    {
        front = 0;
        rear = 0;
        crit[front] = a;
    }
    else
    {
        rear = (rear + 1) % s;
        crit[rear] = a;
    }
}

int consumer(int s)
{
    if (front == -1)
    {
        printf("All the elements have been consumed.\n");
    }
    else if ((front + 1) % s == rear)
    {
        int p = crit[front];
        front = -1;
        rear = -1;
        return p;
    }
    else
    {
        front = (front + 1) % s;
        int p = crit[front];
        return p;
    }
}

int main()
{
    int i;
    int s;

    printf("Enter the size of the critical section:\n");
    scanf("%d", &s);

    for (i = 0; i < s; i++)
    {
        int a = rand();
        producer(a, s);
        sem--;
        printf("The value of the semaphore after the %d element produced:%d\n", i + 1, sem);
    }
    printf("\n\n");
    for (i = 0; i < s; i++)
    {
        int p = consumer(s);
        sem++;
        printf("The element consumed is:%d\n", p);
        printf("The value of the semaphore after the consumer consumes:%d\n", sem);
    }

    return 0;
}