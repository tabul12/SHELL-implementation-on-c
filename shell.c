#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>

#include "help_m.h"
#include "cd_m.h"
#include "pwd_m.h"
#include "type_m.h"
#include "nice_m.h"
#include "ulimit_m.h"
#include "echo_m.h"
#include "kill_m.h"
#include "execute_m.h"
#include "export_m.h"
#include "redirect_m.h"
#include "shell.h"

#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define MAX_COMMANDS_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10
#define NUMBER_OF_DELIMITERS 3
char * functions[]={"?","cd","pwd1","exit","ulimit","nice","kill","type","echo","export"};
char * delimiters[]={"&&","||","|"};
char * cur_wor_dir;
int is_builtin(char *func)
{
    int i;
    for(i = 0; i<NUMBER_OF_FUNCTIONS; i++)
        if(strcmp(func,functions[i])==0)
            return 1;
    return -1;
}
int call_function(char* func,char*params[MAX_PARAM_NUMBER],int numb_of_params)
{
    if(is_builtin(func)==1)
    {
        //aq viwyebt ra brzanebebi shemovida
        if(strcmp(func,"?")==0)
            help();
        if(strcmp(func,"cd")==0)
            cd(params[0],cur_wor_dir);
        if(strcmp(func,"pwd")==0)
            pwd();
        if(strcmp(func,"ulimit")==0)
            ulimit_m(numb_of_params,params);
        
        if(strcmp(func,"nice")==0)
            nice_m(numb_of_params,params);
        if(strcmp(func,"type")==0)
            type(params[0]);
        if(strcmp(func,"echo")==0)
            echo_m(numb_of_params,params);
        if(strcmp(func,"kill")==0)
            kill_m(params,numb_of_params);
        if(strcmp(func,"export")==0)
            export_m(params[0]);
    }
    else  //ei unda vezebo programa
    {
        return execute_m(func,numb_of_params,params);
    }
    return -1;
}
void sigintHandler(int sig_num)
{
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler);
    printf("\nShell:~");
    fflush(stdout);
}

void sigstopHandler(int sig_num)
{
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigstopHandler);
    printf("\nShell:~");
    fflush(stdout);
}
int is_delimiter(char* d)
{
    int i;
    for(i=0; i<NUMBER_OF_DELIMITERS; i++)
    {
        if(strcmp(d,delimiters[i])==0)
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, sigintHandler);
    signal(SIGTSTP,sigstopHandler);
    cur_wor_dir=malloc(BUFF_SIZE);
    memset(cur_wor_dir,0,BUFF_SIZE);
    strcat(cur_wor_dir,"Shell:~");

    char* func;
    while(1)
    {
        int number_of_commands=0;
        command_m commands[MAX_COMMANDS_NUMBER];

        char*params[MAX_PARAM_NUMBER];
        printf("%s%s",cur_wor_dir,"$ ");
        
        char* tok=readline("");
        if(strcmp(tok,"")!=0)
            add_history(tok);
        else
            continue;
        
        int numb_of_params=0;
        while ((tok = strtok(tok, " ")) != NULL)
        {
            params[numb_of_params]=tok;  //take all params and save to array
            numb_of_params++;
            tok = NULL;
        }
        int i;
        int last_ind=0;
        int is_redirection=0;
        int is_pipeline=0;
        for(i=0;i<numb_of_params; i++)
        {
            if(strcmp(params[i],"<")==0 || strcmp(params[i],">")==0 || strcmp(params[i],">>")==0)
                is_redirection=1;
             if(strcmp(params[i],"|")==0)
                is_pipeline=1;
            if(is_delimiter(params[i])==1)
            {
                commands[number_of_commands].func=params[last_ind];
                commands[number_of_commands].rig=params[i];
                int j;
                for(j=last_ind+1; j<i; j++)
                    commands[number_of_commands].args[j-last_ind-1]=params[j];
                commands[number_of_commands].num_params=i-last_ind-1;
                last_ind=i+1;
                number_of_commands++;
            }
        }
        commands[number_of_commands].func=params[last_ind];
        commands[number_of_commands].rig=NULL;
        int j;
        for(j=last_ind+1; j<i; j++)
            commands[number_of_commands].args[j-last_ind-1]=params[j];

        commands[number_of_commands].num_params=numb_of_params-last_ind-1;
        number_of_commands++;

        if(strcmp(commands[0].func,"exit") == 0) break;

        if(is_redirection==1)
        {
            redirect_m(numb_of_params,params);
            continue;
        }
        if(is_pipeline==1)
        {
            char ** bu[MAX_COMMANDS_NUMBER];
            int h;
            for(h=0; h<number_of_commands; h++)
            {
                bu[h]=(char**)malloc((commands[h].num_params+2)*sizeof(char*));
                bu[h][0]=commands[h].func;
                int k=0;
                for(k=0; k<commands[h].num_params; k++)
                    bu[h][k+1]=commands[h].args[k];
                bu[h][commands[h].num_params+1]=NULL;
                
                //printf("%s\n", bu[h][commands[h].num_params+1]);
                //printf("%d%d\n",h,commands[h].num_params+1);
            }
            pipeline_m(number_of_commands,bu);
            continue;
        }
        int com=0;
        while(com<number_of_commands)
        {
            if(commands[com].rig==NULL)
            {
                call_function(commands[com].func,commands[com].args,commands[com].num_params);
                break;   
            }
            if(strcmp(commands[com].rig,"||")==0)
            {
                if(call_function(commands[com].func,commands[com].args,commands[com].num_params)==0)

                    break;
            }
            if(strcmp(commands[com].rig,"&&")==0)
            {
               if(call_function(commands[com].func,commands[com].args,commands[com].num_params)!=0)
                    break;
            }
            if(strcmp(commands[com].rig,"|")==0)
            {
                char* bu[MAX_COMMANDS_NUMBER];
                int ind;
                while(strcmp(commands[com].rig,"|")==0)
                {

                }
            }
            com++;
        }
        //call_function(func,params,numb_of_params);
    }
    return 0;
}