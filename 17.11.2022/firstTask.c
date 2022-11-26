#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define N 10000
long double accumulating = 0;

void * child_func_add(void * args){
	int i = *(int*)args;
	while(i > 0){
		accumulating++;
		i--;
	}
	return NULL;
}

void * child_func_sub(void * args){
	int i = *(int*)args;
	while(i > 0){
		accumulating--;
		i--;
	}
	return NULL;
}

int main (int argc, char **argv){
	int p, operations;
	if(argc < 3){
		printf("Please call program like: first 3\n");
		p = 5;
		operations = 1000;
	}else{
		p = atoi(argv[1]);
		operations = atoi(argv[2]);
	}
	
	int res0, res1, pdata0[p], pdata1[p];
	pthread_t threads_add[p];
	pthread_t threads_sub[p];
	
	for(int i = 0; i < p; i++){
		res0 = pthread_create(&threads_add[i], NULL, &child_func_add, &operations);
		if(res0 != 0)
			fprintf(stderr, "ERROR\n");
		res1 = pthread_create(&threads_sub[i], NULL, &child_func_sub, &operations);
		if(res1 != 0)
			fprintf(stderr, "ERROR\n");
	}
	
	for(int i = 0; i < p; i++){
		res0 = pthread_join(threads_add[i], (void *)&pdata0[i]);
		res1 = pthread_join(threads_sub[i], (void *)&pdata1[i]);
		}
	
	printf("RESULT: %Lg\n", accumulating);
	return 0;
}
