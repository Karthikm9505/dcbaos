#include <stdio.h>
#include <stdbool.h>

struct Process
{
    int name;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void printGanttChart(struct Process processes[], int n, int sequence[], int steps, int time_quantum)
{
    printf("\nGantt Chart  \n");
    

    printf(" ");
    for(int i = 0; i < steps; i++)
    {
        printf("----");
    }
    printf("\n|");
    

    for(int i = 0; i < steps; i++)
    {
        printf(" P%d |", sequence[i]);
    }
    printf("\n ");
    

    for(int i = 0; i < steps; i++)
    {
        printf("----");
    }
    printf("\n");
    

    printf("0");
    int current_time = 0;
    for(int i = 0; i < steps; i++)
    {
        int execution_time = (processes[sequence[i]].remaining_time + time_quantum - 1) < time_quantum 
                            ? processes[sequence[i]].remaining_time 
                            : time_quantum;
        current_time += execution_time;
        printf("   %2d", current_time);
    }
    printf("\n");
}

void roundRobinScheduling(struct Process processes[], int n, int time_quantum) 
{
    int remaining_processes = n;
    int current_time = 0;
    int sequence[100];  
    int steps = 0;
    

    for(int i = 0; i < n; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
    }
    
    while(remaining_processes > 0)
    {
        for(int i = 0; i < n; i++)
        {
            if(processes[i].remaining_time > 0)
            {
                int execution_time = (processes[i].remaining_time < time_quantum) 
                                    ? processes[i].remaining_time 
                                    : time_quantum;
                

                sequence[steps++] = i;
                

                for(int j = 0; j < n; j++)
                {
                    if(j != i && processes[j].remaining_time > 0)
                    {
                        processes[j].waiting_time += execution_time;
                    }
                }
                
                processes[i].remaining_time -= execution_time;
                current_time += execution_time;
                
                if(processes[i].remaining_time == 0)
                {
                    remaining_processes--;
                    processes[i].turnaround_time = current_time;
                }
            }
        }
    }
    

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\n", 
               processes[i].name, 
               processes[i].burst_time,
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
    

    printGanttChart(processes, n, sequence, steps, time_quantum);
}

int main()
{
    int n, time_quantum;
    printf("Enter the number of processes  ");
    scanf("%d", &n);
    
    printf("Enter the time slice ");
    scanf("%d", &time_quantum);
    
    struct Process processes[n];
    
    for(int i = 0; i < n; i++)
    {
        printf("\nEnter the process name: ");
        scanf("%d", &processes[i].name);
        printf("Enter the burst time of process %d: ", processes[i].name);
        scanf("%d", &processes[i].burst_time);
    }
    
    roundRobinScheduling(processes, n, time_quantum);
    
    return 0;
}
