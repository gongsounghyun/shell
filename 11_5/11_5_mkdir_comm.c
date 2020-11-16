#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

int main() {
	char buf[256]; 
	char *argv[50]; 
	int narg;
	pid_t pid;
	while (1) { 
		printf("shell> ");
		gets(buf);
		narg = getargs(buf, argv);
		pid = fork(); 
		if (pid == 0){
			execvp(argv[0], argv);
			if(mkdir(argv[1], 0755) == 0){
				getcwd(buf, 256);
				printf("path : %s\n",buf);
			}
			else{
				fprintf(stderr, "path error\n");
				exit(1);
			}
			printf("\n");
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
