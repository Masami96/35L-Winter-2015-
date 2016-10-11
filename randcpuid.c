/*reponsible for determining if CPU has RDRAND instruction, so copy all code
from randall.c that deals with pulling information from the CPU and analyzing
this information*/
//luckily, all this code is present at the beginning of the program
#include "randcpuid.h"
#include <cpuid.h>

struct cpuid { unsigned eax, ebx, ecx, edx; };

static struct cpuid
cpuid (unsigned int leaf, unsigned int subleaf)
{
  struct cpuid result;
  asm ("cpuid"
       : "=a" (result.eax), "=b" (result.ebx),
	 "=c" (result.ecx), "=d" (result.edx)
       : "a" (leaf), "c" (subleaf));
  return result;
}

//in randall.c this is a static call, but in randcpuid.h its an extern, change
extern _Bool
rdrand_supported (void)
{
  struct cpuid extended = cpuid (1, 0);
  return (extended.ecx & bit_RDRND) != 0;
}
