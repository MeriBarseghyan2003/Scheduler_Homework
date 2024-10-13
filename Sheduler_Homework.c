#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

// Function to sort processes by arrival time
void sort_by_arrival(struct process p[], int n) {
    struct process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to sort processes by burst time (with arrival time tie-breaking)
void sort_by_burst(struct process p[], int n) {
    struct process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].burst_time > p[j + 1].burst_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            } else if (p[j].burst_time == p[j + 1].burst_time && p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to calculate waiting, turnaround, and response times
void calculate_times(struct process p[], int n, float *avg_wt, float *avg_tat, float *avg_rt) {
    int total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }
        p[i].waiting_time = current_time - p[i].arrival_time;
        p[i].response_time = p[i].waiting_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        current_time += p[i].burst_time;

        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
        total_response_time += p[i].response_time;
    }

    // Calculate average times
    *avg_wt = (float)total_waiting_time / n;
    *avg_tat = (float)total_turnaround_time / n;
    *avg_rt = (float)total_response_time / n;
}

// Function to display the Gantt chart and process details
void display_chart(struct process p[], int n) {
    printf("Gantt Chart:\n");
    int current_time = 0;

    // Display process execution order
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }
        printf("| P%d ", p[i].pid);
        current_time += p[i].burst_time;
    }
    printf("|\n");

    // Display the time intervals
    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }
        printf("%d\t", current_time);
        current_time += p[i].burst_time;
    }
    printf("%d\n", current_time);

    // Display process details
    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
    }
}

// Implement the FCFS algorithm
void fcfs(struct process p[], int n) {
    // Sort processes by arrival time
    sort_by_arrival(p, n);
    
    float avg_wt, avg_tat, avg_rt;
    // Calculate times for each process
    calculate_times(p, n, &avg_wt, &avg_tat, &avg_rt);
    
    // Display the Gantt chart and process details
    display_chart(p, n);

    // Display averages
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_rt);
}

// Implement the SJF algorithm (non-preemptive)
void sjf(struct process p[], int n) {
    // Sort processes by burst time, consider arrival time
    sort_by_burst(p, n);
    
    float avg_wt, avg_tat, avg_rt;
    // Calculate times for each process
    calculate_times(p, n, &avg_wt, &avg_tat, &avg_rt);
    
    // Display the Gantt chart and process details
    display_chart(p, n);

    // Display averages
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_rt);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input validation
    if (n <= 0) {
        printf("Error: Number of processes must be greater than 0.\n");
        return 1;
    }

    struct process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);

        // Input validation for arrival time and burst time
        if (p[i].arrival_time < 0 || p[i].burst_time <= 0) {
            printf("Error: Invalid arrival time or burst time.\n");
            return 1;
        }
    }

    printf("\n=== First Come First Served (FCFS) ===\n");
    fcfs(p, n);

    printf("\n=== Shortest Job First (SJF) ===\n");
    sjf(p, n);

    return 0;
}
