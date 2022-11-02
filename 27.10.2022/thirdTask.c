#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
int localVar = 0;

void increaseLocalVar(){
	localVar++;
	return;
}


int main() {
	pid_t firstChild = fork();
	if(firstChild != 0)
		increaseLocalVar();
	pid_t secondChild = fork();
	if(secondChild != 0)
		increaseLocalVar();
	if(firstChild == 0 && secondChild == 0){
		pid_t secChild = fork();
		if(secChild != 0)
			increaseLocalVar();
	}
	printf("localVar: %d; localVarAddress: %p; ppid: %d; ", localVar, &localVar, getppid());
	if(firstChild != 0)
		printf("child: %d; ", firstChild);
	if(secondChild != 0)
		printf("child: %d; ", secondChild);
	printf("\n\n");
	return 0; 
}
