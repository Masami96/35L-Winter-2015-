#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  //check to make sure only 3 arguments, the function call and the two strings
  if (argc != 3)
    {
      printf("%s \n",  "Invalid number of arguments.");
      return 1;
    }  

  //check to make sure string1 and string2 are the same length
  int len1 = strlen(argv[1]);
  int len2 = strlen(argv[2]);
  char* arg1 = argv[1];
  char* arg2 = argv[2];
  if (len1 != len2)
    {
      printf("%s \n", "Strings are not of the same length.");
      return 2;
    }

  //check for duplicates within the first string
  for (int i = 0; i < len1; i++)
    {
      for (int k = 1; k < len1; k++)
	{
	  if (i == k)
	    continue;
	  if (arg1[i] == arg1[k])
	    {
	      printf("%s \n", "Duplicate in the first string.");
	      return 3;
	    }
	}
    }

  //if the code reaches this point, we simply start translating characters

  char cur;
  while ((cur = getchar()) != EOF)
    {
      for (int i = 0; i < len1; i++)
	{
	  if (cur == arg1[i])
	    {
	      putchar(arg2[i]);
	      break;
	    }
	  else
	    {
	      putchar(cur);
	      break;
	    }
	}
    }
  return 0;
}

