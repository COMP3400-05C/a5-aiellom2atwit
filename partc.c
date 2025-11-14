#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

/**
 * @brief Creates a pipe. Parent runs parta and writes output into pipe. Child sorts by number.
 * 
 * @param argc Number of args
 * @param argv arg[1] filename
 * @return int 0 success, 1 incorrect syntax, 2 pipe creation failed, 3 fork failed, 4 exec parta failed, 5 exec sort failed
 */
int main(int argc, char* argv[]) {
    //if params are incorrect return error
    if (argc < 2 || argv[1] == NULL) {
        printf("USAGE: partc FILEIN\n");
        return 1;
    }

    char *input = argv[1];
    int fd[2];

    //create pipe
    if (pipe(fd) < 0) {
        printf("Pipe ERROR\n");
        return 2;
    }

    //create child process
    pid_t pid = fork();
    if (pid < 0) {
        printf("Fork ERROR\n");
        return 3;
    }
    //parent runs parta
    else if (pid > 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        //replace parent process with parta
        execl("./parta", "./parta", input, NULL);

        //if this line executes, execl didn't work, return error
        printf("Exec error\n");
        return 4;
    }
    //child sorts output
    else {
        //pid == 0
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        //numerically sort output, -t splits by comma, -k2 sort by numbers, -n sort numerically
        execlp("sort", "sort", "-t,", "-k2", "-n", NULL);

        //if line reached, give error
        printf("Exec sort error\n");
        return 5;
    }

    //default return case
    return 0;
}
