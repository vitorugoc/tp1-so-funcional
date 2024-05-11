#include "types.h"
#include "user.h"

int n;
int sleep_time = 0;
int ready_time = 0;
int turnaround_time = 0;
int process_type = -1;

#define NUM_PROCESSES 60
#define NUM_PRIORITIES 4

int
main(int argc, char* argv[])
{
    int pid, retime, rutime, stime, current_p;
    
    n = NUM_PROCESSES;
    
    for (current_p = 0; current_p < n; current_p++)
    {
        pid = fork();

        if(pid == 0)
        {
            continue;
        }
        else if (pid != 0)
        {
            int priority = (current_p % NUM_PRIORITIES) + 1;
            change_prio(priority);
            for(int i = 0; i < 100; i++){
                for(int j = 0; j < 1000000; j++) {}}
            process_type = 1;
            break;
        }else{
            exit();
        }
    }

    wait2(&retime, &rutime, &stime);

    sleep_time += stime;
    ready_time += retime;
    turnaround_time = turnaround_time + retime + rutime + stime;

    switch(process_type) {
        case 1:
            printf(1, "CPU-bound, pid: %d, ready: %d, running: %d, sleeping: %d\n", pid, retime, rutime, stime);
            break;
        case 2:
            printf(1, "CPU-S bound, pid: %d, ready: %d, running: %d, sleeping: %d\n", pid, retime, rutime, stime);
            break;
        case 3:
            printf(1, "I/O bound, pid: %d, ready: %d, running: %d, sleeping: %d\n", pid, retime, rutime, stime);
            break;
    }

    exit(); 
}