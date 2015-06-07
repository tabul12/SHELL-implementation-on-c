#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "cd_m.h"

#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10

void cd(char* directory,char* cur_wor_dir)
{
    if(chdir((const char*)directory)!=0)
        printf("%s\n","error ocured during chdir");
    else
    {
    	strcat(cur_wor_dir,"/");
    	strcat(cur_wor_dir,directory);
    }
}
