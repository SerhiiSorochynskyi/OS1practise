#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct thread_arg{
	char * name;
	char * str;
	int j;
};

void * child_func(void * arg){
	struct thread_arg targ = *(struct thread_arg *) arg;
	for(int i = 0; i < targ.j; i++){
		printf("Thread %s. %s %d\n", targ.name, targ.str, targ.j);
	}
	return NULL;
}

int main (){
	pthread_t thread0, thread1, thread2, thread3;
	struct thread_arg targ[4] = {};
	char *names[4] = {"Name1", "Name2", "Name3", "Name4"};
	char *strs[4] = {"Str1", "Str2", "Str3", "Str4"};
	for(int i = 0; i < 4; i++){
		targ[i].name = names[i];
		targ[i].str = strs[i];
		targ[i].j = i+1;
	}
	int res;
	res = pthread_create(&thread0, NULL, &child_func, &targ[0]);
	res = pthread_create(&thread1, NULL, &child_func, &targ[1]);
	res = pthread_create(&thread2, NULL, &child_func, &targ[2]);
	res = pthread_create(&thread3, NULL, &child_func, &targ[3]);
	if(res != 0){
		fprintf(stderr, "ERROR\n");
	}
	sleep(1);
	return 0;
}
