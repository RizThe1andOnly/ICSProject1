#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//global constants to be used by functions
const A = 2, B = 4, C = 6, D = 10;

int main(){
    //create process A:
    pid_t pid_a, pid_b, pid_c, pid_waited_for;
    int status;

    pid_a = fork();
    if(pid_a<0){//error
        printf("Error in creating process A\n");
    }
    else if(pid_a == 0){//in process A:
        printf("Process A with PID: %ld or %ld has been created\n",(long)getpid,(long)pid_a);
        sleep(5);
        //create process B and C
        pid_b = fork();
        if(pid_b != 0) pid_c = fork();

        //deal with different cases for Processes B and C
        if((pid_b < 0) || (pid_c < 0)){ //either or both had error in creation
            if(pid_b < 0 && pid_c < 0 ){ // both less than zero -> failed to create
                printf("Processes B and C have failed to start\n");
            }
            else{
                char processName = (pid_b < 0 ) ? "B":"C";
                printf("Process %c has failed to start.\n");
            }
        }
        else if(pid_b == 0){ //in process B
            printf("Process B with PID: %ld has started.\n",(long)getpid());
            sleep(5);
            printf("Process B will now create Process D.\n");
            pid_t pid_d = fork();
            if(pid_d < 0 ){ //error in process creation
                printf("Process D has failed to start. \n");
            }
            else if(pid_d == 0){ // in process D
                printf("Process D with PID: %ld has started.\n",(long)getpid());
                sleep(10);
                exit(D);
            }
            // now in Process B, will do nothing now and exit the if statements to the wait statemetns below
        }
        else if(pid_c == 0){// in process C
            printf("Process C with PID: %ld has strated.\n",(long)getpid());
            sleep(5);
            //process C will now exit out of these if statements and go to waiting block
        }
        // process A will now exit out of if statement block to go to waiting block
    }

    //waiting block
    do
    {
        pid_waited_for = wait(&status);
        explain_wait_status(pid_waited_for,&status);
    } while ((!pid_waited_for));
    

}




/* 
    Auxillary function provided by instructor to determine conditions
    under which a process is terminated
*/
void explain_wait_status(pid_t pid, int status){
    if(WIFEXITED(status)){
        fprintf(stderr,"Child with PID= %ld terminated normally, exit status = %d\n",
                (long)pid,WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status)){
        fprintf(stderr,"Child with PID = %ld was terminated by signal, signal = %d\n",
                (long)pid,WTERMSIG(status));
    }
    else if(WIFSTOPPED(status)){
        fprintf(stderr,"Child with PID = %ld has been stopped by a signal, signo = %d\n",
                (long)pid,WSTOPSIG(status));
    }
    else{
        fprintf(stderr,"%s: Internal error: Unhandled case, PID = %ld, status = %d\n",
                __func__, (long)pid, status);
        exit(1);
    }
    fflush(stderr);
}