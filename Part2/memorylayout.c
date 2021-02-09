#include <sys/resource.h>
#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 

int main() {
  struct rusage r_usage;

  fork(); 

  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage: %ld kilobytes\n",r_usage.ru_maxrss);
  return 0;
}
