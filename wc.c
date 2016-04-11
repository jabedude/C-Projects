/*

Poor mans wc made by me

*/

#include <stdio.h>
#include <stdlib.h>

int counter(FILE* file)
{
        int count = 0;
        int wordcount = 0;
        int charcount = 0;

        char ch;
                
        while((ch = fgetc(file)) != EOF) 
        {       
                if(ch == '\n')
                        count++;
                else if(ch == ' ') 
                        wordcount++;
                charcount++;
        }

        printf("%d\n%d\n%d\n", count, wordcount, charcount);
        return count;
}

int main(int argc, char* argv[]) 
{

        if(argc != 2)
        {       
                printf("Please supply one argument\n");
                return 1;
        }

        FILE* filepointer;
        filepointer = fopen(argv[1], "r");
                
        counter(filepointer);

        return 0;
}
