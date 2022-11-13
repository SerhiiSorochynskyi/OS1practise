#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

static pthread_key_t thread_log_key;

void write_to_log(const char* msg){
	FILE* thread_log = (FILE*) pthread_getspecific(thread_log_key);
	fprintf(thread_log, "%s\n", msg);
}

void close_thread_log(void* thread_log){
	fclose((FILE*)thread_log);
}

void * counting_func(void * args){
	srand(time(NULL));
	int id = *(int*)args;
	int max = 100;
	int num = 1+rand()%10;
	char str[100];
	char uniqueStr[] = {", num of strings and pseudo num: "};
	
	char thread_log_filename[20];
	FILE* thread_log;
	sprintf(thread_log_filename, "thread%d.log", id);
	thread_log = fopen(thread_log_filename, "w");
	pthread_setspecific(thread_log_key, thread_log);
	
	for(int i = 0; i < num; i++){
		sprintf(str, "%d%s%d %d", id, uniqueStr, num, rand()%max);
		printf("%s\n", str);
		write_to_log(str);
	}
	return NULL;
}

int makeThreads_func(int argc){
	if(argc == 1){
		printf("Please call program like: fifth 3\n");
		return 0;
	}
	int *wait;
	pthread_t thread[argc];
	pthread_key_create(&thread_log_key, close_thread_log);
	for(int i = 0; i < argc; i++){
		pthread_create(&thread[i], NULL, &counting_func, &i);
		sleep(1);
	}
	for(int i = 0; i < argc; i++)
		pthread_join(thread[i], NULL);
	return 0;
}

int main (int argc, char **argv){
	if(argc == 1){
		printf("Please call program like: first 3\n");
		return 0;
	}
	int size = atoi(argv[1]);
	makeThreads_func(size);
	return 0;
}
