#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>

void signal_handler(int signo, siginfo_t * si, void *context) {
	if(signo == SIGUSR1){
		printf("Signal = %d\nval = %d\ncode = %d\n", signo, si->si_value.sival_int, si->si_code);
	}else if(signo == SIGTERM){
		printf("Termination!\n");
	}else{
		printf("ERROR\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int main (int argc, char *argv[]){
	if (argc < 2){
		printf("Please call program like: ./fourth 3\n");
		return 0;
	}
	int iter = atoi(argv[1]);
	pid_t p = fork();
	if (p == 0){
		union sigval value;
		for(int i = 0; i < iter; i++){
			value.sival_int = i;
			sigqueue(p, SIGUSR1, value);
		}
		sigqueue(p, SIGTERM, value);   
	}
}
