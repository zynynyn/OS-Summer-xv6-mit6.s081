#include "kernel/types.h"
#include "user/user.h"


int
main(int argc, char *argv[]){
    char msg = 'm';
    int length = sizeof(msg);
    int p1[2]; //父-->子
    int p2[2]; //子-->父
    pipe(p1);
    pipe(p2);

    if(fork() == 0){
        close(p1[1]); //关闭父到子的管道写口
        close(p2[0]); //关闭子到父的管带读口
        //子进程
        if(read(p1[0], &msg, length) != length){
            printf("child read parent msg error\n");
            exit(1);
        }
        printf("%d: received ping\n", getpid());
        if(write(p2[1], &msg, length) != length){
            printf("child send msg to parent error\n");
            exit(1);
        }
        exit(0);
    }

    close(p1[0]);
    close(p2[1]);
    if(write(p1[1], &msg, length) != length){
        printf("parent send msg to child error\n");
        exit(1);
    }
    if(read(p2[0], &msg, length) != length){
        printf("parent read child msg error\n");
        exit(1);
    }
    printf("%d: received pong\n", getpid());

    exit(0);
}
