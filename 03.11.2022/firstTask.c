#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void * child_func(void * args){
	for(int i = 0; i < 5; i++){
		printf("Child Thread. Iteration: %d\n", i);
		sleep(1);
	}
	return NULL;
}

int main (){
	pthread_t thread;
	int res;
	res = pthread_create(&thread, NULL, &child_func, NULL);
	if(res != 0){
		fprintf(stderr, "ERROR\n");
	}
	for(int i = 0; i < 5; i++){
		printf("Main Thread. Iteration: %d\n", i);
		sleep(1);
	}
	return 0;
}
