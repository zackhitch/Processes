// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write
// the three messages to the parent and have the parent print out
// the messages.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 16

char *msg1 = "hello world #1";
char *msg2 = "hello world #2";
char *msg3 = "hello world #3";

int main()
{
    // Your code here
    char inbuf[MSGSIZE];
    int p[2];
    int nbytes;

    if (pipe(p) < 0)
    {
        fprintf(stderr, "pipe failed\n");
        exit(2); // 2 instead of 1 so we know if the pipe or fork failed since fork err is 1.
    }

    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Child writing to pipe:\n");
        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);
    }
    else
    {
        close(p[1]);
        printf("Parent reading from pipe:\n");
        // for (int i = 0; i < 3; i++)
        // {
        //     read(p[0], inbuf, MSGSIZE);
        //     printf("%s\n", inbuf);
        // }

        //==========
        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0)
        {
            printf("%s\n", inbuf);
        }
    }

    return 0;
}
