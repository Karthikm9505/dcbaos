#include <stdio.h>
#include <stdbool.h>

void firstFit(int processSize[], int blockSize[], int m, int n)
{
    int allocation[m];
    bool occupied[n];
    for (int i = 0; i < m; i++) 
    {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) 
    {
        occupied[i] = false;
    }
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (!occupied[j] && blockSize[j] >= processSize[i]) 
            {
                allocation[i] = j;
                occupied[j] = true;
                printf("Alloc[%d]\n", processSize[i]);
                printf("Process %d of size %d is allocated in block %d of size %d\n", 
                       i, processSize[i], j, blockSize[j]);
                break;
            }
        }
        if (allocation[i] == -1) 
        {
            printf("Alloc[%d]\n", processSize[i]);
            printf("Process %d of size %d is not allocated\n", i, processSize[i]);
        }
    }
}

void bestFit(int processSize[], int blockSize[], int m, int n) 
{
    int allocation[m];
    bool occupied[n];
    for (int i = 0; i < m; i++) 
    {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) 
    {
        occupied[i] = false;
    }
    for (int i = 0; i < n-1; i++) 
    {
        for (int j = 0; j < n-i-1; j++) 
        {
            if (blockSize[j] > blockSize[j+1]) 
            {
                int temp = blockSize[j];
                blockSize[j] = blockSize[j+1];
                blockSize[j+1] = temp;
            }
        }
    }
    printf("After sorting block sizes are \n");
    for (int i = 0; i < n; i++) 
    {
        printf("Block %d:%d\n", i, blockSize[i]);
    }
    for (int i = 0; i < m; i++) 
    {
        int bestIdx = -1;
        for (int j = 0; j < n; j++) 
        {
            if (!occupied[j] && blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) 
                {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) 
        {
            allocation[i] = bestIdx;
            occupied[bestIdx] = true;
            printf("Alloc[%d]\n", processSize[i]);
            printf("Process %d of size %d is allocated in block %d of size %d\n", 
                   i, processSize[i], bestIdx, blockSize[bestIdx]);
        } 
        else 
        {
            printf("Alloc[%d]\n", processSize[i]);
            printf("Process %d of size %d is not allocated\n", i, processSize[i]);
        }
    }
}

void worstFit(int processSize[], int blockSize[], int m, int n) 
{
    int allocation[m];
    bool occupied[n];
    for (int i = 0; i < m; i++)
    {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        occupied[i] = false;
    }
    for (int i = 0; i < n-1; i++) 
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (blockSize[j] < blockSize[j+1])
            {
                int temp = blockSize[j];
                blockSize[j] = blockSize[j+1];
                blockSize[j+1] = temp;
            }
        }
    }
    printf("After sorting block sizes are \n");
    for (int i = 0; i < n; i++) 
    {
        printf("Block %d %d\n", i, blockSize[i]);
    }
    for (int i = 0; i < m; i++) 
    {
        int worstIdx = -1;
        for (int j = 0; j < n; j++)
        {
            if (!occupied[j] && blockSize[j] >= processSize[i])
            {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) 
                {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) 
        {
            allocation[i] = worstIdx;
            occupied[worstIdx] = true;
            printf("Alloc[%d]\n", processSize[i]);
            printf("Process %d of size %d is allocated in block %d of size %d\n", 
                   i, processSize[i], worstIdx, blockSize[worstIdx]);
        } 
        else 
        {
            printf("Alloc[%d]\n", processSize[i]);
            printf("Process %d of size %d is not allocated\n", i, processSize[i]);
        }
    }
}

int main() 
{
    int m, n, choice;
    printf("Enter the no of process  ");
    scanf("%d", &m);
    printf("Enter the no of blocks  ");
    scanf("%d", &n);
    int processSize[m], blockSize[n], originalBlockSize[n];
    printf("Enter the size of each process \n");
    for (int i = 0; i < m; i++) 
    {
        printf("Process %d ", i);
        scanf("%d", &processSize[i]);
    }
    printf("Enter the block sizes \n");
    for (int i = 0; i < n; i++) 
    {
        printf("Block %d ", i);
        scanf("%d", &blockSize[i]);
        originalBlockSize[i] = blockSize[i];
    }
    do 
    {
        printf("\n1.First fit 2. Best fit 3. Worst fit\n");
        printf("Enter your choice  ");
        scanf("%d", &choice);
        for (int i = 0; i < n; i++)
        {
            blockSize[i] = originalBlockSize[i];
        }
        switch (choice) 
        {
            case 1:
                printf("First Fit\n");
                firstFit(processSize, blockSize, m, n);
                break;
            case 2:
                printf("Best Fit\n");
                bestFit(processSize, blockSize, m, n);
                break;
            case 3:
                printf("Worst Fit\n");
                worstFit(processSize, blockSize, m, n);
                break;
            default:
                printf("Invalid Choice...!\n");
                break;
        }
    } while (choice >= 1 && choice <= 3);
    return 0;
}
