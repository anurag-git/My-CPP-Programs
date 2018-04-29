#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 1000
#define BUFFSIZE 100

int
parseFile (char *filename)
{
  char *token = NULL;
  typedef enum { false, true } bool;
  bool headerPresent = false;
  char year[5];
  char str[MAXCHAR];
  int BASE_YEAR = 0;
  int currentYear = 0;
  int previousYear = 0;
  int lastYear = 0;
  int totalCount = 0;
  int yearCounter[BUFFSIZE];
  int currentYearCount = 0;
  int noOfColumns=0;
  int noOfElementsInYearCounter = 0;
  char str1[1024];
  char *columnsFile = "./columns_global.csv";
  FILE *fp;
  fp = fopen (filename, "r");
  if (fp == NULL) {
      printf ("Could not open file %s\n", filename);
      return 1;
  }

  for(int i=0; i<BUFFSIZE; i++)
    yearCounter[i] = 0;

  char columnName[200][1024];
  if (fgets(str1, 1024, fp) != NULL)
   {
     char *token1 = strtok(str1,",");
     while( token1 != NULL )
     {
          strcpy(columnName[noOfColumns],token1);
          noOfColumns++;
          token1 = strtok(NULL,",");
     }
   }

  fseek(fp, 0, SEEK_SET);

  int lineno = 0;
  while (fgets (str, MAXCHAR, fp) != NULL) {
      token = strtok (str, ",");
      //printf("%s\n", token);
      strncpy (year, token, 4);
      year[4] = '\0';

      if (lineno == 0) {
    	  BASE_YEAR = atoi (year);
    	  if (BASE_YEAR == 0) {
          headerPresent = true;
          continue;
        }

    	  lastYear = currentYear = previousYear = BASE_YEAR;
    	  currentYearCount++;
    	  totalCount++;
    	  yearCounter[previousYear - BASE_YEAR] = currentYearCount;
    	  lineno++;
	    }

      currentYear = atoi (year);
      if (currentYear == previousYear) {
	       currentYearCount++;
	    } else {
	       currentYearCount = 1;
	  	   previousYear = currentYear;
         lastYear=currentYear;
	    }

      totalCount++;
      yearCounter[previousYear - BASE_YEAR] = currentYearCount;
    }

  noOfElementsInYearCounter=lastYear-BASE_YEAR+1;

  FILE *fpToWrite=NULL;
  char fileToWrite[50];
  strcpy(fileToWrite,filename);
  strcat(fileToWrite,".info");

  fpToWrite = fopen(fileToWrite, "w");
  if (fpToWrite == NULL) {
      printf ("Could not open file %s\n", fileToWrite);
      return 1;
  }

  char toPrint[4000]; char temp[100];
  sprintf(temp,"File: %s\n", filename);
  strcat(toPrint,temp);
  if (headerPresent) {
    sprintf(temp, "Header: %s\n", "present");
    strcat(toPrint,temp);
  } else {
    sprintf(temp,"Header: %s\n", "absent");
    strcat(toPrint,temp);
  }

  sprintf(temp,"Rows: %d\n", totalCount);
  strcat(toPrint,temp);

  sprintf(temp, "Columns: %d\n%s\nid years: %d - %d\n%s\n", noOfColumns,"------------------------------------",BASE_YEAR, lastYear,"Year   Rows");
  strcat(toPrint,temp);

  fprintf(fpToWrite, "%s", toPrint);
  printf("%s", toPrint);

  for (int i = 0; i < noOfElementsInYearCounter; i++)
  {
      if (yearCounter[i]) {
	       printf("%d : %d \n", BASE_YEAR + i, yearCounter[i]);
         fprintf(fpToWrite,"%d : %d \n", BASE_YEAR + i, yearCounter[i]);
      } else {
	       printf("%d : %c \n", BASE_YEAR + i, '-');
         fprintf(fpToWrite,"%d : %c \n", BASE_YEAR + i, '-');
      }
  }

  if(headerPresent) {
    FILE *fpColumn;
    fpColumn = fopen(columnsFile, "r");
    if (fpColumn == NULL) {
        printf ("Could not open file %s", columnsFile);
        return 1;
    }

    printf ("------------------------------------\nColumns\n");
    fprintf(fpToWrite, "%s", "------------------------------------\nColumns\n");

    int count=-1,missing=0,countVar=0;
    char *missingStr="[not found]";
    while (fgets (str, MAXCHAR, fpColumn) != NULL)  {
      if(count == -1) {
        printf("# %s",str);
        fprintf(fpToWrite, "# %s", str);
        count++;
        continue;
      }

        printf("%d %s",count+1,str);
        if(strstr (str,columnName[count])) {
        fprintf(fpToWrite, "%d %s", count+1,str);
      } else {
        printf("%d %s   %s\n",count+1,columnName[count],missingStr);
        fprintf(fpToWrite, "%d %s   %s\n",count+1,columnName[count],missingStr);
        count++;
        printf("%d %s",count+1,str);
        fprintf(fpToWrite, "%d %s", count+1,str);
      }

      count++;
    }

    for(int i=0;i<strlen(columnName[count]);i++) {
      if(columnName[count][i] == '\n')
        columnName[count][i] = '\0';
    }
    printf("%d %s   %s\n",count+1,columnName[count],missingStr);
    fprintf(fpToWrite, "%d %s   %s\n",count+1,columnName[count],missingStr);

    fclose(fpColumn);
  }

  fclose(fpToWrite);
  fclose (fp);
  return 0;
}

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      printf ("Incorrect no of arguments passed\n");
      printf ("Usage: argv[0] <filename.csv>\n");
      return 1;
    }
  else if (argc > 2)
    {
      printf ("Too many arguments supplied.\n");
      return 1;
    }

  char *filename = argv[1];
  parseFile(filename);
  return 0;
}
