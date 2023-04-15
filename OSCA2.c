#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 5

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} process;

void initialize_processes(process *processes, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        processes[i].arrival_time = rand() % 10 + 1;
        processes[i].burst_time = rand() % 10 + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
}

void print_processes(process *processes, int n) {
    printf("Processes:\n");
    printf("PID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time);
    }
}

void simulate_round_robin(process *processes, int n) {
    int time = 0;
    int completed = 0;
    int current_process = 0;
    int remaining_time_quantum = TIME_QUANTUM;
    while (completed < n) {
        if (processes[current_process].remaining_time > 0) {
            if (processes[current_process].remaining_time <= remaining_time_quantum) {
                time += processes[current_process].remaining_time;
                remaining_time_quantum -= processes[current_process].remaining_time;
                processes[current_process].remaining_time = 0;
                completed++;
                processes[current_process].turnaround_time = time - processes[current_process].arrival_time;
                processes[current_process].waiting_time = processes[current_process].turnaround_time - processes[current_process].burst_time;
            } else {
                time += remaining_time_quantum;
                processes[current_process].remaining_time -= remaining_time_quantum;
                remaining_time_quantum = 0;
            }
        }
        current_process++;
        if (current_process == n) {
            current_process = 0;
        }
        if (remaining_time_quantum == 0) {
            remaining_time_quantum = TIME_QUANTUM;
        }
    }
}

void print_results(process *processes, int n) {
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    printf("\nResults:\n");
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    process processes[MAX_PROCESSES];
    int n = 5;
    initialize_processes(processes,n);
    print_processes(processes, n);
    simulate_round_robin(processes, n);
    print_results(processes, n);
return 0;
}
