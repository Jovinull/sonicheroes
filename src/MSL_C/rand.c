#include "types.h"

// MSL rand.c, 0x801C28D0 to 0x801C28F8: the linear congruential generator.
// Its seed is the unit's only data, in .sdata at 0x8042BED8.
// Reference: PrimeDecomp/prime extern/sdk/runtime/rand.c. Built with GC/1.3
// like the rest of MSL_C.

static unsigned long int next = 1;

int rand(void)
{
	next = next * 1103515245 + 12345;
	return (next >> 16) & 0x7FFF;
}

void srand(unsigned int seed)
{
	next = seed;
}
