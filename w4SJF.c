#include <stdio.h>
#include <stdbool.h>

struct Process
{
    int name;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    bool completed;
};

void sortByBurstTime(struct Process processes[], int n)
{
   
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].burst_time > processes[j + 1].burst_time) 
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process processes[], int n)
{
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;
    processes[0].completed = true;

    for (int i = 1; i < n; i++)
    {
        processes[i].waiting_time = processes[i - 1].turnaround_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        processes[i].completed = true;
    }
}

void printResults(struct Process processes[], int n)
{
    int total_waiting = 0, total_turnaround = 0;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\n",
               processes[i].name,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }
 
    printf("\nTotal waiting time  %d\n", total_waiting);
    printf("Average waiting time  %.2f\n", (float)total_waiting / n);
    printf("Total turnaround time  %d\n", total_turnaround);
    printf("Average turnaround time  %.2f\n", (float)total_turnaround / n);
}

void printGanttChart(struct Process processes[], int n)
{
    printf("\nGantt Chart \n");

    printf(" ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < processes[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    printf("|");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < processes[i].burst_time - 1; j++) printf(" ");
        printf("P%d", processes[i].name);
        for (int j = 0; j < processes[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n");


    printf(" ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < processes[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");


    printf("0");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < processes[i].burst_time; j++) printf("  ");
        printf("%d", processes[i].turnaround_time);
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter the number of processes ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter process name %d ", i);
        scanf("%d", &processes[i].name);
        printf("Enter burst time for process %d ", processes[i].name);
        scanf("%d", &processes[i].burst_time);
        processes[i].completed = false;
    }

    sortByBurstTime(processes, n);
    calculateTimes(processes, n);
    printResults(processes, n);
    printGanttChart(processes, n);

    return 0;
}
