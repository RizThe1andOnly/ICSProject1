#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// don't think we need the struct
typedef struct
{
        unsigned num_children;
        char name;
        struct node* children;
} node;

int main()
{
        int i = 0;
        int f;
        printf("Proc 0%d created\n", i);

        f = fork();
        if(f < 0)
        {
                printf("Proc 0%d failed to create child\n", i);

        }
        else if(f==0)
        {
                i = 1;
                printf("Proc 0%d created\n", i);

                f = fork();
                if(f < 0)
                {
                        printf("Proc 0%d failed to create child\n", i);

                }
                else if(f==0)
                {
                        i = 2;
                        printf("Proc 0%d created\n", i);
                }
                else
                {

                }
        }
        else
        {
                f = fork();
                if(f < 0)
                {
                        printf("Proc 0%d failed to create child\n", i);

                }
                else if(f==0)
                {
                        i = 3;
                        printf("Proc 0%d created\n", i);
                }
                else
                {

                }
        }

        return i;
}
