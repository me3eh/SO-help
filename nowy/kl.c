#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main (int argc, char** argv)
{
    if (argc != 2){
        fprintf(stderr, "Usage: %s <filename>\n",
                        argv[0]);
        // perror("Usage: %s", argv[0]);
        //nieprawidlowy wejscie
        return EINVAL;
    } 
    int fds[2];
    pid_t pid;
    int code;
    if (pipe(fds) < 0){
        code = errno;
        perror("Fail pipe");
        return code;
    }
    pid = fork ();
    if (pid == (pid_t) 0) {
        
        close (fds[1]);
        
        int file;
        
        if ((file = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0){
            code = errno;
            perror("Open to-write file");
            return code;
        }

        if (dup2(fds[0], STDIN_FILENO) < 0){
            perror("Duplicating for input:");
            return errno;
        }

        if (dup2 (file, STDOUT_FILENO) < 0){
            code = errno;
            perror("Duplicating for file:");
            return code;
        }

        if (execlp("cat", "cat", NULL) < 0){
            perror("Shell command:");
            return errno;
        }

        close(file);

    } else if (pid >0){
        /* This is the parent process. */
        FILE* stream;
        /* Close our copy of the read end of the file descriptor. */
        close (fds[0]);
        /* Convert the write file descriptor to a FILE object, and write to it. */
        stream = fdopen (fds[1], "w");

        fprintf (stream, "This is a test.\n");
        fprintf (stream, "Hello, world.\n");
        fprintf (stream, "My dog has fleas.\n");
        fprintf (stream, "This program is great.\n");
        fprintf (stream, "One fish, two fish.\n");
        fflush (stream);

        close (fds[1]);
        /* Wait for the child process to finish. */
        waitpid (pid, NULL, 0);
    }
    else{
        perror("Fork failure");
        return errno;
    }
    return 0;
}