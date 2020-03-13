#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//global constants to be used by functions
const int A = 2;
const int B = 4;
const int C = 6;
const int D = 10;
const int WAIT_TIME = 20;

//const pointer to file to put output in
FILE *Q3OutputFile;

typedef struct tree_node
{
        unsigned num_children;
        char name[20];
        pid_t pid;
        struct node* children;
} node;

char getProcessName(int exitcode);

int main(){

    //initialize File pointer
    //Q3OutputFile = fopen("Q3OutputFile.txt","a"); //will use "a" to append to same file
    Q3OutputFile = stderr; // outputs to standard output console

    pid_t pid_a, pid_b, pid_c, pid_waited_for;
    int status, counter = 0;

    //create process tree structure:
    //A
    node *processA = (node*)malloc(sizeof(node));
    processA->num_children = 2;
    strcpy(processA->name,"Process A");
    processA->children = NULL;
    //B
    node *processB = (node*)malloc(sizeof(node));
    processB->num_children = 1;
    strcpy(processB->name,"Process B");
    processB->children = NULL;
    //C
    node *processC = (node*)malloc(sizeof(node));
    processC->num_children = 0;
    strcpy(processC->name,"Process C");
    processC->children = NULL;
    //D
    node *processD = (node*)malloc(sizeof(node));
    processD->num_children = 0;
    strcpy(processD->name,"Process D");
    processD->children = NULL;
    //A-> B & C
    node *bandc[2] = {processB,processC};
    processA->children = bandc;
    // B->D
    processB -> children = processD;

    //object representing this current main(root) process:
    node *rootObject = (node*)malloc(sizeof(node));
    strcpy(rootObject -> name,"Root(main) Process");
    rootObject -> pid = getpid();

    //print root info:
    fprintf(Q3OutputFile,"Main/Root process from which tree will start has PID: %ld\n",(long)(rootObject->pid));
    fflush(Q3OutputFile);

    //traverse tree and create processes:
    traverseTree(processA,&(processA->pid),rootObject);

    //wait for processes to complete:
    do
    {
        pid_waited_for = wait(&status);
        if(pid_waited_for != -1) explain_wait_status(pid_waited_for,status);
    } while (pid_waited_for != -1);

    //print tree with aux function:
    print_tree(processA);
}

/* function to traverse tree and create processes accordingly */
void traverseTree(node* root, pid_t *pidLoc, node* parent){
    if(root == NULL) return; //base case

    //select exit code:
    int exitcode;
    //printf("%s",(root->name));
    switch((root->name)[8]){
        case 'A':
            exitcode = A;
            break;
        case 'B':
            exitcode = B;
            break;
        case 'C':
            exitcode = C;
            break;
        case 'D':
            exitcode = D;
            break;
        default:
            exitcode = 9;
            break;
    }


    //create new process:
    pid_t pid = fork();

    //deal with different cases for possible cases for pid
    if(pid<0){//error in creating process
        fprintf(Q3OutputFile,"%s failed to start.\n",root->name);
        fflush(Q3OutputFile);
    }
    else if(pid == 0){//in child process

        //print start of process
        fprintf(Q3OutputFile,"%s with PID: %ld has started. From parent %s\n",(root->name),(long)getpid(),(parent->name));
        fflush(Q3OutputFile);
        sleep(20); //sleep to slow down process in order to better observe
        //has more than one child
        if(root->num_children > 1){
            node** kids = root->children;
            for(int i=0;i<(root->num_children);i++){
                node *focusnode = *(kids+i);
                traverseTree(focusnode,&(focusnode->pid),root);
            }
        }
        else if((root->num_children)==1){
            node* focusnode = root->children;
            traverseTree(focusnode,&(focusnode->pid),root);
        }
        else{//no children
            sleep(WAIT_TIME);
            exit(exitcode);
        }
    }
    else{// in parent process
        *(pidLoc) = pid;
        return;
    }

    //wait for processes to complete:
    fprintf(Q3OutputFile,"%s will wait for its children to terminate.\n",(root->name));
    fflush(Q3OutputFile);
    int status,counter = 0;
    pid_t pid_waited_for;
    do
    {
        pid_waited_for = wait(&status);
        if(pid_waited_for != -1) explain_wait_status(pid_waited_for,status);
    } while (pid_waited_for != -1);

    exit(exitcode);
}


/* 
    Auxillary function provided by instructor to determine conditions
    under which a process is terminated
*/
void explain_wait_status(pid_t pid, int status){
    if(WIFEXITED(status)){
        char processName = getProcessName(WEXITSTATUS(status));
        fprintf(Q3OutputFile,"Child Process %c with PID= %ld terminated normally, exit status = %d\n",
                processName,(long)pid,WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status)){
        fprintf(Q3OutputFile,"Child with PID = %ld was terminated by signal, signal = %d\n",
                (long)pid,WTERMSIG(status));
    }
    else if(WIFSTOPPED(status)){
        fprintf(Q3OutputFile,"Child with PID = %ld has been stopped by a signal, signo = %d\n",
                (long)pid,WSTOPSIG(status));
    }
    else{
        fprintf(Q3OutputFile,"%s: Internal error: Unhandled case, PID = %ld, status = %d\n",
                __func__, (long)pid, status);
        exit(1);
    }
    fflush(Q3OutputFile);
}

/* function to obtain Process name from exit code */
char getProcessName(int exitcode){
    
    switch(exitcode){
        case 2:
            return 'A';
        case 4:
            return 'B';
        case 6:
            return 'C';
        case 10:
            return 'D';
        default:
            return 'R';
    }

    return 'R';
}


/* Auxillary function provided by instructor to print tree. This will call
   method below to print */
void print_tree(node* root){
    fprintf(Q3OutputFile,"\n\n");
    __print_tree(root,1);
    fflush(Q3OutputFile);
}

/* Aux function to print tree, will take level and node as input and print*/
void __print_tree(node* root, int level){
    for(int i=0;i<level;i++){
        fprintf(Q3OutputFile,"\t");
    }
    fprintf(Q3OutputFile,"%s\n",root->name);
    fflush(Q3OutputFile);

    if((root->num_children) == 1){
           __print_tree(root->children,level+1);
           fflush(Q3OutputFile);
       }
    else{
        node** kids = root->children;
        for(int i=0;i<(root->num_children);i++){
            node *focusnode = *(kids+i);
            __print_tree(focusnode,level+1);
            fflush(Q3OutputFile);
        }
    }
}

