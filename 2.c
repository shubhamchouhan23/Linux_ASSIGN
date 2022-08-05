#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
  
int main()
{
    // array of 2 size a[0] is for reading 
    // and a[1] is for writing over a pipe 
    int a[2]; 
    char* t = " 10 ";
  
    // opening of pipe using pipe(a)   
    int buff[10];
    if (pipe(a) == -1) 
    {
        perror("pipe"); // error in pipe
        exit(1); // exit from the program
    }
  
    // writing a string ("code" in pipe
    write(a[1], t,sizeof(int));
    printf("\n");
  
    // reading pipe now buff is equal to "code"
    read(a[0], buff, 5);
  
    // it will print "code"
    printf("%s\n", t);
    close(a[0]);
    close(a[1]);
}
