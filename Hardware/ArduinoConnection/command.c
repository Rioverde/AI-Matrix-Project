#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>

int main(void) {
    int ret = 0;
    pid_t f = fork();

    if(f == 0) {
        ret = execlp("chmod", "chmod", "a+rw", "/dev/ttyACM0", NULL);
    }
    ret = execlp("chmod", "chmod", "a+rw", "/dev/ttyACM1", NULL);

    return 0;
}