#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 100

int buffer[SIZE];
int i = 0;

pthread_mutex_t mutex_variable = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *producer()
{
    int item = 1;
    while (1)
    {
        pthread_mutex_lock(&mutex_variable);
        buffer[(i) % SIZE] = item;
        printf("Producer: Produced item %d \n", item);
        item++;
        i++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex_variable);
        sleep(1);
    }
}

void *consumer()
{
    int item;
    while (1)
    {
        pthread_mutex_lock(&mutex_variable);
        if (i == 0)
        {
            pthread_cond_wait(&cond, &mutex_variable);
        }
        item = buffer[(i - 1) % SIZE];
        printf("Consumer: Consumed item %d \n", item);
        i--;
        pthread_mutex_unlock(&mutex_variable);
        sleep(1);
    }
}

int main()
{
    pthread_t producer_thread_id, consumer_thread_id;

    pthread_create(&producer_thread_id, NULL, producer, NULL);
    pthread_create(&consumer_thread_id, NULL, consumer, NULL);
    pthread_join(producer_thread_id, NULL);
    pthread_join(consumer_thread_id, NULL);
    return 0;
}