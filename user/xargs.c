#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
    int index = 0;
    char *params[MAXARG];
    if(argc == 1){
        params[index++] = "echo";
    }else{
        for(int i = 1; i < argc; i++){
            params[index++] = argv[i];
        }
    }

    char buf[512];
    while(1){
        int i = 0;
        while(1){
            int len = read(0, &buf[i], 1);
            if(len == 0 || buf[i] == '\n'){
                if(i == 0) exit(0);
                buf[i] = 0;
                break;
            }
            i++;
        }
        params[index] = buf;
        if(fork() == 0){ // child
            exec(params[0], params);
            exit(0);
        }else{ // parent
            wait(0);
        }
    }
    
    exit(0);
}