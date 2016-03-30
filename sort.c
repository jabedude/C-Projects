#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

//Credit:
//http://stackoverflow.com/questions/12489/how-do-you-get-a-directory-listing-in-c

int fileIsMp(char* s);

int main(int argc, char* argv[])
{
	DIR* targetDir;
	struct dirent* ep;
	targetDir = opendir("./");

	if(targetDir != NULL)
	{
		while(ep = readdir(targetDir))
			puts(ep->d_name);
		(void)closedir(targetDir);
	}
	else
		perror("Couldnt Open dir");
	


	return 0;
}

int fileIsMp(char* s)
{
	size_t size = strlen(s);
	
	if (s[size-4] == '.' &&
	    s[size-3] == 'm' &&
	    s[size-2] == 'p' &&
	    s[size-1] == '3')
}
