#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define MAX_PORTS 3
#define TOTAL_PORTS 5

sem_t semaphore;

void *open_port(void *arg)
{
    int port_id = *((int *)arg);
    sem_wait(&semaphore);
    printf("Port %d is now OPEN\n", port_id);
    sleep(2);
    printf("Port %d is now CLOSED\n", port_id);
    sem_post(&semaphore);
    return NULL;
}

int main()
{
    pthread_t threads[TOTAL_PORTS];
    int port_ids[TOTAL_PORTS];
    if(sem_init(&semaphore, 0, MAX_PORTS) != 0)
    {
        perror("Semaphore initialization failed");
        return 1;
    }
    for(int i = 0; i < TOTAL_PORTS; i++)
    {
        port_ids[i] = i + 1;
        if(pthread_create(&threads[i], NULL, open_port, (void *)&port_ids[i]) != 0)
        {
            perror("Thread Creation Failed");
            return 1;
        }
    }
    for(int i = 0; i < TOTAL_PORTS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore);
    return 0;
}
