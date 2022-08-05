#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char **argv){
    int pipe1[2];
    int pipe2[2];
    pid_t childpid;
    FILE *fdin;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }

    pipe(pipe1);
    pipe(pipe2);

    // error handling
    if ((childpid = fork()) == -1){
        perror("fork");
        exit(1);
    }

    // parent load file, write to pipe1
    if (childpid != 0){
       
        char buf[1024];
        close(pipe1[0]);
        close(pipe2[1]);

        fdin = fopen(argv[1], "r");
        if (fdin == 0)
        {
            fprintf(stderr, "%s: failed to open file '%s'\n", argv[0], argv[1]);
            exit(1);
        }

     

        int nbytes = fread(buf, 1, sizeof(buf), fdin);
        if (nbytes <= 0)
        {
            fprintf(stderr, "%s: no data in file '%s'\n", argv[0], argv[1]);
            exit(1);
        }
        fclose(fdin);

   
        write(pipe1[1], buf, nbytes);
        close(pipe1[1]);
    }
    else if (childpid == 0){
        
        close(pipe1[1]);
        close(pipe2[0]);
        dup2(pipe2[1], STDOUT_FILENO);//STDOUT_FILENO is an integer file descriptor (actually, the integer 1). You might use it for write syscall.
        dup2(pipe1[0], STDIN_FILENO);//STDIN_FILENO is the default standard input file descriptor number which is 0 .
        close(pipe2[1]);
        close(pipe1[0]);

        execlp("sort", "sort",(char *)0);

        fprintf(stderr, "%s: failed to exec 'sort'\n", argv[0]);
        exit(1);
    }

    // wait child
    wait(NULL);

    // parent read pipe 2 and print
    if (childpid != 0){
        char buf[1024];
        int nbytes;
        while ((nbytes = read(pipe2[0], buf, sizeof(buf))) > 0)
            printf("%.*s", nbytes, buf);
    }
    return 0;
}
