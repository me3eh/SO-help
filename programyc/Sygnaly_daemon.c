#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <syslog.h>

volatile bool still_run = true;

void handler(int signum){
    syslog(LOG_INFO, "Program ends");
    printf("Bye bye\n");
    still_run = false;
}
void handler123(int signum){
    syslog(LOG_INFO, "Interrupted");
}

int main(void){
    int i = 0;
    signal(SIGQUIT, handler);
    signal(SIGINT, handler123);
    openlog("My_programme", LOG_CONS, LOG_DAEMON);
    while(still_run)
    {
        printf("working...\n");
        syslog(LOG_INFO, "Hello, it's %d time", i);
        ++i;
        sleep(1);
    }
    closelog();
}