#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
 DIR *dirp;
 struct dirent *direntp;
 struct stat stat_buf;
 char *str;

 if (argc != 2)
 {
  fprintf( stderr, "Usage: %s dir_name\n", argv[0]);
  exit(1);
 }

 if ((dirp = opendir( argv[1])) == NULL)
 {
  perror(argv[1]);
  exit(2);
 }

 chdir(argv[1]); // Line to be added

 printf("%-10s%25s%15s - %s\n\n", "I_NODE", "NAME", "SIZE", "TYPE");
 while ((direntp = readdir( dirp)) != NULL)
 {
  
  /*
    With lstat, the info of the symbolic link is shown. 
    With stat, the info of shown is the file that the symbolic link points to.
    But still, the sLink I_NODE is never changed.
  */
 
  if (lstat(direntp->d_name, &stat_buf)==-1)   // testar com stat()
  {
   perror("lstat ERROR");
   exit(3);
  }
  
  if (S_ISREG(stat_buf.st_mode)) str = "regular";
  else if (S_ISDIR(stat_buf.st_mode)) str = "directory";
  else str = "other";
  printf("%-10d%25s%15d - %s\n", (int)direntp->d_ino, direntp->d_name, (int) stat_buf.st_size, str);
 }

 closedir(dirp);
 exit(0);
}
