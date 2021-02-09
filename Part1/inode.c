#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
#include <dirent.h>
 
void ls(char path[], int flag) { 
    DIR *dir; 
    struct dirent *file; 
    dir = opendir(path); 
    printf("INO\t   Name \n");
    printf("-----------------\n");
    while(file=readdir(dir)) { 
        if(file->d_name[0] != '.' || flag) { 
            printf("%ld - %s  \n", file->d_ino,file->d_name); 
        } 
    } 
    free(file);  
    free(dir); 
} 
 
int main(int argc, char * argv[]) { 
    char pathname[128]; 
    getcwd(pathname, 128); 
    if(argc == 1){ 
        ls(pathname,0); 
    } 
    printf("\n"); 
    return 0; 
}