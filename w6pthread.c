#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *mythread1(void *vargp)
{
    int i;
    printf("Thread1\n");
    for(int i = 0; i <= 10; i++)
    {
        printf("i = %d\n", i);
    }
    printf("Exit from thread\n");
    return NULL;
}

void *mythread2(void *vargp)
{
    int j;
    printf("Thread2\n");
    for(int j = 1; j <= 10; j++)
    {
        printf("j = %d\n", j);
    }
    printf("Exit from thread\n");
    return NULL;
}

int main()
{
    pthread_t tid;
    printf("before thread\n");
    pthread_create(&tid, NULL, mythread1, NULL);
    pthread_create(&tid, NULL, mythread2, NULL);
    pthread_join(tid, NULL);
    pthread_join(tid, NULL);
    exit(0);
}
