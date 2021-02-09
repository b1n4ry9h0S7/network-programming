#include<stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<stdlib.h>

int main() 
{ 

     // Fork returns process id 
    // in parent process 
    pid_t child_pid = fork(); 
  
    // Parent process  
    if (child_pid > 0){ 
        printf("Zombie process started");
        sleep(10); 
    }
    // Child process 
    else        
        exit(0); 

    // Create a child process       
    int pid = fork(); 
    printf("\n");
    if (pid > 0) 
        printf("in parent process \n"); 
  
    // Note that pid is 0 in child process 
    // and negative if fork() fails 
    else if (pid == 0) 
    { 
        sleep(10); 
        printf("in child process\n"); 
    } 
    printf("\n");
    return 0; 
} 

