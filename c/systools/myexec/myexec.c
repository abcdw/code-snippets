#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


void run_something(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        fprintf(stderr, "usage ./myexec program [some args]\n");
        exit(EXIT_FAILURE);
    }

    char **args = (char **)malloc(sizeof(char *) * (argc - 1));

    if (args == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; ++i) {
        args[i - 1] = argv[i];
    }

    execvp(argv[1], args);

    fprintf(stderr, "no such program\n");

    free(args);
}

void wait_for_child(pid_t cpid)
{
    pid_t w;
    int status;

    do {
        w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
        if (w == -1) {
            perror("waitpid failed");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("process exited, exit status is %d", WEXITSTATUS(status));
        }
    } while(!WIFEXITED(status) && !WIFSIGNALED(status));
}

int main(int argc, char *argv[])
{
    pid_t cpid;

    cpid = fork();

    if (cpid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        run_something(argc, argv);
    } else {
        wait_for_child(cpid);
    }

    return EXIT_SUCCESS;
}
