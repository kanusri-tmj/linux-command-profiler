
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

#define MAX_COMMAND 256
#define MAX_ARGS 64

int main(void)
{
    char command[MAX_COMMAND];

    while (1) {
        printf("\n====================================\n");
        printf("  LINUX COMMAND EXECUTION PROFILER\n");
        printf("====================================\n");
        printf("Enter a command (or type exit): ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        if (strchr(command, '\n') == NULL && !feof(stdin)) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            printf("Error: Command is too long.\n");
            continue;
        }

        command[strcspn(command, "\n")] = '\0';

        if (command[0] == '\0') {
            printf("Error: Empty command.\n");
            continue;
        }

        if (strcmp(command, "exit") == 0) {
            printf("Exiting profiler. Goodbye!\n");
            break;
        }

        char *args[MAX_ARGS];
        int count = 0;
        char *token = strtok(command, " \t");

        while (token != NULL && count < MAX_ARGS - 1) {
            args[count++] = token;
            token = strtok(NULL, " \t");
        }
        args[count] = NULL;

        if (count == 0) {
            printf("Error: Empty command.\n");
            continue;
        }

        struct timespec start, end;
        struct rusage usage;
        int status;

        if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
            perror("clock_gettime");
            continue;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            execvp(args[0], args);
            perror("Command execution failed");
            _exit(127);
        }

        if (wait4(pid, &status, 0, &usage) == -1) {
            perror("wait4");
            continue;
        }

        if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
            perror("clock_gettime");
            continue;
        }

        double elapsed = (end.tv_sec - start.tv_sec)
                       + (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("\n========== EXECUTION REPORT ==========\n");
        printf("Command        : %s\n", args[0]);
        printf("Execution time : %.6f seconds\n", elapsed);
        printf("User CPU time  : %ld.%06ld seconds\n",
               (long)usage.ru_utime.tv_sec,
               (long)usage.ru_utime.tv_usec);
        printf("System CPU time: %ld.%06ld seconds\n",
               (long)usage.ru_stime.tv_sec,
               (long)usage.ru_stime.tv_usec);
        printf("Max memory     : %ld KB\n", usage.ru_maxrss);

        if (WIFEXITED(status))
            printf("Exit status    : %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Terminated by signal: %d\n", WTERMSIG(status));

        printf("======================================\n");
    }

    return 0;
}
