#ifndef SHELL_H_
#define SHELL_H_

#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10
//cd function
typedef struct
{
	char* func;
	char* args[MAX_PARAM_NUMBER];
	char* rig;
	int num_params;
}command_m;
int call_function(char* func,char*params[MAX_PARAM_NUMBER],int numb_of_params);
int is_builtin(char *func);
#endif
