#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <limits.h>

typedef struct {
    int pid; // process ID
    int at; // arrival time
    int bt; // burst time
    int remaining_time;
    int start_time; // time process starts to execute
} process;

// A structure to represent a queue
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

// Print process ids in correct order after routing
// Example: 1 1 2 1 2 3
void printFinal(int sum, int quantum, int *ids){
    for (int i = 0; i < sum ; ++i){
        printf("%d\n", ids[i]);
    }
}

/*
 * Function to create a queue of given capacity.
 * It initializes size of queue as 0.
*/
struct Queue* createQueue(unsigned capacity){
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Queue is full when size becomes equal to the capacity
int isFull(struct Queue* queue){
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(struct Queue* queue){
    return (queue->size == 0);
}

/* Function to add an item to the queue (enqueue).
 * It changes rear and size
 */
void push(struct Queue* queue, int item){
    if (isFull(queue))return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    //printf("%d enqueued to queue\n", item);
}

/*
 * Function to remove an item from queue (dequeue).
 * It changes front and size
 */
int pop(struct Queue* queue){
    if (isEmpty(queue)) return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to calculate max
int max(int a, int b){
    return a>b?a:b;
}


/*
 * Round Robin algorithm
 * Using a ready queue.
 * int n: number of processes
 * int quantum: quantum
 * process *arr: array of all processes as given
 * return: array of pids
 */
int * rr(int n, process *arr, int quantum, int sum){
    // Index of the current process in cpu
    int index;
    // Array to keep track of processes that haven't been executed at all
    bool visited[100]={false};

    int current_time = 0;
    int completed = 0;

    // Ready queue
    struct Queue* queue = createQueue(100);

    // Array to store the final execution order
    int * ids= malloc(sum*sizeof (int));
    int ids_index=0;

    // Push the first process that arrived into the ready queue
    push(queue,0);
    visited[0]=true;


    while(completed!=n){
        // Pop front process to execute (current process)
        index=pop(queue);

        // If current process has not been executed yet at all
        if(arr[index].remaining_time == arr[index].bt){
            // Start time of the process is the maximum of current time and arrival time
            arr[index].start_time = max(current_time, arr[index].at);
            current_time =  arr[index].start_time;
        }

        // If current process has remaining time more that quantum time
        if(arr[index].remaining_time > quantum){
            // Execute for time = quantum time
            arr[index].remaining_time -= quantum;
            for(int i=0;i<quantum;i++){
                ids[ids_index]=arr[index].pid;
                ids_index++;
            }
            // Update current time
            current_time += quantum;
        }
        // If remaining time is less than or equal to quantum time
        else{
            // Update current time
            current_time += arr[index].remaining_time;
            // Execute for time = remaining time
            for(int i=0;i<arr[index].remaining_time;i++){
                ids[ids_index]=arr[index].pid;
                ids_index++;
            }
            arr[index].remaining_time = 0;
            // Process is completed
            completed++;
        }
        // Check which new processes needs to be pushed to ready queue
        for(int i = 1; i < n; i++) {
            if (arr[i].remaining_time > 0 && arr[i].at <= current_time && visited[i] == false) {
                push(queue, i);
                visited[i] = true;
            }
        }
        // Check if current process needs to be pushed again to ready queue
        if( arr[index].remaining_time> 0) {
            push(queue, index);
        }
        // If queue is empty, just add one process from list, whose remaining time > 0
        if(isEmpty(queue)){
            for(int i = 1; i < n; i++){
                if(arr[i].remaining_time > 0){
                    push(queue,i);
                    visited[i] = true;
                    break;
                }
            }
        }
    }
    return ids;
}

int main(){

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

    // Sum burst times, is used to print the final order of processes
    int sum=0;
    for(int i=0; i<n; i++){
        arr[i].remaining_time=arr[i].bt;
        sum=sum+arr[i].bt;
    }

    // Make int array to store the correct order of routing
    int *ids = malloc(sum * sizeof(int));
    // Call Round Robbin function
    ids=rr(n,arr,quantum,sum);
    // Print process ids in order
    printFinal(sum,quantum,ids);

    return 0;

}