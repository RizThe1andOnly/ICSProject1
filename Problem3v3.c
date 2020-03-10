#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

const A = 2, B = 4, C = 6, D = 10;

typedef struct tree_node
{
        unsigned num_children;
        char name[6];
        struct node* children;
} node;

int main(){
    //create node A
    node *A = (node*)malloc(sizeof(node));
    A->children = 2;
    strcpy(A->name,"nodeA");

    //create nodes B and C
    //here i=0 will be to create B and i=1 will be to create C
    node * bandc[2];
    char nameofnode[6] = "";
    for(int i=0;i<2;i++){
        int numofchildren = (i==0) ? 1:0;
        if(i==0) {
            strcpy(nameofnode,"nodeB");
        }
        else {
            strcpy(nameofnode,"nodeC");
        }
        bandc[i] = &(node){numofchildren,nameofnode,NULL};
    }
    A->children = &bandc[0];

    for(int i=0;i<2;i++){
        printf("%s\n",((node*)A->children+i)->name);
    }
    
}