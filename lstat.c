/*

Prints file metadata using the lstat() system call:

Access time
Modification time
creation time

compile with gcc -std=gnu99 lstat.c

*/


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
                printf("%s\n", argv[i]);
                lstat( argv[i], &file_info );
                c = (long long)file_info.st_atim.tv_sec;
                m = (long long)file_info.st_mtim.tv_sec;
                cr = (long long)file_info.st_ctim.tv_sec;
                printf("Create time: %s", ctime( &cr ) );
                printf("Access time: %s", ctime( &c ) );
                printf("Modification time: %s", ctime( &m ) );
                                //printf("%lld.%.9ld\n", (long long)file_info.st_atim.tv_sec, file_info.st_atim.tv_nsec);
        }
        return 0;
}
