#include "fun.h"
int main(int argc, char **argv){
    // signal(SIGINT, handler);
    signal(SIGUSR1, handler);
    signal(SIGINT, handler);
    signal(SIGUSR2, handler);
    if(amount_of_arguments(argc, argv[0]) > 0)
        return EXIT_FAILURE;

    if(equal_namings(argv[1], argv[0]))
        return EINVAL;
    openlog("PROJEKT", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Daemon wlasnie wystartowal");
    FILE * file;
    task_temp * array_of_programs;

    RESTART:

    if ((file = checking_file_valid(argv[1])) == NULL)
        return EINVAL;
    if (( array_of_programs = get_array_of_tasks(file) )== NULL)
        return EINVAL;
    int length = length_of_file();
    set_time_to_exec_temp(array_of_programs, length);
    qsort(array_of_programs, length, sizeof(*array_of_programs), comparator_temp);
    set_time_to_sleep_temp(array_of_programs, length);

    bool first_time =true;
    for(int i = 0; i<length ; ++i){
        // for(int j=0; j<array_of_programs[i].time_to_sleep_before_exec; ++j){
            for(int k=0 ; k < 60 ; ++k){
                if(status_if_print() == true){
                    print_to_log_function(array_of_programs, i, length);
                    change_status_print_to_log(false);
                }
                if(status_if_import() == true){
                    change_status_import_from_file(false);
                    free_space(array_of_programs);
                    fclose(file);
                    goto RESTART;
                }
                sleep(1);
            }
        // }
        title_in_file(array_of_programs[i].original_command_from_file, argv[2], first_time);
        pipe_fork_stuff(array_of_programs[i].program, array_of_programs[i].no_pipes, argv[2], array_of_programs[i].state, array_of_programs, array_of_programs[i].original_command_from_file);
        first_time = false;
    }
    free_space(array_of_programs);

    return 0;
}
