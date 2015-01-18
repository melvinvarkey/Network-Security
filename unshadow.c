/* 
   Unshadow program 
   use: ./unshadow SHADOW-FILE PASSWD-FILE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  FILE *file1 = fopen(argv[1],"r");
  FILE *file2 = fopen(argv[2],"r");
  FILE *file3 = fopen("passwordfile.txt","w");
  int i,j;
  
  char *line1 = NULL, *line2 = NULL;
  size_t len1 = 0, len2 = 0;
  ssize_t read1, read2;
  
  if (file1 == NULL)
  	exit(EXIT_FAILURE);
  if (file2 == NULL)
  	exit(EXIT_FAILURE);
  if (file3 == NULL)
  	exit(EXIT_FAILURE);

  while ((read1 = getline(&line1, &len1, file1)) != -1 &&
         (read2 = getline(&line2, &len2, file2)) != -1 )
  {
    for (i=0; i<36; i++)
      fputc(line1[i],file3);
    for (i=9; i<strlen(line2);i++)
      fputc(line2[i],file3);
  }
  
  free(line1);
  free(line2);
  fclose(file1);
  fclose(file2);
  fclose(file3);
  exit(EXIT_SUCCESS);
}
