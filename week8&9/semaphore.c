#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>



pthread_t p,c;

sem_t s,full,empty;
int arr[30]={0};
int in=0;
int item = 0;


void add()
{
	
	//int item = 0;
	
	item++;
	//item=rand()%10;
	arr[in++]=item;
	printf("Produced item is %d\n",item);
}

void delete()
{	
	int item;
	
	item=arr[--in];
	
	printf("Consumed item is %d\n",item);
	
}

void *producer()
{
	int i=0;
	while(1)
	{
		sem_wait(&empty);
		sem_wait(&s);
		add();
		
		sem_post(&s);
		sleep(1);
		sem_post(&full);
		sleep(1);
	}
}

void *consumer()
{
	int i=0;
	while(1)
	{
		sem_wait(&full);
		sem_wait(&s);
		delete();
		
		sem_post(&s);
		sleep(1);
		sem_post(&empty);
		sleep(1);
	}
}

int main()
{
	printf("PRODUCER-CONSUMER!!!\n");
	sem_init(&s,0,1);
	sem_init(&empty,0,10);
	sem_init(&full, 0,0);
	
	pthread_create(&p,NULL,producer,NULL);
	pthread_create(&c,NULL,consumer,NULL);	
	
	
	pthread_join(c,NULL);
	pthread_join(p,NULL);
	printf("Exit\n");
	return 0;
}