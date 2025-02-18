#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER 5
#define EATING 3
#define HUNGRY 2
#define THINKING 1

sem_t chopsticks[BUFFER];

typedef struct {
	int id;
	int status;
} PHILOSOPHER;

void think(PHILOSOPHER *p)
{
	printf("Philosopher %d is thinking...\n", p->id + 1);
}

void hungry(PHILOSOPHER *p)
{
	int id = p->id;
	p->status = HUNGRY;
	sem_wait(&chopsticks[id]);
	sem_wait(&chopsticks[(id + 1) % BUFFER]);
	printf("Philosopher %d is hungry...\n", id + 1);
}

void eat(PHILOSOPHER *p)
{
	int id = p->id;
	p->status = EATING;
	printf("Philosopher %d picked up chopsticks %d and %d\n", id + 1, id + 1, (id + 1) % BUFFER + 1);
	printf("Philosopher %d is eating...\n", id + 1);
}

void put_down_chopsticks(PHILOSOPHER *p)
{
	int id = p->id;
	p->status = THINKING;
	sem_post(&chopsticks[id]);
	sem_post(&chopsticks[(id + 1) % BUFFER]);
	printf("Philosopher %d put down chopsticks %d and %d\n", id + 1, id + 1, (id + 1) % BUFFER + 1);
}

void *dine(void *philosopher)
{
	PHILOSOPHER *p = (PHILOSOPHER *)philosopher;
	while (true) {
		think(p);
		sleep(2);
		hungry(p);
		eat(p);
		sleep(2);
		put_down_chopsticks(p);
	}
}

int main(void)
{
	PHILOSOPHER *philosophers = (PHILOSOPHER *)malloc(sizeof(PHILOSOPHER) * BUFFER);
	pthread_t *process = (pthread_t *)malloc(sizeof(pthread_t) * BUFFER);

	for (int i = 0; i < BUFFER; i++) {
		sem_init(&chopsticks[i], 0, 1);
		philosophers[i].id = i;
		philosophers[i].status = THINKING;
	}

	for (int i = 0; i < BUFFER; i++)
		pthread_create(&process[i], NULL, dine, (void *)&philosophers[i]);

	for (int i = 0; i < BUFFER; i++)
		pthread_join(process[i], NULL);

	free(philosophers);
	free(process);
	return 0;
}
