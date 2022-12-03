#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

char *str;

void handler(int signo) {
	if (signo == SIGALRM)
		printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

int main (int argc, char *argv[]){
	if (argc < 3){
		printf("Please call program like: ./second 3 string\n");
		return 0;
	}
	int sec = atoi(argv[1]);
	str = argv[2];
	pid_t p = fork();
	if (p > 0){
		if(signal(SIGALRM, handler) == SIG_ERR){
		    printf("SIGALARM ERROR\n");
		    return 0;
		}
		alarm(sec);
		while(1){
		    pause();
		}
	}
}
