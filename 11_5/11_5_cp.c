#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char* argv[]){
    if(argc!=3){
        exit(0);
    }

    char *cmd1;
    char *cmd2;

    cmd1 = argv[1];
    cmd2 = argv[2];

    char block[BUFSIZ];
    int in, out;
    int nread;

    in = open(cmd1,O_RDONLY);
    out = open(cmd2, O_WRONLY| O_CREAT, S_IRUSR| S_IWUSR);
    nread = read(in,block,sizeof(block));
    write(out,block,nread);

    exit(0);
}

