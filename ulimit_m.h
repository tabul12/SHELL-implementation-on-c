#ifndef ULIMIT_H_
#define ULIMIT_H_

#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20
#define NUMBER_OF_FUNCTIONS 10

void getLimits(char* line[]);
void setLimits(char* line[]);
void ulimit_m(int numb_of_params,char*params[MAX_PARAM_NUMBER]);
#endif