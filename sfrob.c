#include <stdio.h>
#include <stdlib.h>

//first create a helper functin, frobcmp, to compare char const * vars 
int frobcmp (const char* a, const char* b)
{
  //iterate through the arrays, comparing each byte one at a time
  while ((*a < 32) && (*b < 32))
    {
      //compare the chars using XOR 42
      char a_val = *a^42;
      char b_val = *b^42;
      if (a_val > b_val)
	  return 1;
      else if (a_val < b_val)
	  return -1;
      a++;
      b++;
    }

  //if this code is reached, the arrays are identical up to a point
  //such as a being a prefix of b, b being a prefix of a, identical words

  //check for a being a prefix
  if ((*a == 32) && (*b != 32))
    return -1;
  //check for b being a prefix
  else if ((*b == 32) && (*a != 32))
    return 1;
  //otherwise they are equal
  else
    return 0;
}

int wrap_frobcmp(const void* a, const void* b)
{
  char const* firstw = *(char const**)a;
  char const* secondw = *(char const**)b;
  return frobcmp(firstw, secondw);
}

int main()
{
  int memory = 8;
  char *char_arr = (char*)malloc(sizeof(char)*memory);

  if (char_arr == NULL)
    {
      fprintf(stderr, "Allocation of memory failed.");
	exit(1);
    }

  int cur_char;
  int wordCount = 0;
  int i;

  for (i = 0; (cur_char = getchar()) != EOF; i++)
    {
      //check to see if memory is already allocated, if not allocate some
      if (i == memory)
	{
	  //increase allocated memory size
	  memory = memory*2;
	  char_arr = (char*)realloc(char_arr, memory);
	  if (char_arr == NULL)
	    {
	      fprintf(stderr, "Reallocation of memory failed.");
	      exit(1);
	    }
	}
      //keep track of words (they are separated by a space)
      if ((char)cur_char == ' ')
	wordCount++;
      //make sure no newlines are added
      if ((char)cur_char == '\n')
	break;
      //add char to the array
      char_arr[i] = (char)cur_char;
    }
  //check to make sure input ends with nonspace
  if (char_arr[i] != ' ')
    {
      wordCount++;
      char_arr[i] = ' ';
    }

  int arr_size = i;

  if (ferror(stdin))
    {
      fprintf(stderr, "Error occured reading from stdin.");
      exit(1);
    }
  //create a new array of pointers 
  char ** wordPtr = (char**)malloc(sizeof(char*)*wordCount);
  if (wordPtr == NULL)
    {
      fprintf(stderr, "Memory allocation failed, array contains pointers.");
	exit(1);
    }
  //create a pointer at the beginning of the array
  char *begin = char_arr;

  for (int k = 0; k < wordCount; k++)
    {
      wordPtr[k] = begin;
      //end of the array
      if (k == (wordCount - 1))
	break;
      while (*begin != ' ')
	begin++;
      begin++;
    }

  //sort the pointers
  qsort(wordPtr, wordCount, sizeof(char*), wrap_frobcmp);
  //output the newly sorted words
  char *output;
  for (int m = 0; m < wordCount; m++)
    {
      output = wordPtr[m];
      putchar(*output);

      while (*output != ' ')
	{
	  output++;
	  putchar(*output);
	}
    }

  if (ferror(stdout))
    fprintf(stderr, "failure");
  free(char_arr);
  free(wordPtr);
}
