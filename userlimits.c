/*

Prints the hard and current stack limit, and the current proc limit
on Linux and BSD.

*/

#include <stdio.h>
#include <sys/resource.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
	struct rlimit rlim;
	int64_t cur;
	int64_t max;
	
	getrlimit(RLIMIT_STACK, &rlim);
	cur = rlim.rlim_cur;
	max = rlim.rlim_max;
	
	printf("Stack Limit: %lld\n", cur);

	getrlimit(RLIMIT_NPROC, &rlim);
	cur = rlim.rlim_cur;
	
	printf("Current process limit: %lld\n", cur);

	getrlimit(RLIMIT_NOFILE, &rlim);
	cur = rlim.rlim_cur;
	
	printf("Current file descriptors limit: %lld\n", cur);

	return 0;
}
