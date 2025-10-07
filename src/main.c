#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int task(char*, double);
double counter(char*);

int
main()
{
    printf("Welcome\n");
    printf("What's the task you want to keep track of ?\n");
    char* buffer = malloc(sizeof(char) * 256);
    if (buffer == NULL) {
        perror("Failed to initialize memory\n");
        return 1;
    }
    scanf("%s", buffer);

    double total = counter(buffer);

    if (total != 1
            && total != 0) {
        task(buffer, total);
    }
}

int task(char* name, double total)
{
    /* task function takes a name as a task and will look for .time file 
       to check whether any infromation about that task exists or not
       Input: Name of the task that the user wants to keep track of time
       Return: If the name of the task user entered was already submmited
       0 will be returned, if it was new, then 1 will be returned and if 
       program fail at some point it'll return -1 */
    FILE* fp = fopen(".time", "r+");
    if (fp == NULL) {
        fp = fopen(".time", "a+");
        fclose(fp);
    }
    fp = fopen(".time", "r+");
    if (fp == NULL) {
        perror("Failed to open .time file\n");
        return -1;
    }

    char* buffer = malloc(sizeof(char) * 256);
    if (buffer == NULL) {
        perror("Failed to allocate memory\n");
        fclose(fp); return -1;
    }

    while (fgets(buffer, 255, fp)) {
        size_t length = strlen(buffer);
        char* token = strtok(buffer, ":");
        if (!strcmp(token, name)) {
            token = strtok(NULL, ":");
            total += strtol(token, NULL, 10);
            fseek(fp, -(length), SEEK_CUR);
            fprintf(fp, "%s:%f\n", name, total);
            fclose(fp);
            free(buffer);
            return 1;
        }
    }
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s:%f\n", name, total);
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
        char* token = strtok(buffer, ":");
        if (!strcmp(token, name)) {
            token = strtok(NULL, ":");
            time_t first = strtol(token, NULL, 10);
            fclose(fp);
            free(buffer);
            remove(".time.bak");
            return difftime(now, first);
        }
    }
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s:%ld", name, now);
    free(buffer);
    fclose(fp);
    return 0;
}
