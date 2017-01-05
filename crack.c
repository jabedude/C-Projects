/**
 * 
 * This is Josh Abraham's implementation
 * of CS50's crack assignment.
 * This program takes user inputted
 * password hash and returns the plaintext
 * of the hashed password.
 * 
 */

// For the C DES crypt(3) function
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Increment array function prototype
char* inc_arr(char* test);

// Array sum function prototype
int sum_arr(char* test);

int main(int argc, string argv[]){
    // Checks if input is correct
    if (argc != 2){
        printf("Usage: %s <hashed password>\n", argv[0]);
        return 1;
    }
    
    // Gets the salt from the hash
    char salt[2];
    strncpy(salt, argv[1], 2);
    
    // Incrementing the char array test from aaaa to zzzz
    // The magic number 488, 4x ASCII 'z'
    char test[5] = {97, 97, 97, 97};
    printf("%s\n", test);
    do {
        strcpy(test, inc_arr(test));
        printf("%s\n", test);
    } while (sum_arr(test) < 488);

    // Testing usage of crypt() 
    // Taken from http://stackoverflow.com/questions/15549591/how-to-use-crypt-method-in-linux
    //printf("%s\n", crypt(argv[1], salt));
    return 0;
}

// Increments char array by one and handles carrying to next member of array
// Taken from http://stackoverflow.com/questions/33102127/increment-char-arrays-int-values-by-1
char* inc_arr(char* test)
{
    for (int i = 3; i >= 0; i--)
    {
        test[i]++;
        if (test[i] > 122)
            test[i] = 97;
        else
            return test;
    }
    return test;
}

// Finds the sum of the members of a given array[4]
int sum_arr(char* test)
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
        sum += test[i];
    return sum;
}
