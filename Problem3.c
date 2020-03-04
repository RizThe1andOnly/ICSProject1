#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
   printf("Process A has started\n");
   pid_t pid_a,pid_b,pid_c,pid_d;
   const A = 2, B = 4, C = 6, D = 10;
   pid_a = getpid();
   if(getpid()==pid_a){
       pid_b = fork();
       pid_c = fork();
       wait();
   }
   if(getpid()==pid_b){
       pid_d = fork();
   }

}