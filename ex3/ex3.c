// Write another program using `fork()`. The child process should print "hello";
// the parent process should print "goodbye". You should ensure that the child
// process always prints first.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // Your code here
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("HELLO (from the child process pid: %d)\n", (int)getpid());
    }
    else
    {
        int wc = waitpid(rc, NULL, 0); // (rc, NULL, WNOHANG)
        printf("GOODBYE (from the parent process pid: %d)\n", (int)getpid());
    }

    return 0;
}
