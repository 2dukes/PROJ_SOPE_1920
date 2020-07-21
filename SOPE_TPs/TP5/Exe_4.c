#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <wait.h>

#define READ 0
#define WRITE 1
#define MAXLINE 1024 

int main(int argc, char* argv[]) {  
    // char str[MAXLINE];

    if(argc != 3)
    {
        fprintf(stderr, "Usage: prog dir word\n");
        exit(1);
    }

    pid_t pid1 = fork();

    if(pid1 > 0) { // Parent

        pid_t pid1;

        do {
            pid1 = wait(NULL);
        } while(pid1 != -1); 
        
        
        exit(0);
    }
    else { // Son
        int fd1[2];
        pipe(fd1);

        pid_t pid2 = fork();
        if(pid2 > 0) { // Parent
            close(fd1[READ]);

            if(fd1[WRITE] != STDOUT_FILENO) { 
                if(dup2(fd1[WRITE], STDOUT_FILENO) != STDOUT_FILENO) 
                {
                    fprintf(stderr, "DUP2 error!\n");
                    exit(4);
                }
                close(fd1[WRITE]);  
            }
            
            execl("/usr/bin/ls", "ls", argv[1], "-laR", NULL); // Result goes to FD1[WRITE]
            exit(2);
        }
        else { // Son
            close(fd1[WRITE]);

            int fd2[2];
            pipe(fd2);          
           
            pid_t pid3 = fork();
            if(pid3 > 0) { // Parent -> Reads from FD
                
                // int n;
                /*while((n = read(fd1[READ], str, MAXLINE)) != 0) {
                    write(STDOUT_FILENO, str, n);
                    // write(fd2[WRITE], str, n);
                }*/

                if(fd2[WRITE] != STDOUT_FILENO) { 
                    if(dup2(fd2[WRITE], STDOUT_FILENO) != STDOUT_FILENO) 
                    {
                        fprintf(stderr, "DUP2 error!\n");
                        exit(4);
                    }
                    close(fd2[WRITE]);  
                }

                if(fd1[READ] != STDIN_FILENO) { 
                    if(dup2(fd1[READ], STDIN_FILENO) != STDIN_FILENO) 
                    {
                        fprintf(stderr, "DUP2 error!\n");
                        exit(3);
                    }
                    close(fd1[READ]);  
                }

                execl("/usr/bin/grep", "grep", argv[2], NULL); // Result goes to FD2[WRITE] | Reads from FD1[READ]
                exit(2);
            }
            else { // Son
                // exit(1);
                close(fd1[READ]);
                close(fd2[WRITE]);

                // int n;
                // while((n = read(fd2[READ], str, MAXLINE)) != 0) {
                //     write(STDOUT_FILENO, str, n);
                //     // write(fd2[WRITE], str, n);
                // }

                if(fd2[READ] != STDIN_FILENO) { 
                    if(dup2(fd2[READ], STDIN_FILENO) != STDIN_FILENO) 
                    {
                        fprintf(stderr, "DUP2 error!\n");
                        exit(3);
                    }
                    close(fd2[READ]);  
                }
                
                execl("/usr/bin/sort", "sort", NULL);
                exit(2);
            }
        }    
    }

    return 0;   
}

/* 
    DIR * dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    char str[MAXLINE];

    if((dirp = opendir(argv[1])) == NULL) {
        fprintf(stderr, "Error opening directory %s", argv[1]);
        exit(2);
    }

    while((direntp = readdir(dirp)) != NULL) {
        sprintf(str, "%s/%s", argv[1], direntp->d_name);

        lstat(str, &stat_buf); 
        
        if(S_ISDIR(stat_buf.st_mode)) 
            printf("Found a dir: \n");
        
        printf("%s\n", str);        
    }
    closedir(dirp);
    */ 