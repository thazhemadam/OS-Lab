#include <stdio.h>
#include <pthread.h>

#define BUF_SIZE 10

int buffer[BUF_SIZE];
int in, out;

void *producer()
{
    int next_produced = 1;
    while(1) {
        printf("Producer: Produced item %d\n", next_produced);
        next_produced++;
        while(((in + 1) % BUF_SIZE) == out)
        ;
        buffer[in] = next_produced;
        in = (in + 1) % BUF_SIZE;
    }
}

void *consumer()
{
    int next_consumed;
    while(1) {
        while(in == out)
        ;
        next_consumed = buffer[out];
        out = (out + 1) % BUF_SIZE;
        printf("Consumer: Consumed item %d\n", next_consumed);
    }
}

int main(void)
{
    pthread_t producer_thread_id, consumer_thread_id;
    in = 0;
    out = 0;
    pthread_create(&producer_thread_id, NULL, producer, NULL);
    pthread_create(&consumer_thread_id, NULL, consumer, NULL);
    pthread_join(producer_thread_id, NULL);
    pthread_join(consumer_thread_id, NULL);
    return 0;
}