/* author: fpayan */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
  /* Checks if the file exists */
  FILE *file = fopen(argv[1], "r");

  if (file == NULL)
  {
    printf("File doesn't exist\n");
    exit(1);
  }

  /* File we will write to */
  FILE *outfile;
  outfile = fopen(argv[2], "w+");

  char str[1024]; /* Stores the line in the file */
  int numwords = 0; /* Stores the number of words in the file. */
  int numlines = 0; /* Stores the number of lines in the file. */
  int numchars = 0; /* Stores the number of chars in the file. */
  char *bytes;

  /* Iterates through each line in the file */
  while (bytes = fgets(str, sizeof(str), file))
  {
    numlines += 1;
    numchars += strlen(bytes);

    char buffer[1024];

    int size = sprintf(buffer, "%s", str);

    size_t output = fwrite(buffer, 1, size, outfile);

    /* Loop to count the number of words and chars in the line */
    for (char *t1 = strtok(str, " ,.;:!?\t\n"); t1 != NULL; t1 = strtok(NULL, " ,.;:!?\n"))
    {
      numwords++;
    };

  };

  printf("%s was copied to %s successfuly.\n", argv[1], argv[2]);
  printf("Total number of characters: %d\n", numchars);
  printf("Total number of words: %d\n", numwords);
  printf("Total number of lines: %d\n", numlines);


  fclose(outfile);
  fclose(file);

  return 0;
}

/* Function to count words */

int countchars(char *word)
{
  int charcount = 0;

  /* Count the number of characters in our word */
  for (int i = 0; word[i] != '\0'; i++)
  {
    charcount++;
  }

  return charcount;
}
