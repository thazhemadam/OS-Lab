#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
        int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
        int sum, product, pid;
        ssize_t array_size;

        sum = 0;
        product = 1;
        array_size = sizeof(array)/sizeof(int);

        if ((pid = fork()) == 0)
        {
                for (int i = 0; i < array_size; i++)
                        sum += array[i];
                printf("\nThe child process has computed the sum to be: %d \n", sum);
        }

        else if (pid < 0)
                fprintf(stderr, "\nThe child process wasn't successfully created.\n");

        else
        {
                for (int i = 0; i < array_size; i++)
                        product *= array[i];
                printf("\nThe parent process has computed the product to be: %d \n", product);
        }
        
        return 0;
}