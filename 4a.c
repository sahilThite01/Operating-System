// compiling gcc 4a.c -pthread
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

# define size 100
sem_t full, empty;
pthread_mutex_t mutex;
int buffer[size], item, counter;

void initialise(){
	pthread_mutex_init(&mutex,NULL);
	sem_init(&full,0,0);
	sem_init(&empty,0,size);
	counter=0;
}

void insert(int item){
	buffer[counter++]=item;
}

int remove_item(){
//	x=buffer[--counter];
	return buffer[--counter];
}

void *producer(){
	int waittime=rand()%2;	
	sleep(waittime);	
	item=rand()%10;
	
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	
	printf("PRODUCER PRODUCED ITEM %d\n", item);
	insert(item);
	
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
}

void *consumer(){
	int waittime=rand()%2;	
	sleep(waittime);	
	item=rand()%10;
	
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	
	item=remove_item();
	printf("CONSUMER CONSUMED ITEM %d\n", item);
	
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
}


int main(){
	int n1,n2;
	printf("\nENTER NO OF PRODUCERS:: ");
	scanf("%d",&n1);
	printf("ENTER NO OF CONSUMERS:: ");
	scanf("%d",&n2);
	printf("\n");
	
	initialise();
	
	pthread_t tid1[size], tid2[size];
	for(int i=0; i<n1; i++){
		pthread_create(&tid1[i],NULL,producer,NULL);
	}
	for(int i=0; i<n2; i++){
		pthread_create(&tid2[i],NULL,consumer,NULL);
	}
	sleep(10);
	return 0;
}

