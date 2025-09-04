#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


int
main()
{
    time_t* initialize = malloc(sizeof(int) * 256);
    time(initialize);
    char* buffer = malloc(sizeof(char) * 256);
    ctime_r(initialize, buffer);
    printf("Initialized at: %s\n", buffer);
    sleep(5);
    time(initialize);
    ctime_r(initialize, buffer);
    printf("At the end: %s\n", buffer);
}
