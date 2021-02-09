#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigstop(); 
void sigcont();
void sigquit();

int main()
{ 
   int pid; 
   if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
     {
       signal(SIGCONT,sigcont);
       for(;;);
     }
     else {
        printf("\nPARENT: sending SIGSTOP to suspend the process\n\n");
        kill(pid, SIGSTOP);
		sigstop();
        sleep(5);
        printf("\nPARENT: sending SIGCONT to continue the suspended process\n\n");
        kill(pid, SIGCONT);
        sleep(5);
        printf("killing child\n\n");
        kill(pid,SIGKILL);
		sigquit();
        sleep(5);
     }
}

void sigstop()
{  
   printf("CHILD: Suspended\n");
}

void sigcont()
{  
   printf("CHILD: Resumed\n\n");
}

void sigquit()
{ 
    printf("CHILD: Terminated\n");
    exit(0);
}