#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
        int a, b, i;
        unsigned long long n;

        a= 0;
        b = 1;
        n = a + b;

        printf("Enter the number of values to be generated in the Fibonacci Sequence:\t");
        scanf("%d", &i);

        pid_t pid = fork();
        if (pid == 0)
        {
                printf("\nChild process is generating the Fibonacci series.\n");
                printf("0\t%llu\t", n);
                while (i-- > 0)
                {
                        n = a + b;
                        printf("%llu\t", n);
                        a = b;
                        b = n;
                        if (i == 0)
                                printf("\nChild ends\n");
                }
        }
        else
        {
                printf("Parent is waiting for child to complete...\n");
                waitpid(pid, NULL, 0);
                printf("Parent ends\n");
        }

        return 0;
}
