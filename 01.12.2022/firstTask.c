#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signo) {
	if(signo == SIGINT){
		printf("\nSIGINT has been captured!\n");
	}else if (signo == SIGTERM){
		printf("\nSIGTERM has been captured!\n");
	}else{
	printf("Unrecognized signal\n");
	exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int main (void) {
	if(signal(SIGINT, signal_handler) == SIG_ERR) {
		printf("ERROR FOR SIGINT\n");
		return 0;
	}
	if(signal(SIGTERM, signal_handler) == SIG_ERR) {
		printf("ERROR FOR SIGTERM\n");
		return 0;
	}
	if(signal(SIGPROF, SIG_DFL) == SIG_ERR) {
		printf("ERROR FOR SIGPROF\n");
		return 0;
	}
	if(signal(SIGHUP, SIG_IGN) == SIG_ERR) {
		printf("CAN`T IGNORE SIGHUP\n");
		return 0;
	}
	
	while(1){
		pause();
	}
	return 0;
}
