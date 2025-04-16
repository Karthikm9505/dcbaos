#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_ITEMS 10

int buffer[MAX_ITEMS];
int in = 0, out = 0;
int n;
int items[MAX_ITEMS];
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *arg) 
{
    for (int i = 0; i < n; i++) 
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = items[i]; 
        in = (in + 1) % MAX_ITEMS;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg) 
{
    for (int i = 0; i < n; i++) 
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        out = (out + 1) % MAX_ITEMS;
        printf("consumed item=%d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() 
{
    printf("Enter the value of n  ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_ITEMS)
    {
        printf("Invalid value of n. It should be between 1 and %d\n", MAX_ITEMS);
        return 1;
    }
    for (int i = 0; i < n; i++) 
    {
        printf("Enter the item ");
        scanf("%d", &items[i]);
    }
    pthread_t producer_thread, consumer_thread;
    sem_init(&empty, 0, MAX_ITEMS);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
