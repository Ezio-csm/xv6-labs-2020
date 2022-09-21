#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAXN 35

void recu(int* p){
	int cur;
	int gen;
	if(read(p[0], &cur, sizeof(int)) == 0)return;
	printf("prime %d\n", cur);
	if(read(p[0], &gen, sizeof(int)) == 0)return;
	int zp[2];
	pipe(zp);
	int pid = fork();
	if(pid > 0){
		do{
			if(gen % cur == 0)continue;
			write(zp[1], &gen, sizeof(int));
		}while(read(p[0], &gen, sizeof(int)) > 0);
		close(zp[1]);
		close(zp[0]);
		wait(0);
	}
	else{
		close(zp[1]);
		recu(zp);
		close(zp[0]);
	}
	return;
}

int main(int argc, char* argv[]){
	int p[2];
	pipe(p);
	int pid = fork();
	if(pid > 0){
		for(int i = 2; i <= MAXN; i++)
			write(p[1], &i, sizeof(int));
		close(p[1]);
		close(p[0]);
		wait(0);
	}
	else{
		close(p[1]);
		recu(p);
		close(p[0]);
	}

	exit(0);
}
