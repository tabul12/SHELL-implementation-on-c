#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "redirect_m.h"
#include "echo_m.h"
#include "shell.h"

#define BUFF_SIZE 1024
#define COMMAND_COUNT 5
#define NUMBER_OF_FUNCTIONS 10


#define MAX_PARAM_NUMBER 20

int parse(int params_count, char * params[], char * commands[]);
int safe_increment(int i);
void redirect_stdout(char *program, char* redirect_type, char *file_name);	//prog > file, prog >> file
void redirect_stdin(char *program, char* redirect_type, char *file_name);	//progr < file
void redirect_stdin_stdout(char *program1, char* redirect_type1, char *file_name_in, char* redirect_type2 , char *file_name_out); //prog < file > file, progr < file >> file

char ** PARAMS;
int N_params;
void redirect_m(int numb_of_params, char* params[]) {
	char * commands[COMMAND_COUNT];
	PARAMS=params;
	N_params=numb_of_params;
	int pars_res = parse(numb_of_params, params, commands);
	if (pars_res != 0) {
		printf("error parsing 'redirect' comand.\n");
		return;
	}
// ---------------------------------------------------------
	if (strcmp(commands[1], ">") == 0 || strcmp(commands[1], ">>") == 0) {
		redirect_stdout(commands[0], commands[1], commands[2]);
	} else {
		if (strcmp(commands[1], "<") == 0 && strcmp(commands[3], "\0") == 0) {
			redirect_stdin(commands[0], commands[1], commands[2]);
		} else if (strcmp(commands[1], "<") == 0 && (strcmp(commands[3], ">") == 0 || strcmp(commands[3], ">>") == 0)) {
			redirect_stdin_stdout(commands[0], commands[1], commands[2], commands[3], commands[4]);
		}
	}
} 
void create_arguments(char *args[], char *program) {
	char * tok = strtok(program, " ");
	args[0] = tok;
	int i = 1;
	while ((tok = strtok(NULL, " ")) != NULL) {
    	args[i++] = tok; 
    }
    args[i] = NULL;
}

void redirect_stdin_stdout(char *program, char* redirect_type1, char *file_name_in, char* redirect_type2 , char *file_name_out) {
	int status;
	//exec command
	pid_t pID = fork();
   	if (pID == 0) {                // child
   		int out_file_fd;
		if (strcmp(redirect_type2, ">") == 0) {
			out_file_fd = open(file_name_out, O_RDWR|O_CREAT|O_TRUNC, S_IRWXU|S_IXUSR|S_IRWXG|S_IXGRP|S_IRWXO|S_IXOTH);
	    	

		} else if (strcmp(redirect_type2, ">>") == 0) {
			out_file_fd = open(file_name_out, O_RDWR|O_CREAT|O_APPEND, S_IRWXU|S_IXUSR|S_IRWXG|S_IXGRP|S_IRWXO|S_IXOTH);
		}
		if (-1 == out_file_fd) { 
			printf("error opening file:%s\n", file_name_out); 
			exit(4);
		}
		//redirect stdout to file 
		if (dup2(out_file_fd, fileno(stdout)) == -1) { 
			printf("error redirectiong stdout to file\n");
			exit(5); 
		}

   		char * args[MAX_PARAM_NUMBER];
   		strcat(program, " ");
   		strcat(program, file_name_in);
   		create_arguments(args, program);
   		
    	if(execvp(args[0],args)==-1)
    		printf("%s\n","cannot extec");

    	fflush(stdout); 
		close(out_file_fd);
    	exit(0);
   	}
   	else if (pID < 0) {            // failed to fork
   	
        exit(1);
        // Throw exception
   	} else {                                  // parent
   	
     	// Code only executed by parent process
   		pID = wait(&status);
      	last_process_status_code = status;

   	}
}
void redirect_stdin(char *program, char* redirect_type, char *file_name) {
	printf("redirectiong stdin........\n");
	int status;
	//exec command
	pid_t pID = fork();
   	if (pID == 0) {                // child
   		

   		char * args[MAX_PARAM_NUMBER];
   		strcat(program, " ");
   		strcat(program, file_name);
   		create_arguments(args, program);
    	if(execvp(args[0],args)==-1)
    		printf("%s\n","cannot extec. ");

    	exit(0);
   	}
   	else if (pID < 0) {            // failed to fork
   	
        exit(1);
        // Throw exception
   	} else {                                  // parent
   	
     	// Code only executed by parent process
   		pID = wait(&status);
      	last_process_status_code = status;

   	}
}



void redirect_stdout(char *program, char* redirect_type, char *file_name) {
	int status;
	//exec command
	pid_t pID = fork();
   	if (pID == 0) {                // child
   		int out_file_fd;
		if (strcmp(redirect_type, ">") == 0) {
			out_file_fd = open(file_name, O_RDWR|O_CREAT|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO);
	   
		} else if (strcmp(redirect_type, ">>") == 0) {
			out_file_fd = open(file_name, O_RDWR|O_CREAT|O_APPEND, S_IRWXU|S_IRWXG|S_IRWXO);
		}
		if (-1 == out_file_fd) { 
			printf("error opening file:%s\n", file_name); 
			exit(4);
		}
		//redirect stdout to file 
		if (dup2(out_file_fd, fileno(stdout)) == -1) { 
			printf("error redirectiong stdout to file\n");
			exit(5); 
		}
   		char * args[MAX_PARAM_NUMBER];
   		create_arguments(args, program);

   		if(is_builtin(program)==1)
   		{

			char * tem[MAX_PARAM_NUMBER];
			tem[0]=PARAMS[1];
   			call_function(PARAMS[0],tem,N_params-1);
   		}
   		else
    		if(execvp(args[0],args)==-1)
    			printf("%s\n","cannot extec");

    	fflush(stdout); 
		close(out_file_fd);
    	exit(0);
   	}
   	else if (pID < 0) {            // failed to fork
   	
        exit(1);
        // Throw exception
   	} else {                                  // parent
   	
     	// Code only executed by parent process
   		pID = wait(&status);
      	last_process_status_code = status;
   	}
	
}

//remove last characher " "
void my_sbstr1(char * s) {
	int l = strlen(s) - 1;
    int c = 0;
 	char *sub = (char *)malloc(l + 1);

    while (c < l) {
       sub[c] = s[c];
       c++;
    }
    sub[c] = '\0';
    
    strcpy(s, sub);
}

int parse(int params_count, char * params[], char * commands[]) {
	int i;
	for (i = 0; i < COMMAND_COUNT; i++) {
		commands[i] = malloc(BUFF_SIZE);
		memset(commands[i],0,BUFF_SIZE);
	}
	char buf[2];
	int index = -1;
	for (i = 0; i < params_count; i++) {
		if (strcmp(params[i], "<")==0 || strcmp(params[i], ">")==0 || strcmp(params[i], ">>")==0) {
			index = safe_increment(index);
			strcat(commands[index], params[i]);
			index = safe_increment(index);
		} else {
			if (index == -1) {
				index = safe_increment(index);
			}
			strcat(commands[index], params[i]);
			strcat(commands[index], " ");
		}
	}

	if (strlen(commands[2]) > 1) {
		my_sbstr1(commands[2]);	
	}
	
	if (strlen(commands[4]) > 1) {
		my_sbstr1(commands[4]);	
	}


	//check command correctness(correct commands: cmd > file, cmd >> file, cmd < file, cmd < file > file)
	if (strcmp(commands[1], ">") != 0 && strcmp(commands[1], ">>") != 0 && strcmp(commands[1], "<") != 0) return -1;
	if (strcmp(commands[1], ">") == 0 || strcmp(commands[1], ">>") == 0) {
		if (strcmp(commands[3], "\0") != 0) return -1;
	}
	if (strcmp(commands[1], "<") == 0 ) {
		if (strcmp(commands[3], "\0") != 0 && strcmp(commands[3], ">") != 0 && strcmp(commands[3], ">>") != 0) return -1;
	}
	return 0;
}

int safe_increment(int i) {
	if (i+1 >= COMMAND_COUNT) {
		//printf("error while parsing 'redirect' parameters\n");
		return i;
	}
	return i+1;
}