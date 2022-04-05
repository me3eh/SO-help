#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void handler(int signum){
    // printf("signal!\n");
    if(strcmp(strsignal(signum), "Interrupt") == 0){
        printf("%s kupeczka", strsignal(signum));
        exit(signum);
    }
    else
        printf("%s lkol", strsignal(signum));
}

int main(void){
    signal(SIGINT, handler);
    signal(SIGKILL, handler);
    while(1)
    {
        printf("working...\n");
        sleep(1);
    }
    return 0;
}