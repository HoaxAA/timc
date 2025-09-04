#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int
main()
{
    FILE* timeData = fopen("time", "a+");

    char* buffer = malloc(sizeof(char) * 256);

    memcpy(buffer, "Salam", 5);
    
    //fwrite(buffer, sizeof(char), 5, timeData);
    char* readBuffer = malloc(256 * sizeof(char));
    printf("Before reading from file: %s\n", readBuffer);
    fread(readBuffer, sizeof(char), 10, timeData);
    printf("After reading the data: %s\n", readBuffer);
    free(readBuffer);
    free(buffer);
    fclose(timeData);
/*
    time_t* initialize = malloc(sizeof(int) * 256);
    time(initialize);
    char* buffer = malloc(sizeof(char) * 256);
    ctime_r(initialize, buffer);*/
}
