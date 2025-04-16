#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 100

int n, hungry, pos[MAX_PHILOSOPHERS];
sem_t chopstick[MAX_PHILOSOPHERS];
sem_t mutex;

void one_philosopher(int id)
{
    int left = id;
    int right = (id + 1) % n;
    sem_wait(&mutex);
    sem_wait(&chopstick[left]);
    sem_wait(&chopstick[right]);
    sem_post(&mutex);
    printf("P %d is granted to eat\n", id);
    sleep(1);
    sem_post(&chopstick[right]);
    sem_post(&chopstick[left]);
}

void two_philosophers(int id1, int id2) 
{
    printf("P %d and P %d are granted to eat\n", id1, id2);
    sleep(1); 
}

void one_at_a_time() {
    
    printf("Allow one philosopher to eat at any time\n");
    for (int i = 0; i < hungry; i++) 
    {
        one_philosopher(pos[i]);
        for (int j = 0; j < hungry; j++) 
        {
            if (j != i) 
            {
                printf("P %d is waiting ", pos[j]);
            }
        }
        printf("\n");
    }
}

void two_at_a_time() 
{
    printf("Allow two philosophers to eat at same time\n");
    int combo = 1;
    int valid_combinations = 0;
    for (int i = 0; i < hungry; i++) 
    {
        for (int j = i + 1; j < hungry; j++)
        {
            if ((pos[i] + 1) % n != pos[j] && (pos[j] + 1) % n != pos[i]) 
            {
                printf("combination %d\n", combo++);
                two_philosophers(pos[i], pos[j]);
                for (int k = 0; k < hungry; k++) 
                {
                    if (k != i && k != j) 
                    {
                        printf("P %d is waiting ", pos[k]);
                    }
                }
                printf("\n");
                valid_combinations++;
            }
        }
    }
    if (valid_combinations == 0) 
    {
        printf("No valid combinations - all philosophers are adjacent\n");
    }
}

int main() 
{
    printf("DINING PHILOSOPHER PROBLEM\n\n");
    printf("Enter the total no. of philosophers  ");
    scanf("%d", &n);
    printf("\nHow many are hungry: ");
    scanf("%d", &hungry);
    for (int i = 0; i < hungry; i++) 
    {
        printf("Enter philosopher %d position  ", i + 1);
        scanf("%d", &pos[i]);
    }
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < n; i++) 
    {
        sem_init(&chopstick[i], 0, 1);
    }
    int choice;
    do 
    {
        printf("\n1.One can eat at a time\n2.Two can eat at a time\n3.Exit\n");
        printf("\nEnter your choice ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
                one_at_a_time();
                break;
            case 2:
                two_at_a_time();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    for (int i = 0; i < n; i++) 
    {
        sem_destroy(&chopstick[i]);
    }
    sem_destroy(&mutex);
    return 0;
}
