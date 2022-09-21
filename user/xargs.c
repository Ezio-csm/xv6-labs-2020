#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char* argv[]){
    char ch;
    char curstr[300];
    char* nargv[MAXARG] = {0};
    memcpy(nargv, argv + 1, sizeof(char*) * (argc - 1));
    while(read(0, &ch, 1) > 0){
        char* p = curstr;
        *(p++) = ch;
        while(read(0, &ch, 1) > 0){
            if(ch == '\n'){
                *p = '\0';
                break;
            }
            *(p++) = ch;
        }
        nargv[argc - 1] = curstr;
        if(fork() == 0)
            exec(nargv[0], nargv);
        wait(0);
    }
        
    exit(0);
}