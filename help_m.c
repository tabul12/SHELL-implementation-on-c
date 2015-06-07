#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "help_m.h"


#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10

char * funclist[]={"?","cd","pwd","exit","ulimit","nice","kill","type","echo","export"};

//help
void help()
{
	printf("%s\n","HELP");
	printf("%s\n","Functions:");
	int i;
	for(i = 0; i<NUMBER_OF_FUNCTIONS; i++)
		printf("%s\n",funclist[i]);
}
