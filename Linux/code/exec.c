#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid_1,pid_2,pid_3;
    int pip[2];
    int status,pid;
    char str[] = "Who are you?";
    char str0[] = "Hello,world!";
    char buff[30];

    pipe(pip);

    pid_1 = fork();
    if(pid_1 == 0) {
        close(pip[0]);
        close(pip[1]);

        execlp("echo","echo","I'm children!",(char *) 0);
        perror("exec1 error.\n");
        exit(1);
    }
    
    pid_2 = fork();
    if(pid_2 == 0) {
        close(pip[0]);
        close(pip[1]);

        execlp("ls","ls","-l",NULL);
        perror("excel2 error. \n");
        exit(1);
    }

    pid_3 = fork();

    if(pid_3 == 0) {
        write(pip[1],str,sizeof(str));
        read(pip[0],buff,30);
        printf("buff from father:");
        puts(buff);
    }else {
        read(pip[0],buff,30);
        printf("buff from sun:");
        puts(buff);
        write(pip[1],str0,sizeof(str0));
    }


    while((pid = wait(&status)) != -1) {
        if(pid_1 == pid)
            printf("child 1 exit with %d \n",(status >> 8));
        if(pid_2 == pid)
            printf("child 2 exit with %d \n",(status >> 8));
        if(pid_3 == pid)
            printf("child 3 exit with %d \n",(status >> 8));
    }
    
    puts("All process terminated.\n");

    return 0;
}

