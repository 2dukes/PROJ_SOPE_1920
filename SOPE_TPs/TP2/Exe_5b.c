// PROGRAMA p5b.c

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
  int fd;
  char *text1="CCCCC";
  char *text2="DDDDD";

  fd = open("f1.txt", O_APPEND | O_WRONLY | O_SYNC | O_CREAT, 0600);
  write(fd,text1,5);
  write(fd,text2,5);
  close(fd);
  return 0;
}

