#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
double pi;

void * counting_func(void * args){
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	int old_state;
	int count = 0;
	int flag;
	pi = 1.0-(1.0/3.0);
	double start = 5.0;
	for(int i = 0; i < 1000000; i++){
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);
		if(count == 1){
			pi -= (1.0/start);
			flag = 0;
		}
		if(count == 0){
			pi += (1.0/start);
			flag = 1;
		}
		pthread_setcancelstate(old_state, NULL);
		count = flag;
		start += 2.0;
		printf("current pi: %g\n", pi*4.0);
	}
	return NULL;
}

int main (int argc, char **argv){
	if(argc == 1){
		printf("Please call program like: fourth 3\n");
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
		printf("thread was ended with pi: %g\n", pi*4.0);
	return 0;
}
