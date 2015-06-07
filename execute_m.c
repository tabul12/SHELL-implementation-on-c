#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "nice_m.h"
#include "type_m.h"
#include "echo_m.h"
#include "execute_m.h"

#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10

int execute_m(char* function,int numb_of_params,char* params[MAX_PARAM_NUMBER]){
	int status;
	
	char* path_to_program=getPath_m(function);
	if(path_to_program==NULL)
  {
    printf("%s\n","command not found");
    return -1;
  }
  printf("%s\n",function);

	char* args[MAX_PARAM_NUMBER];
	int i;
	for(i= 0; i<MAX_PARAM_NUMBER; i++)
		args[i]=NULL;

	args[0]=path_to_program;
	for(i = 1; i<=numb_of_params; i++)
		args[i]=params[i-1];

	pid_t pID = fork();
   	if (pID == 0)                // child
   	{
    	if(execv(args[0],args)==-1)
    		printf("%s\n","cannot extec");
    	exit(0);
   	}
   	else if (pID < 0)            // failed to fork
   	{
        exit(1);
        // Throw exception
   	}
   	else                                   // parent
   	{
     	// Code only executed by parent process
   		pID = wait(&status);
      last_process_status_code=status;
      return status;
   	}
}