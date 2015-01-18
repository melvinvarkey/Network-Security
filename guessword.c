/* 
   Extracting Word-list , creating hashes in Hashlist and find username:password 
   use: ./guessword <UNSHADOW-FILE> <DICTIONARY-FILE>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>

#define _GNU_SOURCE

int main(int argc, char *argv[])
{
  char *crypt(const char *pa,const char *salt);
  
  FILE *file1 = fopen(argv[2],"r");
  FILE *file3;
  file3 = fopen("pass-ext.txt","w");
  FILE *file_hash;
  FILE *unshadow, *allcracked;

  char c1[10],c2[10],c3[10],pass[10],password[100],user[100];
  char *pa, salt[] = "$1$GC";
  char *line = NULL, *lineu = NULL, *str;
  size_t len = 0, lenu = 0;
  ssize_t read, readu;
  int i = 0;

  if (file1 == NULL)
    exit(EXIT_FAILURE);
  if (file3 == NULL)
    exit(EXIT_FAILURE);

  //Extract known passwords from dictionary to pass-ext.txt
  while ((read = getline(&line, &len, file1)) != -1)
  {
    sscanf(line,"%s%s%s%s",c1,c2,c3,pass);
    fputs(pass,file3);
    fputc('\n',file3);
  }
  fclose(file1);
  fclose(file3);
  
  file3      = fopen("pass-ext.txt","r");
  file_hash  = fopen("hashlist.txt","w");
  allcracked = fopen("allcrackedpasswords.txt","w");
 
  if (file3 == NULL)
    exit(EXIT_FAILURE);

  //puts all the passwords of pass-ext.txt into hashlist.txt 
  while(fscanf(file3,"%s",line) != -1)
  { 
    pa = crypt(line,salt);
    fputs(pa,file_hash);
    fputc('\n',file_hash);
   
    unshadow = fopen(argv[1],"r");

    while((readu = getline(&lineu,&lenu,unshadow))!=-1) 
    {
      str = strtok(lineu,":");
      while(str != NULL && i < 2) 
      {
        if(i == 0) 
        {
          sscanf(str,"%s",user);
          str = strtok(NULL,":");
        }
        else if(i == 1) 
        {
          sscanf(str,"%s",password);
          str = strtok(NULL,":");
        } i++;
      } i = 0;
    if(strcmp(pa,password) == 0) {
       fputs(user,allcracked);
       fputc(':',allcracked);        
       fputs(line,allcracked);
       fputc('\n',allcracked);
     }
    }
  }
  free(line);
  free(lineu);
  fclose(file3);
  fclose(file_hash);
  fclose(unshadow);
  exit(EXIT_SUCCESS);
}
