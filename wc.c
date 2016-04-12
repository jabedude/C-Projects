/*

Poor mans wc made by me

*/

#include <stdio.h>
#include <stdlib.h>

/*
func prototype
*/
int counter(FILE* file, char* fname);

int main(int argc, char* argv[]) 
{

        if(argc != 2)
        {       
                printf("Please supply one argument\n");
                return 1;
        }

        FILE* filepointer;
        filepointer = fopen(argv[1], "r");
                
        counter(filepointer, argv[1]);

        return 0;
}

int counter(FILE* file, char* fname)
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

        printf("%d\t%d\t%d\t%s\n", count, wordcount, charcount, fname);
        return count;
}