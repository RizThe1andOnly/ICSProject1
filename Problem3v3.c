#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
    THIS ONE IS GARBAGE. THE PROPER ONE IS Problem3v2.c.
*/


const A = 2, B = 4, C = 6, D = 10;

typedef struct tree_node
{
        struct node *children;
        unsigned num_children;
        char name[6];
        pid_t pid;
} node;

int main(){
    //create node A
    node *A = (node*)malloc(sizeof(node));
    A->children = 2;
    strcpy(A->name,"nodeA");

    //create nodes B and C
    //here i=0 will be to create B and i=1 will be to create C
    node  *bandc[2];
    char nameofnode[6] = "";
    for(int i=0;i<2;i++){
        int numofchildren = (i==0) ? 1:0;
        if(i==0) {
            strcpy(nameofnode,"nodeB");
        }
        else {
            strcpy(nameofnode,"nodeC");
        }
        node *tempNode = (node*)malloc(sizeof(node));
        tempNode->children = numofchildren;
        strcpy(tempNode->name,nameofnode);
        tempNode->children = NULL;
        bandc[i] = tempNode;
    }
    
    A->children = bandc;
    node** temp = A->children;
    node* temp2 = *(temp+1);

    temp2 -> pid = fork();
    if(temp2->pid == 0){
        strcpy(temp2->name,"hugabuga");
    }
    printf("%ld\n",(long)temp2->pid);
    printf("%s\n",temp2->name);

    
}