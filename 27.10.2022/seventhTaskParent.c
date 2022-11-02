#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main (){
	double Pi = 0;
	int exitVal;
	int m;
	int n = 255;
	double radius = 0;
	double S = 0;
	printf("Enter radius, for example: 15.6\n");
	while(radius < 1.0)
		scanf("%lf", &radius);
	char str[10];
	sprintf(str, "%lf", radius);
	printf("%s\n", str);
	char *mass[] = {"", str, "255", (char *)0};	
	pid_t status;
	status = fork();
	if(status == 0)
		execv("seven2", mass);
	wait(&exitVal);
	m = WEXITSTATUS(exitVal);
	printf("Num of dots: %d\n", m);
	double monte = (double)m/(double)n;
	Pi = 4.0*monte;
	S = monte*(radius*2)*(radius*2);
	printf("S = %lf\nPi = %lf\n", S, Pi);
}
