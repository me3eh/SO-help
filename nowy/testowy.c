#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
void handler(int signum){
    if(signum == 2){
        syslog(LOG_INFO, "koniec");
        printf("koniec");
        exit(EXIT_SUCCESS);
    }
    if(signum == 10)
        printf("hih69");

    if(signum == 12)
        printf("hih");
}
void handler1(int signum){
    syslog(LOG_ERR, "KUPA");
}
int main(){
signal(SIGINT, handler);
signal(SIGUSR1, handler);
signal(SIGUSR2, handler);
openlog("PROJEKT", LOG_PID|LOG_CONS, LOG_USER);
char st[200];
printf("%s",st);
syslog(LOG_ERR, "cos sie stalo");
syslog(LOG_INFO, "shared");
while(1){
    raise(SIGINT);
    break;
}
closelog();
}