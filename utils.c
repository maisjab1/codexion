#include "codexion.h"

long get_elapsed_ms(struct timespec start)
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);	
	return ((now.tv_sec - start.tv_sec )*1000 +(now.tv_nsec - start.tv_nsec)/ 1000000)
}
