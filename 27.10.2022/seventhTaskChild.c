#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int IsPointInCircle(double R, double x, double y){
	if(((x-R)*(x-R) + (y-R)*(y-R)) < R*R){
		return 1;
	}else return 0;
}
 
int main(int argc, char* argv[]){
	int radius = atoi(argv[1]);
	int Npoints = atoi(argv[2]);
	int Nincircle = 0;
	srand(time(0));
	for(int i = 0; i < Npoints; i++){
		//if(IsPointInCircle(radius, (rand()%(4*Npoints)-2*Npoints)/(2.0*Npoints), (rand()%(4*Npoints) - 2*Npoints)/(2.0*Npoints)) == 1)
		if(IsPointInCircle(radius, (rand()%(radius*2)), (rand()%(radius*2))) == 1)
			Nincircle++;
	}
	exit(Nincircle);
}
 



