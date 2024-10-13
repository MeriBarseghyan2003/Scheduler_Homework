
# Process Scheduling Simulator

This C program simulates two process scheduling algorithms:
1. First Come First Served (FCFS)
2. Shortest Job First (SJF)

It calculates and displays:
- Waiting Time (WT)
- Turnaround Time (TAT)
- Response Time (RT)
- Average times for each algorithm

## How to Run

### Compilation
1. Save the code in `scheduler.c`.
2. Compile with:
   ```bash
   gcc -o scheduler scheduler.c
   ```
### Execution
Run the program:
```bash
./scheduler
```

### Input Format
- Enter the number of processes.
- Provide arrival time and burst time for each process.

### Output
Displays Gantt charts, process metrics (WT, TAT, RT), and average times.


