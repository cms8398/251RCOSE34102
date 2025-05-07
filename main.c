#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#define MAX_PROCESSES 10

int main(void)
{  
    int num_processes;
    printf("Enter the number of processes to schedule (max %d): ", MAX_PROCESSES);
    scanf("%d", &num_processes);
    
    Process *processes = create_process(num_processes);
    for(int i = 0; i < num_processes; i++) {
        process_init(&processes[i]); //initialize each process
        printf("%dth process!\n", i+1);
        print_process(&processes[i]); // print process information
    }
    delete_processes(processes); // free the allocated memory
   
    return 0;
}