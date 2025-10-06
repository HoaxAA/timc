#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int task(char*);

int
main()
{
    char name[] = {"salam"};
    task(name);
}

int task(char* name)
{
    /* task function takes a name as a task and will look for .time file 
       to check whether any infromation about that task exists or not
       Input: Name of the task that the user wants to keep track of time
       Return: If the name of the task user entered was already submmited
       0 will be returned, if it was new, then 1 will be returned and if 
       program fail at some point it'll return -1 */
    FILE* fp = fopen(".time", "a+");

    char* buffer = malloc(sizeof(char) * 256);
    if (buffer == NULL) {
        perror("Failed to initialize buffer\n");
        return -1;
    }

    int exists = 0;
    while (fgets(buffer, 255, fp)) {
        if (buffer == name) {
            exists = 1;
            break;
        }
    }
    if (exists) {
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s:", name);
    return 1;
}
