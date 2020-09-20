#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    if ((pid = fork()) == 0) {
        printf("Child process successfully created.");
        execv("./subprogram", argv);
		exit(0);
	}

    else if (pid < 0)
                fprintf(stderr, "\nThe child process wasn't successfully created.\n");
	else
		pid = wait(NULL);

	return 0;
}
