#include<stdio.h>
#include<stdbool.h>
#define MAX_P 10
#define MAX_R 10

int main()
{
    int processes, resources;
    int allocation[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];
    int available[MAX_R];
    int work[MAX_R];
    bool finish[MAX_P] = {false};
    int safe_seq[MAX_P];
    int count = 0;
    printf("Enter no.of processes");
    scanf("%d", &processes);
    printf("Enter no.of resource classes");
    scanf("%d", &resources);
    for(int i = 0; i < resources; i++)
    {
        int total;
        printf("Enter instances of resource class %d ", i+1);
        scanf("%d", &total);
        printf("Enter free vectors of resources class %d  ", i+1);
        scanf("%d", &available[i]);
    }
    printf("Enter the current allocation matrix\n");
    for(int i = 0; i < processes; i++)
    {
        for(int j = 0; j < resources; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter the request matrix\n");
    for(int i = 0; i < processes; i++)
    {
        for(int j = 0; j < resources; j++)
        {
            scanf("%d", &need[i][j]);
        }
    }
    for(int i = 0; i < resources; i++)
    {
        work[i] = available[i];
    }
    while(count < processes)
    {
        bool found = false;
        for(int i = 0; i < processes; i++)
        {
            if(!finish[i])
            {
                int j;
                for(j = 0; j < resources; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        break;
                    }
                }
                if(j == resources)
                {
                    for(int k = 0; k < resources; k++)
                    {
                        work[i] = available[i];
                    }
                    safe_seq[count++] = i + 1;
                    finish[i] = true;
                    found = true;
                    printf("Process %d is satisfied\n", i + 1);
                    printf("a[0] = %d\n", work[0]);
                    printf("a[1] = %d\n", work[1]);
                    printf("a[2] = %d\n", work[2]);
                }
            }
        }
        if(!found)
        {
            printf("System is in unsafe state\n");
            return 0;
        }
        printf("System is in safe state\nSafe Sequence");
        for(int i = 0; i < processes; i++)
        {
            printf("%d", safe_seq[i]);
        }
        printf("\n");
    }
    return 0;
}
