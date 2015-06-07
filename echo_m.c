#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#include "echo_m.h"

#define MAX_PARAM_NUMBER 20

int last_process_status_code = 0;

char * my_sbstr(char * s, int p, int l);

void echo_m(int numb_of_params,char*params[MAX_PARAM_NUMBER]){

	int i;
	for (i = 0; i < numb_of_params; i++) {
		if (params[i][0] == '$') {
			if (strlen(params[i]) < 2) {
				printf("$");
			} else if (params[i][1] != '?') {
				char * var_name =  my_sbstr(params[i], 1, strlen(params[i]));
				char * var_value = getenv(var_name);
				printf("%s ", var_value);
			} else {
				printf("%d ", last_process_status_code);
			}
		} else {
			printf("%s ", params[i]);
		}
		
	}
	printf("%s\n","");
}

char * my_sbstr(char * s, int p, int l) {
    int c = 0;
 	char *sub = (char *)malloc(l+1);

    while (c < l) {
       sub[c] = s[p+c];
       c++;
    }
    sub[c] = '\0';
    return sub;
}