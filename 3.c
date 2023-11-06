// SJF
#include <stdio.h>
#include <string.h>

struct Table {
	char pname[10]; 
	int arrival_time;
    	int burst_time;
    	int temp_burst;
};

int main() {
    	struct Table t[50];
    	int n, i, j, temp;
    	int st[10], wt[10], ta[10];
    	int totwt = 0, totta = 0;
    	float awt, ata;

    	printf("Enter the number of processes:: ");
    	scanf("%d", &n);
    	printf("\n");

    	for (i = 0; i < n; i++) {
        		printf("Enter Process name, Arrival time and Execution time::\n");
        		scanf("%s %d %d", t[i].pname, &t[i].arrival_time, &t[i].burst_time);
        		//t[i].burst_time = t[i].temp_burst; // Initialize burst_time
        		printf("\n");
    	}

    	// Sorting the processes based on their arrival time
    	// BUBBLE SORT
    	for (i = 0; i < n - 1; i++) {
        		for (j = 0; j < n - i - 1; j++) {
            		if (t[j].arrival_time > t[j + 1].arrival_time) {
                			struct Table temp = t[j];
                			t[j] = t[j + 1];
                			t[j + 1] = temp;
            		}
        		}
    	}
	
	// considering process 1 as the first process
    	st[0] = t[0].arrival_time;
    	wt[0] = 0;
    	ta[0] = t[0].burst_time;

    	totwt += wt[0];
    	totta += ta[0];

    	for (i = 1; i < n; i++) {
        		st[i] = st[i - 1] + t[i - 1].burst_time;
        		wt[i] = st[i] - t[i].arrival_time;			//  WT = ET - AT  or   WT = TAT - BT
        		ta[i] = wt[i] + t[i].burst_time;			// TAT = WT + BT  or   TAT = CT - AT 

        		totwt += wt[i];
        		totta += ta[i];
    	}

    	awt = (float)totwt / n;
    	ata = (float)totta / n;

    	printf("Pname\tArrival time\tBurst time\tWaiting time\tTA time");
    	for (i = 0; i < n; i++) {
        		printf("\n%s\t%5d\t\t%5d\t\t%5d\t\t%5d", t[i].pname, t[i].arrival_time, t[i].burst_time, wt[i], ta[i]);
    	}

    	printf("\n\nAverage waiting time is: %f", awt);
    	printf("\nAverage turnaround time is: %f\n", ata);

    	return 0;
}


// ROUND ROBIN
#include <stdio.h>
#include <string.h>

struct Table {
    char pname[10];
    int arrival_time;
    int burst_time;
};

int main() {
    int n, i, time = 0, quantum;
    float awt = 0, ata = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    struct Table t[n];
    int remaining_time[n];
    int waiting_time[n];
    int turnaround_time[n];

    for (i = 0; i < n; i++) {
        printf("Enter Process name, Arrival time and Burst time for Process %d: ", i + 1);
        scanf("%s %d %d", t[i].pname, &t[i].arrival_time, &t[i].burst_time);
        remaining_time[i] = t[i].burst_time;		// initialising remaining time of processes
        printf("\n");
    }

    char seq[50][50];				// queue for sequence

    int completed = 0;
    int count = 0;

    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] <= quantum) {
                    time += remaining_time[i];
                    turnaround_time[i] = time - t[i].arrival_time;
                    waiting_time[i] = turnaround_time[i] - t[i].burst_time;
                    remaining_time[i] = 0;
                    completed++;

                    strcpy(seq[count++], t[i].pname); 	// copying the process name
                    //count++;
                } else {
                    time += quantum;
                    remaining_time[i] -= quantum;
                    strcpy(seq[count++], t[i].pname); 	// copying the process name
                    //count++;
                }
            }
        }
    }

    printf("\nProcess\tArrival time\tBurst time\tWaiting time\tTurnaround time\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%5d\t\t%5d\t\t%5d\t\t%5d\n", t[i].pname, t[i].arrival_time, t[i].burst_time, waiting_time[i], turnaround_time[i]);
        awt += waiting_time[i];
        ata += turnaround_time[i];
    }

    awt /= n;
    ata /= n;

    printf("\nAverage waiting time: %.2f", awt);
    printf("\nAverage turnaround time: %.2f\n", ata);

    printf("\nExecution Sequence: ");
    for (i = 0; i < count; i++) {
        printf("%s -> ", seq[i]);
    }
    printf("DONE\n\n");

    return 0;
}






