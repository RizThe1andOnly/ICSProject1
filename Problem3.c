#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
   printf("Process A has started\n");
   pid_t pid_a,pid_b,pid_c,pid_d;
   const A = 2, B = 4, C = 6, D = 10;
   int status;
   printf("Process A will create and wait for Processes B and C\n");
   pid_b = fork();
   if(pid_b<0){
       printf("Error in Process Creation\n");
   }
   else if(pid_b==0){
       printf("Process B has started\n");
       pid_d = fork();
       if(pid_d<0){
           printf("Error in creating a process\n");
       }
       else if(pid_d==0){
           printf("Process D has been created\n");
           sleep(15);
           exit(D);
       }
       else {
           printf("Process B is Waiting for Process D to finish\n");
           wait(NULL);
           printf("Process D has terminated\n");
           exit(B);
       }
   }
   else{
       pid_c = fork();
       if(pid_c<0){
           printf("Error in creating Process C\n");
       }
       else if(pid_c==0){
           printf("Process C has been created\n");
           printf("Process C will enter sleep now.\n");
           sleep(15);
           exit(C);
       }
       else{
           int stat;
           while(wait(&status)>0){
               stat = WEXITSTATUS(status);
               char processName = (stat==B) ? 'B':'C';
               printf("Process %c has terminated.\n",processName);
           }
           printf("Process A will now termniate\n");
       }
   }

   return 0;

}