#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t master_sem;
sem_t user_sem;
sem_t waiter_sem;

int *mass, massN = 0, n, min, max;

void *master_thread(void *arg) {
	while (1) {
		sleep(1);
		int num = min+rand()%max; 
		sem_wait(&user_sem);
		sem_wait(&waiter_sem);
		mass[massN] = num;
		massN++;
		sem_post(&master_sem);
		sem_post(&waiter_sem);
		printf("{master}");
		for (int i = 0; i < massN; i++)
		    printf("[%d]%d ", i, mass[i]);
		printf("\n");
	}

	return 0;
}

void *user_thread(void *arg) {
	while (1) {
		sleep(2);
		sem_wait(&master_sem);
		sem_wait(&waiter_sem);
		mass[massN] = 0;
		massN--;
		sem_post(&waiter_sem);
		sem_post(&user_sem);
		printf("{user}");
		for (int i = 0; i < massN; i++)
		    printf("[%d]%d ", i, mass[i]);
		printf("\n");
	}
	return 0;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	if (argc < 5) {
		printf("Please call program like: first 10 10 1 100\n");
		return 1;
	}
	int seconds = atoi(argv[1]);
	n = atoi(argv[2]); 
	min = atoi(argv[3]); 
	max = atoi(argv[4]);
	mass = malloc(sizeof(int) * n);
	pthread_t master, user;
	sem_init(&master_sem, 1, 0);
	sem_init(&user_sem, 1, n);
	sem_init(&waiter_sem, 1, 1);
	
	pthread_create(&master, NULL, master_thread, NULL);
	pthread_create(&user, NULL, user_thread, NULL);

	sleep(seconds);
	pthread_cancel(master);
	pthread_cancel(user);
	return 0;
}
