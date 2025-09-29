#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

long int firstInitialize(FILE*);
long int initializedTime(FILE*);
long int isInitialized(FILE*);
long int initialize();
double counter();


int
main()
{
}

long int firstInitialize(FILE* filePtr)
{
    // Set the timer variable value to the current time of calander system (since epoch)
    // with the help of the time() function
    time_t timer = time(NULL);

    // Save the current time to buffer 
    char* buffer = malloc(sizeof(char) * 256);
    if (buffer == NULL) { 
        perror("Failed to allocate memory\n");
    }
    // Since time returns a long int and our buffer data type is a string (char pointer) we need to convert it some how
    // with the help of sprintf we can wrtie number into our buffer
    sprintf(buffer, "%lu:", timer);
    // Write to the text file we opened at first of the file
    fwrite(buffer, sizeof(char), strlen(buffer), filePtr);

    return timer;
}

long int initializedTime(FILE* filePtr)
{
    // place the file pointer at the first of the file
    // beacuse "a+" mode set the pointer at the end of the file
    // if we set the origin to SEEK_SET and offset to ZERO, file pointer
    // will be placed at the start of the file
    fseek(filePtr, 0, SEEK_SET);

    char* buffer = malloc(sizeof(char) * 256); if (buffer == NULL) {
        perror("Failed to allocate memory\n");
        return 1;
    }
    size_t len = 0;

    ssize_t status = getline(&buffer, &len, filePtr);
    if (status == -1) {
        perror("Failed to read the line\n");
        return -1;
    }
    // convert buffer (string) into long int (same data type as time() function return value)
    long int time = strtol(buffer, NULL, 10);
    free(buffer);
    return time;
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

long int initialize()
{
    FILE* filePtr = fopen("time", "a+");
    if (filePtr == NULL) {
        perror("Failed to open the file\n");
        return -1;
    }

    // with the help of three functions we wrote, checks whether the 
    // file is empty or not
    // if yes -> read the first initialized time from the file
    // if no -> writes the current time of the calander system to "time" file
    long int time;
    if (isInitialized(filePtr)) {
        time = initializedTime(filePtr);
    }
    else {
        firstInitialize(filePtr);
    }

    fclose(filePtr);
    return time;
}

double counter()
{
    FILE* filePtr = fopen("time.bak", "a+");

    // pointer position for "a+" mode is clearly mentiond so just to
    // be sure we set the file pointer at the end of the file
    // to check whether time.bak exists or not

    fseek(filePtr, 0, SEEK_END);
    if (!ftell(filePtr)) {
        time_t now = time(NULL);
        char* buffer = malloc(sizeof(char) * 256);

        // wrtie current time to buffer to write it on time.bak
        sprintf(buffer, "%ld", now);
        fwrite(buffer, sizeof(char), 256, filePtr);
        free(buffer);
        fclose(filePtr);
        return 0;
    }
    fseek(filePtr, 0, SEEK_SET);
    char* buffer = malloc(sizeof(char) * 256);
    fread(buffer, sizeof(char), 255, filePtr);
    time_t start = strtol(buffer, NULL, 10);
    fclose(filePtr);
    free(buffer);
    time_t now = time(NULL);
    double diff = difftime(now, start);
    remove("time.bak");
    return diff;
}
