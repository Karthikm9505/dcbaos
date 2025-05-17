#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread1()
{
    for(int i = 0; i < 10; i++)
    {
        printf("Thread 1 is executed\n");
    }
}

void* thread2()
{
    for(int i = 0; i < 10; i++)
    {
        printf("Thread 2 is executed\n");
    }
}

int main()
{
    pthread_t t1,t2;
    pthread_create(&t1, NULL, &thread1, NULL);
    pthread_create(&t2, NULL, &thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
