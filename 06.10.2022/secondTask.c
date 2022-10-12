#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
 int rez = 0;
 char *filename = "standart";
 while ((rez = getopt(argc, argv, "ho:c")) != -1){
  switch (rez) {
  case 'h': 
  printf("call program with params:\nh - to get program help\no out_file_name - to set a custom output name\nc - to enter the special mode\n"); 
  return 0;
  case 'o': 
  printf("Changing output name of file to: %s\n", optarg);
  filename = optarg;
  break;
  case 'c': 
  printf("You have entered the special mode\n"); 
  break;
  case '?': 
  printf("Error found!\n"); 
  break;
  } 
  fopen(filename, "wb"); 
 }
 return 0; 
}
