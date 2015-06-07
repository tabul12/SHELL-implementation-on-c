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

#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10


void nice_m(int numb_of_params,char* params[MAX_PARAM_NUMBER]){
	int status;
	char* program_name=params[2];
	char* path_to_program=getPath_m(program_name);
	
	char* args[MAX_PARAM_NUMBER];
	int i;
	for(i= 0; i<MAX_PARAM_NUMBER; i++)
		args[i]=NULL;

	args[0]=path_to_program;
	for(i = 1; i<numb_of_params-2; i++)
		args[i]=params[i+2];

	pid_t pID = fork();
   	if (pID == 0)                // child
   	{
   		if(nice(atoi(params[1]))<0)
   			printf("%s\n","errororor");
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

   		//if ( WIFEXITED(status) ){
      	//	printf("Parent: Child exited with status: %d\n", WEXITSTATUS(status));
      	//}
   	}
}
