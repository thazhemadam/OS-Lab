/* 
 * Compile this code as follows:
 *      gcc fork_exec_wait_subprogram.c -o subprogram
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	printf("\nEntered sub-program through the child process.");
	if(argc == 1){
                printf("\nNo arguments were explicitly passed.");
                goto exit;
        }
                                
        printf("\nArguments passed on to the sub-program are: \n");
	for (int i = 1; i < argc; i++)
	    printf("%s\t", argv[i]);
exit:
        printf("\nExiting sub-program.\n");
	return 0;
}
