#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
int globalMass[1000];

void * counting_func(void * args){
	srand(time(NULL));
	int thread_num = *(int*)args;
	int pseudo = 1+rand()%10;
	sleep(thread_num);
	globalMass[thread_num] = pseudo;
	sleep(pseudo);
	return NULL;
}

void * printMass_func(void * args){
	int size = *(int*)args;
	int flag = 0;
	while(flag == 0){
		printf("\n");
		flag = 1;	
		for(int i = 0; i < size; i++){
			printf("%d\n", globalMass[i]);
			if(globalMass[i] == 0) 
				flag = 0;
		}
		sleep(1);
		printf("\n");
	}
	printf("Detached thread was ended, wait till end\n");
	return NULL;
}

int makeThreads_func(int argc){
	if(argc == 1){
		printf("Please call program like: first 3\n");
		return 0;
	}
	int *wait;
	pthread_t thread[argc];
	pthread_attr_t attr;
	pthread_t detached_thread;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&detached_thread, &attr, &printMass_func, &argc);
	for(int i = 0; i < argc; i++){
		pthread_create(&thread[i], NULL, &counting_func, &i);
		pthread_join(thread[i], (void *)&wait);
	}
	pthread_attr_destroy(&attr);
	return 0;
}

int main (int argc, char **argv){
	if(argc == 1){
		printf("Please call program like: first 3\n");
		return 0;
	}
	int size = atoi(argv[1]);
	for(int i = 0; i < 1000; i++){
		globalMass[i] = 0;
	}
	makeThreads_func(size);
	return 0;
}
