#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char * argv[]){
 double a = atof(argv[1]);
 double b = atof(argv[2]);
 double c = atof(argv[3]);
 double func, x;
 printf("a = %lg\nb = %lg\nc = %lg\n", a, b, c);
 printf("enter x value: ");
 scanf("%lg", &x);
 func = a*pow(x, 2)+b*x+c;
 printf("a*x^2+b*x+c = %lg\n", func);
 return 0;
}
