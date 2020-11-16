#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

void ctrlfun(int sig);
pid_t pid=-1;

int main() {
	char buf[256]; 
	char *argv[50]; 
	int narg;
	pid_t pid;
	signal(SIGINT,ctrlfun);
    signal(SIGTSTP,ctrlfun);
	while (1) { 
		printf("shell> ");
		gets(buf);
		narg = getargs(buf, argv);
		pid = fork(); 
		if (pid == 0){
			if( signal(SIGINT,ctrlfun) == SIG_ERR){
				printf("SIGINT Error\n");
				_exit(1);
			}
            execvp( argv[0], argv );
            printf( "No such file\n" );
            _exit( 0 );
        }
		else if (pid > 0)
			wait((int *) 0);
		else
			perror("fork failed");
	} 
}
int getargs(char *cmd, char **argv) {
	int narg = 0;
	while (*cmd) {
		if (*cmd == ' ' || *cmd == '\t')
			*cmd++ = '\0'; 
		else {
			argv[narg++] = cmd++;
			while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
				cmd++;
		}
	}
	argv[narg] = NULL; 
	return narg;
}
void ctrlfun(int sig){
	if(pid != 0){
		switch(sig){
			case SIGINT:
				printf("Ctrl + c SIGINT\n"); 
				break;
			case SIGQUIT:
				printf("Ctrl + z SIGTSTP\n");
				kill(0,SIGCHLD);
				break;
            case SIGCONT:
                printf("Restart rs SIGCONT\n");
                break;
            }
    }
}
