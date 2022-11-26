#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

double x;
double a = 0;
double b = 2;
double h;
int accuracy = 1;
static double accumulating = 0;
pthread_mutex_t mutex;

struct data{
	int ai;
	int bi;	
};

double fx(double xs){
	return 4-(xs*xs);
}

void * child_func_add(void * args){
	struct data targ = *(struct data *) args;
	int i = targ.ai;
	do{
		double xs = h*(i-h/2);
		pthread_mutex_lock(&mutex);
		accumulating += h*fx(xs);
		pthread_mutex_unlock(&mutex);
		i++;
	}while(i < b/h);
	
	return NULL;
}

int main (int argc, char **argv){
	if(argc < 2){
		printf("Please call program like: second 10\n");
		return 0;
	}
	pthread_mutex_init(&mutex, NULL);
	int p = atoi(argv[1]);
	int res, pdata[p], ai, bi;
	h = (b - a)/p;
	pthread_t threads[p];
	struct data d[1000000] = {};
	for(int i = 0; i < p; i++){
		d[i].ai = a+i*h;
		d[i].bi = d[i].ai+h;
	}
	for(int i = 0; i < p; i++){
		res = pthread_create(&threads[i], NULL, &child_func_add, &d[i]);
		if(res != 0)
			fprintf(stderr, "ERROR\n");
	}
	for(int i = 0; i < p; i++){
		res = pthread_join(threads[i], (void *)&pdata[i]);
		if(res != 0)
			fprintf(stderr, "ERROR\n");
	}
	pthread_mutex_destroy(&mutex);
	printf ("RESULT: %f\n", accumulating/p);
	return 0;
}
