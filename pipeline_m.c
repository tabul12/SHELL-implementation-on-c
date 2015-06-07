#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "pipeline_m.h"

#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define MAX_COMMANDS_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10
#define NUMBER_OF_DELIMITERS 3

void pipeline_m(int numbercommands, char** bu[MAX_COMMANDS_NUMBER])
{
  int status;
  int i;
 
  //bu[0] = (char**)malloc(2*sizeof(char*));
  //bu[0][0]="ls";
  //bu[0][1]=NULL;

  //bu[1] =(char**) malloc(2*sizeof(char*));
  //bu[1][0]="sort";
  //bu[1][1]=NULL;

  //bu[2] = (char**)malloc(4*sizeof(char*));
  //bu[2][0]="cut";
  //bu[2][1]="-b";
  //bu[2][2]="1-5";
  //bu[2][3]=NULL;

  // make 2 pipes (cat to grep and grep to cut); each has 2 fds
  int num_pipes=numbercommands-1;
  int num_cond=numbercommands;
  int pipes[num_pipes*2];

  printf("%d\n",num_pipes);
  //printf("%s\n",bu[0][1]);
  //printf("%s\n",bu[1][1]);

  int l;
  for(l =0; l<num_pipes; l++)
    pipe(pipes+2*l);

  for(i=0; i<num_cond; i++)
  {
    int pid=fork();
    if(pid==0)
    {
      if(i==0)
        dup2(pipes[1], 1);
      else
        if(i==num_cond-1)
          dup2(pipes[i*2-2],0);
        else
        {
          dup2(pipes[i*2-2],0);
          dup2(pipes[i*2+1],1);
        }
      int k =0;
      for(k=0; k<num_pipes*2; k++)
        close(pipes[k]);

      execvp(bu[i][0],bu[i]);
    }
    else
      if(pid>0)
      {

      }
      else
        exit(1);
  }
  int k;
  for(k=0; k<num_pipes*2; k++)
        close(pipes[k]);

  for (i = 0; i < num_cond; i++)
    wait(&status);
}
