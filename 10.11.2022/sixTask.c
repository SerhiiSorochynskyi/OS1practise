#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void closeCounting(void* args){
	int arg = *(int*)args;
	fprintf(stderr, "All okay, received data: %d\n", arg);
}

void * counting_func(void * args){
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	int i = 0;
	pthread_cleanup_push(closeCounting, &i);
	while(1){
	printf("iteration %d\n", i);
	sleep(1);
	i++;
	}
	pthread_cleanup_pop(1);
	return NULL;
}

int main (int argc, char **argv){
	if(argc == 1){
		printf("Please call program like: six 3\n");
		return 0;
	}
	pthread_t thread;
	void * wait;
	int delay = atoi(argv[1]);
	pthread_create(&thread, NULL, &counting_func, NULL);
	
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
