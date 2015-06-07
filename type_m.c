#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "type_m.h"

#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10

char * funcs[]={"?","cd","pwd","exit","ulimit","nice","kill","type","echo","export"};

char* getPath_m(char * name)
{
    char * pp=getenv("PATH");
    char * directories=malloc(BUFF_SIZE);
    memset(directories,0,BUFF_SIZE);
    memcpy(directories,pp,strlen(pp));

    while ((directories = strtok(directories, ":")) != NULL)
    {
        DIR * dirp = opendir(directories);
        if (dirp == NULL)
            continue;
        int len = strlen(name);
        struct dirent * dp;
        while ((dp = readdir(dirp)) != NULL) {
            if (strcmp(dp->d_name, name) == 0) {
                char * ret=malloc(BUFF_SIZE);
                memset(ret,0,BUFF_SIZE);
                sprintf(ret,"%s/%s",directories,name);
                return ret;
            }
        }
        (void)closedir(dirp);
        directories = NULL;
    }
    return NULL;
}
void type(char * name)
{
    int i;
    for(i = 0; i<NUMBER_OF_FUNCTIONS; i++)
        if(strcmp(funcs[i],name)==0)
        {
            printf("%s is builtin function\n",name);
            break;
        }
    char * pathF=getPath_m(name);
    if(pathF !=NULL)
    {
        printf("%s\n","Path to Program:");
        printf("%s\n",pathF);
    }
}
