#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void * counting_func(void * args){
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	int i = 0;
	int delay = *(int*)args;
	while(i < delay*2){
	printf("iteration %d\n", i);
	sleep(1);
	i++;
	}
	return NULL;
}

int main (int argc, char **argv){
	if(argc == 1){
		printf("Please call program like: third 3\n");
		return 0;
	}
	pthread_t thread;
	void * wait;
	int delay = atoi(argv[1]);
	pthread_create(&thread, NULL, &counting_func, &delay);
	
	sleep(delay);
	pthread_cancel(thread);
	if(!pthread_equal(pthread_self(), thread))
		pthread_join(thread, &wait);
	if(wait == PTHREAD_CANCELED){
		printf("thread was canceled by main thread\n");
		}else 
		printf("thread was ended\n");
	return 0;
}
