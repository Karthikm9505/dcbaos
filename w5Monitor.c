#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#define MAX_PORTS 3
#define TOTAL_PORTS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int open_ports = 0;

void *open_port(void *arg)
{
    int port_id = *((int *)arg);
    pthread_mutex_lock(&mutex);
    while(open_ports >= MAX_PORTS)
    {
        pthread_cond_wait(&cond, &mutex);
    }
    open_ports++;
    printf("Port %d is now OPEN\n", port_id);
    pthread_mutex_unlock(&mutex);
    sleep(2);
    pthread_mutex_lock(&mutex);
    open_ports--;
    printf("Port %d is now CLOSED\n", port_id);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t threads[TOTAL_PORTS];
    int port_ids[TOTAL_PORTS];
    for(int i = 0; i < TOTAL_PORTS; i++)
    {
        port_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, open_port, (void *)&port_ids[i]);
        sleep(1);
    }
    for(int i = 0; i < TOTAL_PORTS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
