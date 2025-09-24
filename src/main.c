#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <malloc.h>
#include <string.h>

void initialize(FILE*);
ssize_t isInitialized(FILE*);

int
main()
{
    FILE* initializedTime = fopen("time", "a+");

    printf("%zu\n",isInitialized(initializedTime));

    fclose(initializedTime);
}

void initialize(FILE* initializedTime)
{
    // Set the timer variable value to the current time of calander system (since epoch)
    // with the help of the time() function
    time_t timer = time(NULL);

    // Save the current time calculated with timer value with the help of ctime function
    char* buffer = ctime(&timer);
    // Write (re-write if already exists) to the text file we opened at first of the file
    fwrite(buffer, sizeof(char), strlen(buffer), initializedTime);
    printf("%s", buffer);
}

ssize_t isInitialized(FILE* filePtr)
{
    char* buffer = malloc(sizeof(char) * 256);
    size_t leng = 255;

    ssize_t status = getline(&buffer, &leng, filePtr);
    printf("buffer: %s, count: %zu\n", buffer, status);
    free(buffer);
    return status;
}
