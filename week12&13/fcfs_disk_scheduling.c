#include <stdio.h>
#include <stdlib.h>

float seek_time (int *arr, int size, int pos, int range)
{
	float time;
	for (int i = 0; i < size; i++) {
		int diff = abs(pos - arr[i]);

		if (diff > range - diff)
			diff = range - diff;

		printf("Disk head moves from %d to %d with seek %d\n", pos, arr[i], diff);
		pos = arr[i];
		time += diff;
	}

	return time;
}

int main(void)
{
	int range, size, pos;
	int *arr;

	printf("\nEnter the max range of disk: ");
	scanf("%d", &range);

	printf("\nEnter the size of queue request: ");
	scanf("%d", &size);

	arr = (int *)malloc(sizeof(int) * size);

	printf("\nEnter the queue of disk partitions to be read:\n");
	for (int i = 0; i < size; ++i)
		scanf("%d", &arr[i]);

	printf("\nEnter the initial head position: ");
	scanf("%d", &pos);

	float time = seek_time(arr, size, pos, range);

	printf("Total seek time is %d\n", (int)time);
	printf("Average seek time is %.6f\n", (float)(time / size));
	free(arr);

	return 0;
}