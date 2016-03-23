#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char* argv[])
{
        if (argc < 2)
        {
               printf("Usage: must supply at least one file\n");
                return 1;
        }

        struct dirent* dir_element;
        struct stat file_info;
	time_t c;
	time_t m;
	time_t cr;

        for (int i = 1; i < argc; i++)
        {
		//lstat(dir_element->d_name, &file_info);
		lstat( argv[i], &file_info );
		c = (long long)file_info.st_atim.tv_sec;
		m = (long long)file_info.st_mtim.tv_sec;
		cr = (long long)file_info.st_ctim.tv_sec;
		printf( ctime( &c ) );
		printf( ctime( &m ) );
		printf( ctime( &cr ) );
		//printf("%lld.%.9ld\n", (long long)file_info.st_atim.tv_sec, file_info.st_atim.tv_nsec);
        }
        return 0;
}
