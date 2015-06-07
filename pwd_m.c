#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "pwd_m.h"


#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10

//print working directory
void pwd()
{
    char* buf=malloc(BUFF_SIZE);
    memset(buf,0,BUFF_SIZE);
    printf("%s\n",getcwd(buf,BUFF_SIZE));
    free(buf);
}
