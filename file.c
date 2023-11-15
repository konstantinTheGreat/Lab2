#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
int main() { 
    pid_t pid;
    for (int i = 0; i<2; i++) {
        pid = fork();

        if (pid == 0) {
            if (i == 0) {
                pid = fork();
                printf("Child process %d (PID: %d) with parent (PPID: %d)\n", i + 1, getpid(), getppid());
                for (int j = 0 ; j < 3 ; j++) {
                    pid = fork();
                    if (pid == 0){
                        printf("Child process %d (PID: %d) with parent (PPID: %d)\n", j + i + 1, getpid(), getppid());
                        if (j + i + 1 == 6) {
                            int fd = open("./output.txt",O_WRONLY | O_CREAT, 0777);
                            dprintf(fd, "pid: %d\n", getpid());
                            dprintf(fd, "execl(/bin/ls,ls, -1, NULL)");
                            execl("/bin/ls","ls", "-1", NULL); 
                            close(fd);
                        } 
                    } else {
                        waitpid (pid, NULL, 0);
                    }
                }        
            }
            printf("Child process %d (PID: %d) with parent (PPID: %d)\n", i + 1, getpid(), getppid());
        } else {
            waitpid (pid, NULL, 0);
        }
    }
    return 0;
}