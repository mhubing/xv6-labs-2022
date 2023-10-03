#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[1] = "p";

int
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);

    if(fork() == 0){ // child
        if(read(p[0], buf, 1)){
            fprintf(1, "%d: received ping\n", getpid());
            close(p[0]);
            write(p[1], buf, 1);
            close(p[1]);
            exit(0);
        }
        exit(1);
    }else{ // parent
        write(p[1], buf, 1);
        close(p[1]);
        if(read(p[0], buf, 1)){
            fprintf(1, "%d: received pong\n", getpid());
            close(p[0]);
            exit(0);
        }
        exit(1);
    }
}