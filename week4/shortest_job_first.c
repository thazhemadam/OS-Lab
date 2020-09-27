#include<stdio.h>

int main(void)
{
	int burst_time[20], p[20], wait_time[20], turnaround_time[20], i, j, n, total = 0, pos, temp;
	float avg_wait_time, avg_turnaround_time;

	printf("Enter number of process:");
	scanf("%d", &n);

	printf("\nEnter Burst Time:\n");
	for (i = 0; i < n; i++) {
		printf("p%d:", i+1);
		scanf("%d", &burst_time[i]);
		p[i] = i+1;		   //contains process number
	}

	//sorting burst time in ascending order using selection sort
	for (i = 0; i < n; i++) {
		pos = i;
		for (j = i+1; j < n; j++) {
			if (burst_time[j] < burst_time[pos])
				pos = j;
		}

		temp = burst_time[i];
		burst_time[i] = burst_time[pos];
		burst_time[pos] = temp;

		temp = p[i];
		p[i] = p[pos];
		p[pos] = temp;
	}

	wait_time[0] = 0;			//waiting time for first process will be zero

	//calculate waiting time
	for (i = 1; i < n; i++)	{
		wait_time[i] = 0;
		for (j = 0; j < i; j++)
			wait_time[i] += burst_time[j];

		total += wait_time[i];
	}

	avg_wait_time = (float)total/n;	  //average waiting time
	total = 0;

	printf("\nProcess\t	Burst Time	\tWaiting Time\tTurnaround Time");
	for (i = 0; i < n; i++)	{
		turnaround_time[i] = burst_time[i]+wait_time[i];	 //calculate turnaround time
		total += turnaround_time[i];
		printf("\np%d\t\t  %d\t\t	%d\t\t\t%d", p[i], burst_time[i], wait_time[i], turnaround_time[i]);
	}

	avg_turnaround_time = (float)total/n;	 //average turnaround time
	printf("\n\nAverage Waiting Time=%f", avg_wait_time);
	printf("\nAverage Turnaround Time=%f\n", avg_turnaround_time);

	return 0;
}
