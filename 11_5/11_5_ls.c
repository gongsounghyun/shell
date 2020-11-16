#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
void _ls(char* pos,int depth);
int count = 0;
int main(int argc,char* argv[]){
    if(argc>2){
        perror("perror \n");
        exit(EXIT_FAILURE);
    }
    char* position;
    position = argv[1];
    _ls(position,0);
    exit(0);
}
void _ls(char* pos,int depth){
    DIR *dp; 
    struct dirent *dir;
    struct stat stat;
    if( (dp=opendir(pos)) == NULL){
        perror("open directory error..\n");
        exit(EXIT_FAILURE);
    }
    chdir(pos);
    while(dir = readdir(dp)){
        if(S_ISDIR(stat.st_mode)){ 
            if(strncmp(".",dir->d_name,1) == 0 ||
                    strncmp("..",dir->d_name,2) == 0)
                continue;
            printf("%*s%20s ",depth,"",dir->d_name);
            count+=1;
            _ls(dir->d_name,depth+4);
        }
        else
            printf("%*s%20s ",depth,"",dir->d_name);
            count+=1;
            if (count%4==0) printf("\n");
    }
    printf("\n");
    closedir(dp);
}

