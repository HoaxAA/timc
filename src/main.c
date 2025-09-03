#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <malloc.h>

int
main()
{
    time_t* initialize = malloc(sizeof(int) * 256);
    time(initialize);
    //printf("%lu\n", *initialize);
    char* buffer = malloc(sizeof(char) * 256);
    ctime_r(initialize, buffer);
    printf("initialized time: %s\n", buffer);

    sleep(3);
    time_t current = time(NULL);
    ctime_r(&current, buffer);
    printf("elapsed time: %s\n", buffer);

    time_t diff = difftime(current, *initialize);

    printf("Total time spent: %lu seconds\n", diff);

    free(buffer);
    free(initialize);
}
