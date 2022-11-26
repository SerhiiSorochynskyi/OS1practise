#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <malloc.h>

int p = 5;
int *mass;
int *massForReaders;

pthread_rwlock_t q_lock;


void * child_func_writer(void * args){
	srand(time(NULL));
	int i = *(int*)args;
	mass[i] = 1+rand()%1000;
	return NULL;
}

void * child_func_reader(void * args){
	srand(time(NULL));
	int size = *(int*)args;
	int i = 0;
	while(i < p*2){
		if(mass[i] == 0){
			pthread_rwlock_rdlock(&q_lock);
			massForReaders[i] = mass[rand()%size];
			pthread_rwlock_unlock(&q_lock);
			
			return NULL;
		}
		i++;
	}
	return NULL;
}


void * printMass_func(void * args){
	int size = *(int*)args;
	int j;
	do{
		for(int i = 0; i < p*2; i++)
			printf("mass[%d] = %d\n", i, massForReaders[i]);
		printf("\n");
		j++;
		sleep(1);
	}while(j < p*2);
	return NULL;
}

int main (int argc, char **argv){
	pthread_rwlock_init(&q_lock, NULL);
	int massSize;
	if(argc < 2){
		printf("Please call program like: third 10\n");
		massSize = 5;
	}else{
		massSize = atoi(argv[1]);
	}
	int writerThreadsNum = p;
	int readerThreadsNum = writerThreadsNum*2;  
	int pdata0[writerThreadsNum];
	int pdata1[readerThreadsNum];
	int res0, res1;
	pthread_t writerThreads[writerThreadsNum];
	pthread_t readerThreads[readerThreadsNum];
	
	pthread_attr_t attr;
	pthread_t detached_thread;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	mass = (int*)malloc(massSize*sizeof(int));
	massForReaders = (int*)malloc(readerThreadsNum*sizeof(int));
	for(int i = 0; i < massSize; i++)
		mass[i] = 0;	
	for(int i = 0; i < readerThreadsNum; i++)
		massForReaders[i] = 0;
	
	for(int i = 0; i < writerThreadsNum; i++){
		res0 = pthread_create(&writerThreads[i], NULL, &child_func_writer, &i);
		if(res0 != 0)
			fprintf(stderr, "ERROR\n");
		pthread_join(writerThreads[i], (void *)&pdata0[i]);
	}
	
	for(int i = 0; i < readerThreadsNum; i++){
		res1 = pthread_create(&readerThreads[i], NULL, &child_func_reader, &massSize);
		if(res1 != 0)
			fprintf(stderr, "ERROR\n");
	}
	
	pthread_create(&detached_thread, &attr, &printMass_func, &massSize);
	sleep(1);
	
	pthread_attr_destroy(&attr);
	return 0;
}
