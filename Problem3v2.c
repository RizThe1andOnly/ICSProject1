#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//global constants to be used by functions
const A = 2, B = 4, C = 6, D = 10;

void slowProcess(int slowLevel);
void processB();
void processC();
void processD();

int main(){
    printf("Process A has started \n");
    int pid_a,pid_b,pid_c,pid_d,status;
    slowProcess(1);
    printf("Process A will now create Processes B\n");
    pid_b = fork();
    if(pid_b<0){//error
        printf("Failed To create Process B\n");
    }
    else if(pid_b>0){ // in Process A
        printf("Process A will create Process C\n");
        pid_c = fork(); //create process c
        if(pid_c<0){//error
            printf("Failed To create Process C\n");
        }
        else if(pid_c>0){// in process A
            printf("Process A will now wait for Process B and C to terminate.\n");
            int stat;
           while(wait(&status)>0){
               stat = WEXITSTATUS(status);
               char processName = (stat==B) ? 'B':'C';
               printf("Process %c has terminated.\n",processName);
           }
           printf("Process A will now termniate\n");
        }
        else{// this is process C, since here pid_c == 0
            processC();
        }
    }
    else{// this is process B, here pid_b == 0
        processB();
    }
    
}


/* method that will carry out the tasks for process B*/
void processB(){
    printf("Process B has started.\n");
    slowProcess(1);
    printf("Process B will now create Process D.\n");
    int pid_d = fork();
    if(pid_d<0){//error
        printf("Process D failed to start.\n");
    }
    else if(pid_d>0){// in process B
        printf("Process B will wait for Process D to finish.\n");
        int status;
        wait(NULL);
        exit(B);
    }
    else{// in process D
        processD();
    }
}

/* Method to carry out tasks for Process C*/
void processC(){
    printf("Process C has started.\n");
    slowProcess(1);
    printf("Process C will now enter sleep.\n");
    sleep(15);
    exit(C);
}

/* Method to carry out tasks for Process D*/
void processD(){
    printf("Process D has started.\nProcess D will now enter sleep.\n");
    sleep(15);
    exit(D);
}


/*
    Slow down execution of a process after certain events so that
    the process tree can be better observed.
 */
void slowProcess(int slowLevel){
    if(slowLevel == 1){
        // for(int i=0;i<10000;i++){
        //     continue;
        // }
        sleep(5);
    }
    else{
        for(int i=0;i<2000;i++){
            continue;
        }
    }
}