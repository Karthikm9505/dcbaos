#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int name;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

void printGanttChart(struct Process processes[], int n)
{
    printf("\nGantt Chart \n");
    
    printf(" ");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < processes[i].burst_time; j++)
        {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < processes[i].burst_time - 1; j++)
        {
            printf(" ");
        }
        printf("P%d", processes[i].name);
        for(int j = 0; j < processes[i].burst_time - 1; j++)
        {
            printf(" ");
        }
        printf("|");
    }
    printf("\n ");
    

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < processes[i].burst_time; j++)
        {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
    

    printf("0");
    int current_time = 0;
    for(int i = 0; i < n; i++)
    {
        current_time += processes[i].burst_time;
        for(int j = 0; j < processes[i].burst_time * 2; j++)
        {
            printf(" ");
        }
        if(current_time < 10)
        {
            printf(" ");
        }
        printf("%d", current_time);
    }
    printf("\n");
}

void priorityScheduling(struct Process processes[], int n)
{
  
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(processes[j].priority > processes[j + 1].priority)
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }


    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;

    for(int i = 1; i < n; i++)
    {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }


    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].name, 
               processes[i].burst_time, 
               processes[i].priority,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }


    int total_waiting = 0, total_turnaround = 0;
    for(int i = 0; i < n; i++)
    {
        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
    }

    printf("\nTotal waiting time is %d\n", total_waiting);
    printf("Average waiting time is %.2f\n", (float)total_waiting / n);
    printf("Total Turn Around Time is %d\n", total_turnaround);
    printf("Average Turn Around time is %.2f\n", (float)total_turnaround / n);

    printGanttChart(processes, n);
}

int main()
{
    int n;
    printf("Enter the number of processes ");
    scanf("%d", &n);

    struct Process processes[n];

    for(int i = 0; i < n; i++)
    {
        printf("\nEnter the process name ");
        scanf("%d", &processes[i].name);
        printf("Enter the burst time of process %d ", processes[i].name);
        scanf("%d", &processes[i].burst_time);
        printf("Enter the priority of process %d ", processes[i].name);
        scanf("%d", &processes[i].priority);
    }

    priorityScheduling(processes, n);

    return 0;
}
