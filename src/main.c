#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <malloc.h>
#include <string.h>

void initialize(FILE*);
ssize_t initializedTime(FILE*);
long int isInitialized(FILE*);

int
main()
{
    FILE* filePtr = fopen("time", "r+");

    // with the help of three functions we wrote, checks whether the 
    // file is empty or not
    // if yes -> read the first initialized time from the file
    // if no -> writes the current time of the calander system to "time" file
    if (isInitialized(filePtr)) {
        initializedTime(filePtr);
    }
    else {
        initialize(filePtr);
    }

    fclose(filePtr);
}

void initialize(FILE* filePtr)
{
    // Set the timer variable value to the current time of calander system (since epoch)
    // with the help of the time() function
    time_t timer = time(NULL);

    // Save the current time calculated with timer value with the help of ctime function
    char* buffer = ctime(&timer);
    // Write (re-write if already exists) to the text file we opened at first of the file
    fwrite(buffer, sizeof(char), strlen(buffer), filePtr);
    printf("%s", buffer);
}

ssize_t initializedTime(FILE* filePtr)
{
    char* buffer = malloc(sizeof(char) * 256);
    size_t leng = 255;

    ssize_t status = getline(&buffer, &leng, filePtr);
    free(buffer);
    return status;
}

long int isInitialized(FILE* filePtr)
{
    // fseek sets the reading pointer where we need, in our case 
    // we want to check wheter the file is empty or not, so we want
    // to put that pointer at the end of the file (SEEK_END)
    // and with the help of ftell we read the total number of bytes
    // from the begging of the file until where our pointer is (end of the file)
    // if the file is empty so ftell will return 0 otherwise it will return any other number
    
    fseek(filePtr, 0, SEEK_END);
    long int position = ftell(filePtr);
    return position;
}
