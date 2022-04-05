#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
/*
* Check if a file exist using stat() function
* return 1 if the file exist otherwise return 0
*/
// int cfileexists(const char* filename){
// }
#define SHELL "/bin/sh"

int my_system(const char*command);

int main(int argc, char ** argv){
  if(argc == 2){
    my_system(argv[1]);
    return EXIT_SUCCESS;
  }
  else{
    printf("Za malo argumentow");
    return EXIT_FAILURE;
  }
}
/*
int my_system (const char *command)
{
  char path [20]= "/usr/bin/";
  strcat(path, command);
  pid_t pid;
  // printf("%p", popen(command, "r"));
  // return 1;
  printf("%d", access( command, F_OK ));
  if(access( command, F_OK ) == 0){
    printf("Nie mozna odnalezc danej aplikacji");
    return 1;
  }
  // fclose(file);
  do{
    pid = fork();
    if(pid > 0){
      execl(SHELL,SHELL, path, NULL);
      _exit (EXIT_FAILURE);
    }
    else if (pid < 0)
      exit(EXIT_FAILURE);
    sleep(20);
  }while(1);
  return 0;
}
*/
int my_system (const char *command)
{
  pid_t pid;
  do{
    pid = fork();
    if(pid > 0){
      execlp(command, command, NULL);
      printf("lklklk");
      _exit (EXIT_FAILURE);
    }
    else if (pid < 0)
      exit(EXIT_FAILURE);
    sleep(20);
  }while(1);
  return 0;
}
