#include<stdio.h>
#include<pthread.h>

void * thread_sum(void * arg);
int sum = 0;
int main()
{
    pthread_t id_t1,id_t2;
    int ranger1[] = {1,5};
    int ranger2[] = {6,10};
    pthread_create(&id_t1,NULL,thread_sum,(void *) ranger1);
    pthread_create(&id_t2,NULL,thread_sum,(void *) ranger2);
    
    pthread_join(id_t1,NULL);
    pthread_join(id_t2,NULL);

    printf("result : %d \n",sum);

    return 0;
}

void * thread_sum(void *arg)
{   
    int start = ((int *)arg)[0];
    int end = ((int *)arg)[1];

    while(start <= end)
    {
        sum += start;
        start++;
    }

    return NULL;
}