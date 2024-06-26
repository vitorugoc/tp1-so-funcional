#include "types.h"
#include "user.h"

int n;
int sleep_time = 0;
int ready_time = 0;
int turnaround_time = 0;
int process_type = -1;

int
main(int argc, char* argv[])
{
    int pid, retime, rutime, stime, current_p;
    

    if (argc < 1){
        exit();
    } else{
        n = 3 * atoi(argv[1]);
    }

    for (current_p = 0; current_p < n; current_p++)
    {
        pid = fork();

        if(pid == 0)
        {
            continue;
        }
        else if (pid % 3 == 0)
        {
            for(int i = 0; i < 100; i++){
                for(int j = 0; j < 1000000; j++) {}}
            process_type = 1;
            break;
        }
        else if (pid % 3 == 1)
        {
            for(int i = 0; i < 20; i++){
                for(int j = 0; j < 1000000; j++){}
                yield();
            }
            process_type = 2;
            break;
        }
        else if (pid % 3 == 2)
        {
            for(int i = 0; i < 100; i++){            
                sleep(1);}
            process_type = 3;
            break;
        }else{
            exit();
        }
        process_type = 0;
        
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