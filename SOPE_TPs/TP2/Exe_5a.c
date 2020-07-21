#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define ERROR -1

int main(void)
{
  int fd;
  int nw;
  char *text1="AAAAA";
  char *text2="BBBBB";

  
  if((fd = open("f1.txt",O_CREAT|O_EXCL|O_TRUNC|O_WRONLY|O_SYNC|O_APPEND,0600)) == ERROR)
  {
      write(STDOUT_FILENO, strerror(errno), strlen(strerror(errno)));
      return 1;
  }

  write(STDOUT_FILENO, "Writing text1...\n", 17);
  getchar();
  if((nw = write(fd,text1,5)) <= 0)
  {
      perror(text1);
      close(fd);
      return 2;
  }
  write(STDOUT_FILENO, "\n\nWriting text2...\n", 19);
  getchar();
  if((nw = write(fd,text2,5)) <= 0)
  {
      perror(text2);
      close(fd);
      return 3;
  }
  close(fd);
  return 0;


}

