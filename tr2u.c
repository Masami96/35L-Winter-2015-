#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
  //the checks for validity are the same as tr2b.c so just copy it
  if (argc != 3)
    {
      printf("%s \n", "Invalid number of arguments.");
      return 1;
    }

  int len1 = strlen(argv[1]);
  int len2 = strlen(argv[2]);
  char* arg1 = argv[1];
  char* arg2 = argv[2];
  if (len1 != len2)
    {
      printf("%s \n", "Strings are not of the same length.");
      return 2;
    }

  for (int i = 0; i < len1; i++)
    {
      for (int k = 0; k < len2; k++)
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

  //now redo the code for translating characters, this is where this file is
  //different than tr2b.c

  char cur;
  while ((read(0, &cur, 1)) != 0)
    {
      for (int i = 0; i < len1; i++)
	{
	  if (cur == arg1[i])
	    {
	      write (1, &arg2[i], 1);
	      break;
	    }
	  else
	    {
	      write (1, &cur, 1);
	      break;
	    }
	}
    }
    return 0;
}
