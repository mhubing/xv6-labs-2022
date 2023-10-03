#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int* p);

int
main()
{
    int p[2];
    pipe(p);
    
    int pid = fork();
    if(pid == 0){ // child
        close(p[1]);
        prime(p);
        close(p[0]);
        exit(0);
    }else if(pid > 0){ // parent
        close(p[0]);
        for(int i = 2; i <= 35; i++){
            write(p[1], &i, sizeof(i));
        }
        close(p[1]);
        wait((int *)0);
        exit(0);
    }else{
        exit(1);
    }
}

void
prime(int* p)
{
    int p2[2];
    pipe(p2);
    int prime_num;

    if(read(p[0], &prime_num, sizeof(prime_num)) == 0){
        exit(0);
    }
    fprintf(1, "prime %d\n", prime_num);

    int pid = fork();
    if(pid == 0){ // child
        close(p2[1]);
        prime(p2);
        close(p2[0]);
        exit(0);
    }else if(pid > 0){ // parent
        int num;
        close(p[1]);
        close(p2[0]);
        while(read(p[0], &num, sizeof(num))){
            if(num % prime_num != 0){
                write(p2[1], &num, sizeof(num));
            }
        }
        close(p2[1]);
        wait((int *)0);
        exit(0);
    }else{
        exit(1);
    }
}