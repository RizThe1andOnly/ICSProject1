#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
   printf("Process A has started\n");
   pid_t pid_a,pid_b,pid_c,pid_d;
   const A = 2, B = 4, C = 6, D = 10;
   int status;
   printf("Process A will create and wait for Processes B and C");
   pid_b = fork();
   if(pid_b<0){
       printf("Error in Process Creation");
   }
   else if(pid_b==0){
       printf("Process B has started");
       pid_d = fork();
       if(pid_d<0){
           printf("Error in creating a process");
       }
       else if(pid_d==0){
           printf("Process D has been created");
           sleep(10);
           printf("Process D will now terminate");
           exit(D);
       }
       else {
           printf("Waiting for Process D to finish");
           wait(NULL);
           printf("Process B has now finished.");
           exit(B);
       }
   }
   else{
       pid_c = fork();
       if(pid_c<0){
           printf("Error in creating Process C");
       }
       else if(pid_c==0){
           printf("Process C has been created");
           printf("Process C will enter sleep now.");
           sleep(10);
           printf("Process C will now finish.");
           exit(C);
       }
       else{
           printf("Process A is waiting for Processes B and C to finish.");
           wait(&status);
           if(status==B){
               printf("Process A has received the termination signal from Process B");
           }
           else{
               printf("Process A has received the termination signal from Process C");
           }
           wait(&status);
           if(status==B){
               printf("Process A has received the termination signal from Process B");
           }
           else{
               printf("Process A has received the termination signal from Process C");
           }
           printf("Process A will now termniate");
       }
   }

   return 0;

}