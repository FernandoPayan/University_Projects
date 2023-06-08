/* author: fpayan */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
  /* Checks if the file exists */
  int file = open(argv[1], O_RDONLY | O_CREAT, 0644);

  if (file == -1)
  {
    printf("File doesn't exist\n");
    exit(1);
  }

  /* File we will write to */
  int output = open(argv[2], O_WRONLY | O_CREAT, 0644);

  char buffer[1024]; /* Stores the line in the file */
  int numbytes = 0; /* Stores the number of bytes in the file. */
  int readfile = 0; /* Used to read the file */

  /* Iterates through each line in the file */
  while ( (readfile = read(file, buffer, 1024)) > 0)
  {
    numbytes += readfile;
    
    int writefile = write(output, buffer, readfile);
    
  };

  printf("%s was copied to %s successfuly.\n", argv[1], argv[2]);
  printf("Total number of bytes: %d\n", numbytes);


  close(output);
  close(file);

  return 0;
}