#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
int main() { 
    pid_t pid; 
    for (int i = 0; i<2; i++) {
        pid = fork(); 
	
        if (pid == 0) { 
            printf("Child process %d (PID: %d) with parent (PPID: %d)\n", i + 1, getpid(), getppid());
            if (i == 0) {  
                pid = fork(); 
                if (pid == 0) { 
                	printf("Child process %d (PID: %d) with parent (PPID: %d)\n", 3, getpid(), getppid());
                	for (int j = 4; j < 7; j++) { 
                    		pid = fork();
                    		if (pid == 0){ 
                        		printf("Child process %d (PID: %d) with parent (PPID: %d)\n", j, getpid(), getppid());
                        		if (j == 5) { 
                            			int fd = open("./output.txt",O_WRONLY | O_CREAT, 0777);
                            			dprintf(fd, "pid: %d\n", getpid());
                            			dprintf(fd, "execl(/bin/ls,ls, -1, NULL)");
                            			execl("/bin/ls","ls", "-1", NULL); 
                            			close(fd);
                        		} 
                		} else {
                			wait(NULL);
                		}  
                	} 
            	} else {
            		wait(NULL);
            	} 
            }
        } else {
            wait(NULL);
        }
    }
    return 0;
}
