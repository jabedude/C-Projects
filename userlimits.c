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
	
	printf("Hard stack limit: %#llx\nCurrent Stack Limit: %#llx\n", max, cur);

	getrlimit(RLIMIT_NPROC, &rlim);
	cur = rlim.rlim_cur;
	
	printf("Current process limit: %#llx\n", cur);

	return 0;
}
