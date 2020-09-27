#include<stdio.h>

int main(void)
{
	int burst_time[20], process[20], wait_time[20], tat[20], priority[20], i, j, n, total = 0, position, temp, avg_wait_time, avg_turnaround_time;

	printf("Enter Total Number of Process:");
	scanf("%d", &n);

	printf("\nEnter Burst Time and Priority\n");
	for (i = 0; i < n; i++) {
		printf("\nP[%d]\n", i+1);
		printf("Burst Time:");
		scanf("%d", &burst_time[i]);
		printf("Priority:");
		scanf("%d", &priority[i]);
		process[i] = i+1;		   //contains process number
	}

	//sorting burst time, priority and process number in ascending order using selection sort
	for (i = 0; i < n; i++) {
		position = i;
		for (j = i + 1; j < n; j++) {
			if (priority[j] < priority[position])
				position = j;
		}

		temp = priority[i];
		priority[i] = priority[position];
		priority[position] = temp;

		temp = burst_time[i];
		burst_time[i] = burst_time[position];
		burst_time[position] = temp;

		temp = process[i];
		process[i] = process[position];
		process[position] = temp;
	}

	wait_time[0] = 0;	//waiting time for first process is zero

	//calculate waiting time
	for (i = 1; i < n; i++) {
		wait_time[i] = 0;
		for (j = 0; j < i; j++)
			wait_time[i] += burst_time[j];

		total += wait_time[i];
	}

	avg_wait_time = total/n;	  //average waiting time
	total = 0;

	printf("\nProcess\t	Burst Time	\tWaiting Time\tTurnaround Time");
	for (i = 0; i < n; i++) {
		tat[i] = burst_time[i]+wait_time[i];	 //calculate turnaround time
		total += tat[i];
		printf("\nP[%d]\t\t  %d\t\t	%d\t\t\t%d", process[i], burst_time[i], wait_time[i], tat[i]);
	}

	avg_turnaround_time = (float)total/n;	 //average turnaround time
	printf("\n\nAverage Waiting Time = %d", avg_wait_time);
	printf("\nAverage Turnaround Time = %d\n", avg_turnaround_time);

	return 0;
}
