
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
#define WRITE_END 1
#define READ_END 0
int lk =0;
int k=0;
bool first_time = true;
int title_in_file(char*original_line_in_file, char*outfile){
    FILE * file;
    if(first_time){
        if((file = fopen(outfile, "w")) == NULL){
            perror("Function title_in_file:");
            return -1;
        }
    }
    else{
        if((file = fopen(outfile, "a")) == NULL){
            perror("Function title_in_file:");
            return -1;
        }
    }
    if(first_time)
        fprintf(file, "%s\n", original_line_in_file);
    else
        fprintf(file, "\n%s\n", original_line_in_file);
    first_time = false;
    fclose(file);
    return 0;
}
int pipe_fork_stuff(char *** array, int length, char * outfile, int state){
    
    bool something_bad = false;
    pid_t pid;
    int file, file_null;
    int fd[length-1][2];
    if((file = open(outfile, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC , 0777)) < 0){
        exit(EXIT_FAILURE);
    }
    if((file_null = open("/dev/null", O_WRONLY)) < 0){
        exit(EXIT_FAILURE);
    }
    if(state >= 1)
        dup2(file, STDERR_FILENO);
    for(int i = 0 ; i < length-1 ; ++i)
        pipe(fd[i]);
    for(int i = 0 ; i < length ; ++i){
        pid = fork();
        if(pid == 0){
            if((i == length - 1) && (i == 0)){
                if(state  == 0){
                    dup2(file, STDOUT_FILENO);
                    dup2(file_null, STDERR_FILENO);
                }
                if(state == 1)
                    dup2(file_null, STDOUT_FILENO);
                if(state == 2)
                    dup2(file, STDOUT_FILENO);
                
                execvp(array[0][0], array[0]);
                fprintf(stderr, "%s: %s", array[0][0],strerror(errno));
                something_bad = true;
                exit(EXIT_FAILURE);
                close(file);
                close(file_null);
            }
            else if(( i == length - 1 ) && ( i != 0 )){
                dup2(fd[i-1][READ_END], STDIN_FILENO);
                
                if(state  == 0){
                    dup2(file, STDOUT_FILENO);
                    dup2(file_null, STDERR_FILENO);
                }
                if(state == 1)
                    dup2(file_null, STDOUT_FILENO);
                if(state == 2)
                    dup2(file, STDOUT_FILENO);
                execvp(array[i][0], array[i]);
                fprintf(stderr, "%s: %s", array[i][0],strerror(errno));
                something_bad = true;
                exit(EXIT_FAILURE);
                close(file);
                close(file_null);
            }
            else{
                if(i != 0)
                    dup2(fd[i-1][READ_END], STDIN_FILENO);

                close(fd[i][READ_END]);
                // perror("555");
                dup2(fd[i][WRITE_END], STDOUT_FILENO);
                if(state == 0)
                    dup2(file_null, STDERR_FILENO);
                execvp(array[i][0], array[i]);
                fprintf(stderr, "%s: %s", array[0][0],strerror(errno));
                something_bad = true;
                exit(EXIT_FAILURE);
                close(file);
                close(file_null);
            }
        }
        else if(pid > 0){
            int status;
            waitpid(pid, &status, 0);
            // if(something_bad == true){
            //     close(fd[i][WRITE_END]);
            //     close(file);
            //     close(file_null);
            //     exit(EXIT_FAILURE);
            // }
            if(WIFEXITED(status)){
                if(WEXITSTATUS(status) != 0){
                    printf("hh");
                    close(fd[i][WRITE_END]);
                    // something_bad = true;
                    close(file);
                    close(file_null);
                    return 0;
                }
            }
            if( i != (length-1))
                close(fd[i][WRITE_END]);
            if((i == length - 1)){
                close(file);
                close(file_null);
            }
            ++lk;

        }
    }
    return 0;
}

int t=0;
int main(){
    // char * arr1[] = {"ls", "ko", NULL};
    // char * arr2[] = {"grep", "p", NULL};
    // char ** array[] = {arr1, arr2};
    // printf("Cos w ogole umiesz");
    // perror("Suko");
    // char pol[] = "ls \\| | hihihi";
    // char *save_pol = NULL;
    // char *token;
    // int size[2];
    // size[0] =0;
    // size[1] =0;
    // int i = 0;
    // char polak [200] ="";
    // token = strtok_r(pol, "|", &save_pol);
    // while(token != NULL){
    //     strcpy(polak, token);
    //     printf("%s->%ld", token, strlen(token));
    //     while(polak[strlen(polak)-1] == '\\'){
    //         strcat(polak, "|");
    //         token = strtok_r(NULL, "|", &save_pol);
    //         printf("%s", token);
    //     }
    //     prep[i] = string_to_array(polak, &size[i]);
    //     if(prep[i] == NULL)
    //         perror("siku");
    //     ++i;
    //     token = strtok_r(NULL, "|", &save_pol);
    //     perror("hih");
    // }
    // for(int j=0 ; j<2; ++j)
    //     for(int t = 0; t<size[j]; ++t)
    //         printf("\n%s------>%d\n", prep[j][t], size[j]);
    
    // for (int j=0 ; j<2; ++j){
    //     for(int t = 0; t<size[j]; ++t)
    //         free(prep[j][t]);
    //     free(prep[j]);
    // }
    // free(prep);
    // pid_t pid;
    // pid = fork();
    // pid = fork();
    // if (pid == 0)
        // printf("Dupa");
    // if(pid > 0)
        // printf("Mala");
        // 20:30:ls -l:2
// 20:40:ls -l | wc -l:2
// 12:10:lsdp -ldfd:2
// 10:30:codxsad:2
    char * arr1[] = {"ls", "-l", NULL};
    char * arr6[] = {"ls", "-l", NULL};
    char * arr2[] = {"wc","-l", NULL};
    char * arr5[] = {"lsdp", "-ldfd", NULL};
    char * arr[] = {"codxsad", NULL};
    // char * arr3[] = {"ls", "-l", NULL};
    // char * arr4[] = {"grep", "p", NULL}; 
    // char * arr3[] = {"awk","'{print", "$5", "\"", "\"", "$3", "\"", "\"", "$9}'", NULL};
    // char * arr4[] = {"sort","-n", NULL};
    char **array3[] = {arr6};
    char **array[] ={arr1, arr2};
    char **array2[] ={arr5};
    char **array4[] ={arr};

    // char **array[] ={arr1};
    lk=0;
    pipe_fork_stuff(array, 2, "polko.txt",2);
    printf("\n\n----=---%d\n\n", lk);

    // lk=0;
    // pipe_fork_stuff(array2, 1, "polko.txt",2);
    // printf("\n\n----=---%d\n\n", lk);
    // k=0;
    // lk=0;
    // pipe_fork_stuff(array4, 1, "polko.txt",2);
    // printf("\n\n----=---%d\n\n", lk);
    // printf("\n\n----=---kkk%d\n\n", lk);
    
    // pipe_fork_stuff(array3, 1, "polko.txt",2);
    return 0;
}

// int pipe_fork_stuff(char *** array, int length, char * outfile){
//     pid_t pid;
//     int file;
//     int fd[length-1][2];
//     int flk[0];
//     int fp[2];
//     int sp[2];
//     perror("555");
//     for(int i = 0 ; i < length-1 ; ++i){
//         pipe(fd[i]);
//     }
//     for(int i = 0 ; i < length ; ++i){
//         pid = fork();
//         if(pid == 0){
//             if((i == length - 1) && (i == 0)){
//                 if((file = open("polko.txt", O_WRONLY | O_CREAT , 0777)) == 0){
//                     return 55;
//                 }
//                 dup2(file, STDERR_FILENO);
//                 perror("101");
//                 if(execvp(array[0][0], array[0])<0){
//                     perror("Fajnie");
//                     return EXIT_FAILURE;
//                 }
//                 close(file);
//             }
//             else if(( i == length - 1 ) && ( i != 0 )){
//                 perror("1");
//                 dup2(fd[i-1][READ_END], STDIN_FILENO);
//                 file = open("polko.txt", O_WRONLY | O_CREAT , 0777);
//                 perror("2");
//                 dup2(file, STDOUT_FILENO);
//                 execvp(array[i][0], array[i]);
//                 perror("kup");
//             }
//             else{
                
//                 perror("101");
//                 if(i != 0){
//                     dup2(fd[i-1][READ_END], STDIN_FILENO);
//                 }

//                 close(fd[i][READ_END]);
//                 dup2(fd[i][WRITE_END], STDERR_FILENO);
//                 perror("666");
//                 execvp(array[i][0], array[i]);
//                 return -1;
//             }
//         }
//         else if(pid > 0){
//             int status;
//             waitpid(pid, &status, 0);
//             if( i != (length-1))
//                 close(fd[i][WRITE_END]);
//                 perror("kontrolne");
//             if((i == length - 1)){
//                 perror("Po");
//                 close(file);
//             }
//         }
//     }
// }
    // pid = fork();

//     if(pid == 0){
//             close(fd[READ_END]);
        
//         // close(fd[WRITE_END]);
//         // close(fd[READ_END]);
//         dup2(fd[WRITE_END], STDOUT_FILENO);

//         execlp(array[0], array[0], array[1], (char*) NULL);
//         fprintf(stderr, "Failed to execute '%s'\n", array[0]);
//         close(fd[WRITE_END]);
//         exit(1);
//     }
//     else if (pid > 0){ 
//         pid=fork();

//         if(pid==0){
//             close(fd[WRITE_END]);
            
//             dup2(fd[READ_END], STDIN_FILENO);
//             dup2(fd[WRITE_END], STDOUT_FILENO);
//             // close(fd[WRITE_END]);
//             execlp(array[2], array[2], array[3],(char*) NULL);
//             fprintf(stderr, "Failed to execute '%s'\n", array[2]);
//             close(fd[READ_END]);
//             close(fd[WRITE_END]);
            
//             exit(1);
//         }
//         else if (pid > 0 ){
//             pid = fork();
//             if(pid == 0){
//                 close(fd[WRITE_END]);
//                 dup2(fd[READ_END], STDIN_FILENO);
//                 close(fd[READ_END]);
//                 execlp("sort", "sort",(char*) NULL);
//                 fprintf(stderr, "Failed to execute '%s'\n", array[2]);
//                 return -1;
//             }
//             else if(pid > 0)
                
//                 int status;
//                 waitpid(pid, &status, 0);
//                 close(fd[READ_END]);
//                 close(fd[WRITE_END]);
                
//             return 0;
//         }
// }