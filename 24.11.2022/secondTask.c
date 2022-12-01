#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t thread_flag_mutex;
int global;
int *mass, massN = 0, n, min, max, thread_flag;

void initialize_flag(){
	pthread_mutex_init (&thread_flag_mutex, NULL);
	thread_flag = 0;
}

void set_thread_flag(int flag_value) {
	pthread_mutex_lock(&thread_flag_mutex);
	thread_flag = flag_value;
	pthread_mutex_unlock(&thread_flag_mutex);
}

void *master_thread(void *arg) {
	while (1) {
		sleep(2);
		global = min+rand()%max;  
		mass[massN] = global;
		massN++;
		set_thread_flag(1);
	}
	return 0;
}

void *user_thread(void *arg) {
	while (1) {
		int flag_is_set;
		pthread_mutex_lock(&thread_flag_mutex);
		flag_is_set = thread_flag;
		pthread_mutex_unlock(&thread_flag_mutex);
		if (flag_is_set) {
			global = 0;

			printf("{user}");
			for (int i = 0; i < massN; i++)
				printf("[%d]%d ", i, mass[i]);
			printf("\n");

			set_thread_flag(0);
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	if (argc < 5) {
		printf("Please call program like: first 10 5 1 100\n");
		return 1;
	}
	int seconds = atoi(argv[1]);
	n = atoi(argv[2]); 
	min = atoi(argv[3]); 
	max = atoi(argv[4]);
	mass = malloc(sizeof(int) * n);
	pthread_t master, user;

	initialize_flag();

	pthread_create(&master, NULL, master_thread, NULL);
	pthread_create(&user, NULL, user_thread, NULL);

	sleep(seconds);
	pthread_cancel(master);
	pthread_cancel(user);
	return 0;
}
