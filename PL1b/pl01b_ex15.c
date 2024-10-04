#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
    char cmd[32];
    int time_cap;
} command_t;

void execute_command(command_t cmd) {
    printf("Executing command: %s\n", cmd.cmd);
    sleep(cmd.time_cap);
    printf("Command %s completed.\n", cmd.cmd);
}

int main() {
    command_t commands[] = {
        {"command1", 5},
        {"command2", 3},
        {"command3", 10}
    };
    int num_commands = sizeof(commands) / sizeof(commands[0]);
    for (int i = 0; i < num_commands; i++) {
        command_t cmd = commands[i];
        printf("Starting command: %s\n", cmd.cmd);
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) { // child process
            execute_command(cmd);
            exit(0);
        } else { // parent process
            int status;
            int result = waitpid(pid, &status, 0);
            if (result == -1) {
                perror("waitpid failed");
                exit(1);
            } else if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                printf("Command %s completed within time limit.\n", cmd.cmd);
            } else {
                printf("The command %s did not complete in its allowed time!\n", cmd.cmd);
            }
        }
    }
    printf("All commands completed.\n");
    return 0;
}
