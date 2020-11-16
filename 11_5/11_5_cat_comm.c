#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

int main(int argc, char *argv[]) {
	char buf[256]; 
	int narg;
	int i;
	pid_t pid;
	while (1) { 
		printf("shell> ");
		gets(buf);
		narg = getargs(buf, argv);
		pid = fork(); 
		if (pid == 0){
			execvp(argv[0], argv);    
    		for(i = 1; i<argc; i++){
        		FILE *f;
       			int c;
        		f = fopen(argv[i], "r");
        		if(!f){
            		perror(argv[i]);
            		exit(1);
       			}
        		while((c=fgetc(f)) != EOF){
            		if(putchar(c) < 0) exit(1);
        		}
        		fclose(f);
    		}
     		exit(0);
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
