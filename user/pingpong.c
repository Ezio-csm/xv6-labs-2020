#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p0[2];
	int p1[2];
    pipe(p0);
	pipe(p1);
    if(fork() == 0){
		char ch[2];
        read(p0[1], ch, sizeof(ch));
        printf("%d: received ping\n", getpid());
        write(p1[0], ch, sizeof(ch));
    }
	else{
		char ch[2];
        write(p0[0], "6", 1);
        wait(0);
        read(p1[1], ch, sizeof(ch));
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}
