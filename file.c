#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
int main() { 
    pid_t pid2, pid3;
    printf("Child process %d (PID: %d) with parent (PPID: %d)\n", 1, getpid(), getppid());
    pid2 = fork();
    
    if (pid2 == 0) {
    	pid_t pid4;
    	pid4 = fork();
    	if (pid4 == 0) {
    		pid_t pid5, pid6, pid7;
    		pid5 = fork();
    		if (pid5 == 0){
    			 printf("Child process %d (PID: %d) with parent (PPID: %d)\n", 5, getpid(), getppid());
    		} else {
    			waitpid(pid5, NULL, 0);
    			pid6 = fork();
    			if (pid6 == 0){
    				printf("Child process %d (PID: %d) with parent (PPID: %d)\n", 6, getpid(), getppid());
    			 	int fd = open("./output.txt",O_WRONLY | O_CREAT, 0777);
                         	dprintf(fd, "pid: %d\n", getpid());
                         	dprintf(fd, "execl(/bin/ls,ls, -1, NULL)");
                         	execl("/bin/ls","ls", "-1", NULL); 
                         	close(fd);
    			} else {
    				waitpid(pid6, NULL, 0);
    				pid7 = fork();
    				if (pid7 == 0){
    			 		printf("Child process %d (PID: %d) with parent (PPID: %d)\n", 7, getpid(), getppid());
    				} else {
    					waitpid(pid7, NULL, 0);
    				}
    			}
    		}
    	} else {
    		waitpid(pid4, NULL, 0);
    	}	
    } else {
   	pid3 = fork();
   	if (pid3 == 0) {
   		printf("Child process %d (PID: %d) with parent (PPID: %d)\n", 7, getpid(), getppid());
   	} else {
   		waitpid(pid3, NULL, 0);
   	}
    }
    
    return 0;
    
    
}
