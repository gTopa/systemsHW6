#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

static void sighandler(int signo){
  if (signo==SIGINT){
    int fileID = open("./msg.txt", O_WRONLY|O_APPEND);
    char msg[]="Program exited due to SIGINT\n";
    write(fileID, msg, sizeof(msg)); 
    kill(getpid(), 9);
  }else if(signo == SIGUSR1){
    printf("Parent PID: %d\n", getppid());
  }
}

int main(){
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while(1){
    printf("PID: %d\n", getpid());
    sleep(1);
  }
  return 0;
}
