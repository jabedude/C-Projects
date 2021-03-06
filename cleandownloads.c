/*

Deletes mp3 and gif files in a directory 

*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

//Credit:
//http://stackoverflow.com/questions/12489/how-do-you-get-a-directory-listing-in-c
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
