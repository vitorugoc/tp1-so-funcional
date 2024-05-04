#include "types.h"
#include "user.h"



int
main(int argc, char *argv[])
{
	if (argc != 2){
				printf(1, "Usage: sanity [n]\n");
				exit();
 		}
	int i;
	int n;
	int j = 0;
	int k;
	int w;
	int z;
	int l;
	int retime;
	int rutime;
	int stime;
	int sum_cpu[1][3];
	int sum_cpu_bound[1][3];
	int sum_io_bound[1][3];
	int n_cpu = 0;
	int n_cpu_bound = 0;
	int n_io_bound = 0;
	for (i = 0; i < 1; i++)
		for (j = 0; j < 3; j++){
			sum_cpu[i][j] = 0;
			sum_cpu_bound[i][j] = 0;
			sum_io_bound[i][j] = 0;
		}

	n = atoi(argv[1]);
	int pid;
	for (i = 0; i < n; i++) {
		j = i % 3;
		pid = fork();
		if (pid == 0) {//child
			j = (getpid() - 4) % 3; // ensures independence from the first son's pid when gathering the results in the second part of the program
			switch(j) {
				case 0: //CPU‐bound process (CPU):
						for (z = 0; z < 100; z++){
				         for(w = 0; w < 1000000; w++){} 
						}
					break;
				case 1: //short tasks based CPU‐bound process (S‐CPU):
					for (k = 0; k < 20; k++){
						for (l = 0; l < 1000000; j++){}
						yield();
					}
					break;
				case 2:// simulate I/O bound process (IO)
					for(k = 0; k < 100; k++){
						sleep(1);
					}
					break;
			}
			exit(); // children exit here
		}
		continue; // father continues to spawn the next child
	}
	for (i = 0; i < n; i++) {
		pid = wait2(&retime, &rutime, &stime);
		int res = (pid - 4) % 3; // correlates to j in the dispatching loop
		switch(res) {
			case 0: // CPU bound processes
				n_cpu++;
				printf(1, "CPU-bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
				sum_cpu[0][0] += retime;
				sum_cpu[0][1] += rutime;
				sum_cpu[0][2] += stime;
				break;
			case 1: // CPU bound processes, short tasks
				n_cpu_bound++;
				printf(1, "CPU-S bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
				sum_cpu_bound[0][0] += retime;
				sum_cpu_bound[0][1] += rutime;
				sum_cpu_bound[0][2] += stime;
				break;
			case 2: // simulating I/O bound processes
				n_io_bound++;
				printf(1, "I/O bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
				sum_io_bound[0][0] += retime;
				sum_io_bound[0][1] += rutime;
				sum_io_bound[0][2] += stime;
				break;
		}
	}



	printf(1, "\n\nCPU bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sum_cpu[0][0], sum_cpu[0][1], sum_cpu[0][2], sum_cpu[0][0] + sum_cpu[0][1] + sum_cpu[0][2]);
	printf(1, "CPU-S bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sum_cpu_bound[0][0], sum_cpu_bound[0][1], sum_cpu_bound[0][2], sum_cpu_bound[0][0] + sum_cpu_bound[0][1] + sum_cpu_bound[0][2]);
	printf(1, "I/O bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sum_io_bound[0][0], sum_io_bound[0][1], sum_io_bound[0][2], sum_io_bound[0][0] + sum_io_bound[0][1] + sum_io_bound[0][2]);
	exit();
}