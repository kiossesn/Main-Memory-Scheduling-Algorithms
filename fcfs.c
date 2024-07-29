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

    // Print process ids in order.
    // Order of processes doesn't have to change because processes are given in arrival time order.
    printFinal(n, quantum, arr);

	return 0; /* DO NOT EDIT THIS LINE */
}
