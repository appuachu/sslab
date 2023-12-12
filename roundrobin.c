#include <stdio.h>
#include<string.h>
struct process{
    char pname[50];
    int at,bt,wt,tt,status,left;
}p[30];
struct gantt{
    char pname[50];
    int st,ct;
}g[30];
int val,queue[100],front=-1,rear=-1,n,k,count=0,m=0;
int enqueue(int val)
{
    if(front==-1 && rear ==-1)
    {
        front=0;
        rear=0;
        queue[front]=val;
    }
    else
    {
        rear++;
        queue[rear]=val;
    }
}
int dequeue()
{
    if (front==rear)
    {       
        k=queue[front];
        front=-1;
        rear=-1;
    }
    else if(front>-1)
    {
        k=queue[front];
        front++;  
    }
    return k;
}
int main()
{
    int n,i=0,j=0,k=0,idle=0,np=0,temp=0;
    float avgwt=0.0,avgtt=0.0;
    int tq=0;char tempname[30];
    int loop=0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &tq);
    for(i=0;i<n;i++)
    {
        printf("Enter the process name: ");
        scanf("%s",&p[i].pname);
        printf("Enter arrival time: ");
        scanf("%d",&p[i].at);
        printf("Enter the burst time: ");
        scanf("%d",&p[i].bt);
        p[i].status=0;
        p[i].left=p[i].bt;
    }

     for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp =  p[i].at;
                p[i].at = p[j].at;
                p[j].at = temp;
               
                temp =  p[i].bt;
                p[i].bt = p[j].bt;
                p[j].bt = temp;
               
                strcpy(tempname,p[i].pname);
                strcpy(p[i].pname,p[j].pname);
                strcpy(p[j].pname, tempname);

                temp = p[i].left;
                p[i].left = p[j].left;
                p[j].left = temp;
            }
        }
    }
    for(i=0,np=0;np<n+count;np++)
    {
        for(j=0;j<n;j++)
        {  
            if((p[j].at<=i)&&(p[j].status==0))
            {
                enqueue(j);
                p[j].status=1;
            }
        }
        if(front>-1)
        {
            if (idle==1)
            {
                g[m].ct=i;
                m++;
            }
            k=dequeue();
            if(p[k].left<=tq)
            {
                strcpy(g[m].pname,p[k].pname); 
                     g[m].st=i;
                g[m].ct=i+p[k].left;
                p[k].left=0;
                p[k].tt = g[m].ct-p[k].at;
                p[k].wt=p[k].tt-p[k].bt;
                p[k].status=2;
                i=g[m].ct;
                idle=0;
                m++; 
            }
            else{
                strcpy(g[m].pname,p[k].pname);
                g[m].st=i;
                g[m].ct=i+tq;
                i=g[m].ct;
                p[k].left = p[k].left-tq;
               count++;
                for(j=0;j<n;j++)
                {
                    if(p[j].at<=i && p[j].status==0)
                    {
                        enqueue(j);
                        p[j].status=1;
                    }
                }
                enqueue(k);
                m++;
                }
        }
        else if(front==-1 && idle==0)
        {
            strcpy(g[m].pname,"idle");
                g[m].st=i;
                i++; idle=1;
                count++;g[m].ct=i;
                loop++;
        }
        else 
            i++;
    }
    printf("\n\nTime Quantum: %d\n",tq);
    printf("Gantt Chart \n");
    for(i=0;i<n+count;i++)
    {
        printf("|   %s   ", g[i].pname);
    }
    printf("|\n");
    printf("%d      ", g[0].st);
    for(i=0;i<n+count;i++)
    {
 	printf("%d        ", g[i].ct);
    }
    printf("\n\n");
  
    printf("Pname|Arrival time|Burst time|Turnaround time|Waiting time \n  ");
    for(m=0;m<n;m++)
    {
        printf("%s    ", p[m].pname);
        printf("%d            ", p[m].at);
        printf("%d          ", p[m].bt);
        printf("%d               ", p[m].tt);
        printf("%d \n  ", p[m].wt);
	avgtt=avgtt+p[m].tt;
	avgwt=avgwt+p[m].wt;
    }
    printf("\nAverage turnaround time: %f \n", avgtt/n);
    printf("Average waiting time: %f\n\n ", avgwt/n);
    return 0;
}
