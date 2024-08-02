#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2,"usage:sleep <time> \n");
    exit(1);
  }
  int sec = atoi(argv[1]);
  sleep(sec);  
  exit(0);
}

