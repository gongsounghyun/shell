#include<stdio.h>
#include<unistd.h>

int main(void){

    char buf[BUFSIZ];
    int bufsize;

    getcwd(buf,BUFSIZ);

    printf("%s\n",buf);

    return 0;
}
