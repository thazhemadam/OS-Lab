#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

void producer(FILE *pipe_write_end)

{

	int i = 1;

	for (i = 1; i <= 10; i++) {

		fprintf(pipe_write_end, "%d ", i);
		printf("producer: got %d\n", i);
	}

	fclose(pipe_write_end);

	exit(0);
}

void consumer(FILE *pipe_read_end)

{

	int n, k;

	while (1) {

		int n = fscanf(pipe_read_end, "%d", &k);

		if (n == 1)
			printf("consumer: got %d\n", k);

		else
			break;
	}

	fclose(pipe_read_end);

	exit(0);
}

int main()

{

	pid_t producer_id, consumer_id;

	int pd[2];

	FILE *pipe_write_end, *pipe_read_end;

	pipe(pd);

	pipe_read_end = fdopen(pd[0], "r");

	pipe_write_end = fdopen(pd[1], "w");

	producer_id = fork();

	if (producer_id == 0) {
		fclose(pipe_read_end);
		producer(pipe_write_end);
	}

	consumer_id = fork();

	if (consumer_id == 0) {
		fclose(pipe_write_end);
		consumer(pipe_read_end);
	}

	fclose(pipe_read_end);
	fclose(pipe_write_end);

	wait(NULL);
	wait(NULL);

	return 0;
}