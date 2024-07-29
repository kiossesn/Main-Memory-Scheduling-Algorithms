#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid; // process ID
	int at; // arrival time
	int bt; // burst time
} process;

// Print process ids in correct order after routing
// Example: 1 1 1 (id: 1, burst time: 3)
void printFinal(int n, int quantum, process *order){
    for (int i = 0; i < n ; ++i){
        for(int j=0; j<order[i].bt; j++){
            printf("%d\n", order[i].pid);
        }
    }
}

/*
 * Shortest Job First algorithm
 * int n: number of processes
 * int quantum: quantum
 * process *arr: array of all processes as given
 * return: the correct ordered array of processes
 */
process *  sjf(int n,int quantum, process *arr){

    // Sort the array of all processes due to burst time with bubble sort
    int temp;
    for(int i=0; i<n; i++) {
        int index=0;

        for (int j = i+1; j < n; j++) {
            // Find minimum burst time process
            if (arr[j].bt < arr[i].bt) {
                index=j;
            }
        }
        // Exchange processes
        temp=arr[i].bt;
        arr[i].bt=arr[index].bt;
        arr[index].bt=temp;

        temp=arr[i].at;
        arr[i].at=arr[index].at;
        arr[index].at=temp;

        temp=arr[i].pid;
        arr[i].pid=arr[index].pid;
        arr[index].pid=temp;
    }

    return arr;
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

    // Make process array to store the correct order of routing
    process *ids = malloc(n * sizeof(process));

    // Call sjf algorithm
    ids=sjf(n,quantum, arr);

    // Print process ids in order
    printFinal(n, quantum, ids);

	return 0; /* DO NOT EDIT THIS LINE */
}
