//copy the main function from randall.c
//modify part of it (its marked)
#include "randcpuid.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <immintrin.h>

int
main (int argc, char **argv)
{
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  if (nbytes == 0)
    return 0;

  void (*initialize) (void);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);

  //begin changing the code
  
  void *soft;
  void *hard;
  
  if (rdrand_supported ())
    {
      //still call the hardware functions, but differently
      hard = dlopen("randlibhw.so", RTLD_NOW);
      if (dlerror() != NULL)
	{
	  printf("Hardware library failure \n");
	  return -1;
	}
      initialize = dlsym(hard, "hardware_rand64_init");
      if (dlerror() != NULL)
	{
	  printf("Hardware initiation function error \n");
	  return -1;
	}
      rand64 = dlsym(hard, "hardware_rand64");
      if (dlerror() != NULL)
	{
	  printf("Hardware rand64 function error \n");
	  return -1;
	}
      finalize = dlsym(hard, "hardware_rand64_fini");
      if (dlerror() != NULL)
	{
	  printf("Hardware finalization function error \n");
	  return -1;
	}
    }
  else
    {
      soft = dlopen("randlibsw.so", RTLD_NOW);
      if (dlerror() != NULL)
	{
	  printf("Software library failure \n");
	  return -1;
	}
      initialize = dlsym(soft, "software_rand64_init");
      if (dlerror() != NULL)
	{
	  printf("Software initiation function error \n");
	  return -1;
	}
      rand64 = dlsym(soft, "software_rand64");
      if (dlerror() != NULL)
	{
	  printf("Software rand64 function error \n");
	  return -1;
	}
      finalize = dlsym(soft, "software_rand64_fini");
      if (dlerror() != NULL)
	{
	  printf("Software finalization function error \n");
	  return -1;
	}
    }

  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (fwrite (&x, 1, outbytes, stdout) != outbytes)
	{
	  output_errno = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      finalize ();
      return 1;
    }
  if (hard == NULL)
    dlclose(soft);
  else
    dlclose(hard);
  return 0;
}
