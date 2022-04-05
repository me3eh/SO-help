#ifndef _fun_h

#define _fun_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>

// typedef struct task{
//     long hours;
//     long minutes;
//     char program[40];
//     long state;
//     long time_to_exec;
//     long time_to_sleep_before_exec;
// }task;

typedef struct task_temp{
    long hours;
    long minutes;

    //zadania podzielone na potoki
    char ***program;

    //ile argumentow w jednym zadaniu (ile oddzieleń spacjami)
    int *how_many_arguments_in_program;

    //oryginalna komenda wywołana z pliku taskfile
    char * original_command_from_file;
    long state;
    long time_to_exec;
    long time_to_sleep_before_exec;
    
    //ile potoków
    int no_pipes;
}task_temp;

int amount_of_arguments(int arg, char*word);

FILE* checking_file_valid(char * naming);

//nie jest uzywana samodzielnie. Jest czescia funkcji get_array_of_tasks
//zwracana dlugosc pliku
int check_format(FILE * file);

bool equal_namings(char* naming_input, char* naming_output);

//zwraca globalna zmienna lines_in_file, ustalana w get_array_of_tasks
int length_of_file();


task_temp * get_array_of_tasks(FILE * file);

//nie jest uzywana samodzielnie. Czesc funkcji get_array_of_tasks
int amount_of_pipes(char* pol);


//te trzy funkcje do prawidlowego posortowania chronologicznego
void set_time_to_exec_temp(task_temp * array, int length);

void set_time_to_sleep_temp(task_temp * array, int length);

int comparator_temp(const void *p, const void *q);

void free_space(task_temp * array);

// int pipe_fork_stuff(char *** array, int length, char * outfile, int state);

char ** string_to_array(char * text, int * size);
int title_in_file(char*original_line_in_file, char*outfile, bool first_time);

int pipe_fork_stuff(char *** array, int length, char * outfile, int state, task_temp*ar, char* original_command_in_file);

bool status_if_import();

void change_status_import_from_file(bool t);

bool status_if_print();

void change_status_print_to_log(bool t);

void handler(int signum);

void print_to_log_function(task_temp * array, int i, int max_length);

#endif