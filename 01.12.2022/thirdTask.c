#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void main_handler(int signo){
	if (signo == SIGUSR1){
		printf("main has send kill\n");
	}
	sleep(1);
}

void child_handler(int signo){
	if (signo == SIGUSR1){
		printf("child has send kill\n");
		kill(0, SIGUSR1);
	}
	sleep(1);
}

int main (){
	pid_t p = fork();
	if (p > 0){
		while(1){
		    if(signal(SIGUSR1, child_handler) == SIG_ERR){
			printf("CAN`T HANDLE SIGALRM!\n");
			return 0;
		    }
		}
	}else{
		while(1){
			if(signal(SIGUSR1, main_handler) == SIG_ERR) {
				printf("CAN`T HANDLE SIGALRM!\n");
				return 0;
			}
			kill(p, SIGUSR1);
		}    
	}
	return 0;
}
