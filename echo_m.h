#ifndef ECHO_H_
#define ECHO_H_

#define MAX_PARAM_NUMBER 20

extern int last_process_status_code;


//echo function
void echo_m(int numb_of_params, char*params[MAX_PARAM_NUMBER]);

#endif