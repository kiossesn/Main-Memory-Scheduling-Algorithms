#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid; // process ID
	int at; // arrival time
	int bt; // burst time
    int remaining_time; // remaining time
} process;

// Print process ids in correct order after routing
// Example: 1 1 2 1 2 3
void printFinal(int sum, int quantum, int *ids){
    for (int i = 0; i < sum ; ++i){
            printf("%d\n", ids[i]);
    }
}

/*
 * Shortest Remaining Time First algorithm
 * Using a while loop increasing current time one at a time.
 * Each loop accesses all the processes and checks if it's time to execute.
 * int n: number of processes
 * int quantum: quantum (not used)
 * process *arr: array of all processes as given
 * return: array of pids
 */
int * srtf(int n, int sum, int quantum, process *arr){
    // Initialize current_time, works as a clock
    int current_time=0;
    // Initialize integer array that will take the pids of every process that is being chosen each time
    int *ids= malloc(sum *sizeof (int ));

    // Copy burst times into remaining_time of each process because no process has been chosen yet
    for(int i=0; i<n; i++){
        arr[i].remaining_time = arr[i].bt;
    }

    // Time iteration, start the clock
    while(current_time != sum){
        // Find minimum remaining time process that has arrived until current time
        int minrt=1000,index=-1;
        for(int i=0;i<n;i++){
            if(arr[i].at<=current_time && arr[i].remaining_time!=0){
                  if(arr[i].remaining_time < minrt){
                      minrt=arr[i].remaining_time;
                      index=i;
                  }
            }
        }
        // Put the chosen process id in ids array
        ids[current_time]=arr[index].pid;
        // Reduce remaining time of the chosen process by 1
        arr[index].remaining_time=arr[index].remaining_time-1;

        // Update current time by 1
        current_time=current_time + 1;
    }
    return ids;
}

int main() {

	/* read in data - DO NOT EDIT (START) */
	int n;
	int quantum;
	scanf("%d", &n);
	scanf("%d", &quantum);
	process *arr;
	arr = malloc(n * sizeof(process));
	for (int i = 0; i < n ; ++i) {
		scanf("%d", &arr[i].pid);
		scanf("%d", &arr[i].at);
		scanf("%d", &arr[i].bt);
	}
	/* read in data - DO NOT EDIT (END) */

    // Sum burst times, is used to print the array of pids
    int sum=0;
    for(int i=0; i<n; i++){
        sum=sum+arr[i].bt;
    }

    // Make int array to store the correct order of routing
    int *ids = malloc(n * sizeof(int));

    // Call srtf algorithm
    ids=srtf(n, sum, quantum, arr);

    // Print process ids in order
    printFinal(sum, quantum, ids);

	return 0; /* DO NOT EDIT THIS LINE */
}
