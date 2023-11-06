// compiling gcc 4b.c -pthread
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

pthread_mutex_t mutex;
sem_t wrt;
int readcount=0, nwt, nrd;

void *reader_thr(int temp){
  	printf("\nReader %d is trying to enter database for reading.",temp);
   	pthread_mutex_lock(&mutex);			// no two processes can access readcount
   	readcount++;
   	if(readcount==1)				// 1 reader present
   		sem_wait(&wrt);			// no writer can access
    	pthread_mutex_unlock(&mutex);			// readers can access readcount
 
  	printf("\n	Reader %d is now reading in database.",temp); 
   	pthread_mutex_lock(&mutex);			// no two processes can access readcount 
  	readcount--;			
  	if(readcount==0)				// no readers present 
  		sem_post(&wrt); 			// allowing writers to enter 
   	pthread_mutex_unlock(&mutex);			// free mutex to allow other threads
   	
  	printf("\n	Reader %d has left the database.\n",temp);  
  	sleep(3);
}

void *writer_thr(int temp){
 	printf("\nWriter %d is trying to enter database for modifying data.",temp);
 	sem_wait(&wrt);				// allow access to only 1 writer at a time
 	printf("\n	Writer %d is writing in database.",temp);
 	sleep(3);
 	printf("\n	Writer %d is leaving the database.\n",temp);
 	sem_post(&wrt);				// allow other writera as well
}

int main(){
	long int i;
	pthread_mutex_init(&mutex,0);			// initializing
	sem_init(&wrt,0,1);				// initializing
	pthread_t reader[100],writer[100];
	  
	printf("\n	Enter number of readers:: ");
	scanf("%d",&nrd);
	printf("\n	Enter number of writers:: ");
	scanf("%d",&nwt);
	 
	for(i=1;i<=nwt;i++){
		pthread_create(&writer[i],NULL,(void *)writer_thr,(int *)i);
	    	pthread_join(writer[i],NULL);
	}
	 
	for(i=1;i<=nrd;i++){
		pthread_create(&reader[i],NULL,(void *)reader_thr,(int *)i);
	    	pthread_join(reader[i],NULL);
	}	   
	   
	sem_destroy(&wrt);
	pthread_mutex_destroy(&mutex);

}









