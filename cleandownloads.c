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
		{
			puts(ep->d_name);

			//char s[] = ep->d_name;
			size_t size = strlen(ep->d_name);
			
			if ((ep->d_name[size-4] == '.' &&
			     ep->d_name[size-3] == 'm' &&
			     ep->d_name[size-2] == 'p' &&
			     ep->d_name[size-1] == '3')||
			    (ep->d_name[size-4] == '.' &&
			     ep->d_name[size-3] == 'g' &&
			     ep->d_name[size-2] == 'i' &&
			     ep->d_name[size-1] == 'f'))
			{
				remove(ep->d_name);
			}
			else
				perror("File ");

		}

		(void)closedir(targetDir);
	}
	else
		perror("Couldn't open directory. :(");

	return 0;
}
/*
int fileIsMp(char* s)
{
	char s[] = ep->d_name;
	size_t size = strlen(s);
	
	if (s[size-4] == '.' &&
	    s[size-3] == 'm' &&
	    s[size-2] == 'p' &&
	    s[size-1] == '3')
	{
		remove(s);
	}
	else
		perror("Couldn't delete file :(");
}
*/

