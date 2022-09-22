#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float f(float x){
	return exp(-abs(x))*sin(x);
}

float g(float x){
	return exp(-abs(x))*cos(x);
}

int main(){
float x;
printf("Enter integer x: ");
scanf("%f", &x);

printf("f(x) = %f\n", f(x));
printf("g(x) = %f\n", g(x));

return 0;
}
