#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 100

int n, hungry, pos[MAX_PHILOSOPHERS];
sem_t chopstick[MAX_PHILOSOPHERS];

void* one_philosopher(void* arg)
{
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % n;

    sem_wait(&chopstick[left]);
    sem_wait(&chopstick[right]);

    printf("P %d is granted to eat\n", id);
    sleep(1);

    sem_post(&chopstick[right]);
    sem_post(&chopstick[left]);

    printf("P %d finished eating\n", id);
    return NULL;
}

void* two_philosophers(void* arg)
{
    int* pair = (int*)arg;
    int id1 = pair[0];
    int id2 = pair[1];

    int l1 = id1;
    int r1 = (id1 + 1) % n;
    int l2 = id2;
    int r2 = (id2 + 1) % n;

    // Lock all necessary chopsticks
    sem_wait(&chopstick[l1]);
    sem_wait(&chopstick[r1]);
    sem_wait(&chopstick[l2]);
    sem_wait(&chopstick[r2]);

    printf("P %d and P %d are granted to eat\n", id1, id2);
    sleep(1);

    // Release chopsticks
    sem_post(&chopstick[r2]);
    sem_post(&chopstick[l2]);
    sem_post(&chopstick[r1]);
    sem_post(&chopstick[l1]);

    printf("P %d and P %d finished eating\n", id1, id2);
    free(pair);
    return NULL;
}

void one_at_a_time()
{
    pthread_t threads[hungry];
    for (int i = 0; i < hungry; i++)
    {
        pthread_create(&threads[i], NULL, one_philosopher, &pos[i]);
        pthread_join(threads[i], NULL);

        for (int j = 0; j < hungry; j++)
        {
            if (j != i)
                printf("P %d is waiting ", pos[j]);
        }
        printf("\n");
    }
}

void two_at_a_time()
{
    pthread_t threads[hungry * (hungry - 1) / 2];
    int count = 0, combo = 1;
    int valid = 0;

    for (int i = 0; i < hungry; i++)
    {
        for (int j = i + 1; j < hungry; j++)
        {
            int a = pos[i], b = pos[j];
            if ((a + 1) % n != b && (b + 1) % n != a) // not adjacent
            {
                printf("Combination %d:\n", combo++);
                int* pair = malloc(2 * sizeof(int));
                pair[0] = a;
                pair[1] = b;
                pthread_create(&threads[count++], NULL, two_philosophers, pair);

                for (int k = 0; k < hungry; k++)
                {
                    if (k != i && k != j)
                        printf("P %d is waiting ", pos[k]);
                }
                printf("\n");
                valid = 1;
                sleep(2); // allow time for execution
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        pthread_join(threads[i], NULL);
    }

    if (!valid)
    {
        printf("No valid combinations - all philosophers are adjacent\n");
    }
}

int main()
{
    printf("DINING PHILOSOPHER PROBLEM\n\n");
    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);

    if (n <= 1 || n > MAX_PHILOSOPHERS)
    {
        printf("Invalid number of philosophers (1 < n <= %d)\n", MAX_PHILOSOPHERS);
        return 1;
    }

    printf("How many are hungry: ");
    scanf("%d", &hungry);
    if (hungry > n || hungry <= 0)
    {
        printf("Hungry philosophers should be between 1 and %d\n", n);
        return 1;
    }

    for (int i = 0; i < hungry; i++)
    {
        printf("Enter philosopher %d position (0 to %d): ", i + 1, n - 1);
        scanf("%d", &pos[i]);
        if (pos[i] < 0 || pos[i] >= n)
        {
            printf("Invalid position! Exiting.\n");
            return 1;
        }
    }

    // Initialize semaphores
    for (int i = 0; i < n; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. One can eat at a time\n");
        printf("2. Two can eat at a time (if not adjacent)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
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
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    // Clean up
    for (int i = 0; i < n; i++)
    {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}
