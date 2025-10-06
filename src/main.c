#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int task(char*);
double counter(char*);

int
main()
{
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
    if (fp == NULL) {
        perror("Failed to open .time file\n");
        return -1;
    }

    char* buffer = malloc(sizeof(char) * 256);
    if (buffer == NULL) {
        perror("Failed to allocate memory\n");
        fclose(fp);
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
        fclose(fp);
        free(buffer);
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s:", name);
    fclose(fp);
    free(buffer);
    return 1;
}

double counter(char* name)
{
    /* Save the time (since epoch) into .time.bak file with the task name
       if that task name already exists the current time would be subtracted
       to the saved time and it will be returned
       Input: Task name
       Return: if task didn't exist return value will be 0, if it exist it will be 
       subtracted value. If in any point of program any errors encounter 1 will returned */

    FILE* fp = fopen(".time.bak", "a+");
    if (fp == NULL) {
        perror("Failed to open .time.bak file\n");
        return 1;
    }

    char* buffer = malloc(sizeof(char) * 256);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        fclose(fp);
        return 1;
    }

    time_t now = time(NULL);

    while (fgets(buffer, 255, fp)) {
        if (buffer == name) {

        }
    }
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s:%ld:", name, now);
    return 0;
}
