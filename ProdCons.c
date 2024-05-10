#include&lt;time.h&gt;
#include &lt;stdio.h&gt;
#include&lt;stdlib.h&gt;

int sem=1;
int crit[20];
int front=-1;
int rear=-1;
void producer(int a,int s)
{
if((rear+1)%s==front)
{
printf(&quot;The critical section is full.\n&quot;);
}
else if(front==-1)
{
front=0;
rear=0;
crit[front]=a;
}
else
{
rear=(rear+1)%s;
crit[rear]=a;

}
}

int consumer(int s)
{
if(front==-1)
{
printf(&quot;All the elements have been consumed.\n&quot;);
}
else if((front+1)%s==rear)
{
int p=crit[front];
front=-1;
rear=-1;
return p;
}
else
{
front=(front+1)%s;
int p=crit[front];
return p;
}
}

int main()
{
int i;int s;

printf(&quot;Enter the size of the critical section:\n&quot;);
scanf(&quot;%d&quot;,&amp;s);

for(i=0;i&lt;s;i++)
{
int a=rand();
producer(a,s);
sem--;
printf(&quot;The value of the semaphore after the %d element
produced:%d\n&quot;,i+1,sem);
}
printf(&quot;\n\n&quot;);
for(i=0;i&lt;s;i++)
{
int p=consumer(s);
sem++;
printf(&quot;The element consumed is:%d\n&quot;,p);
printf(&quot;The value of the semaphore after the consumer
consumes:%d\n&quot;,sem);
}

return 0;
}
