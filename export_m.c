#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "export_m.h"
#define BUFF_SIZE 1024
#define MAX_PARAM_NUMBER 20

void split(char * str, char * key_value[]);

void export_m(char * param) {
	char * key_value[2];
	split(param, key_value);

	if (strlen(key_value[1]) == 0) {
		key_value[1] = getenv(key_value[0]);
	}


	int res = setenv(key_value[0], key_value[1], 1);

	if (res != 0) {
		printf("%s\n", "error while setting enviroment variable.");
	}
}

void split(char * str, char * key_value[]) {
	key_value[0] =malloc(BUFF_SIZE);
	memset(key_value[0],0,BUFF_SIZE);

	key_value[1] = malloc(BUFF_SIZE);
	memset(key_value[1],0,BUFF_SIZE);

	char buf[2];


	int i;
	int exist = 0;
	for (i = 0; i < strlen(str); i++) {
		if (exist == 1) {
			buf[0] = str[i];
			buf[1] = '\0';
			strcat(key_value[1], buf);
		} else {
			if (str[i] == '=') {
				exist = 1;
				continue;
			} else {
				buf[0] = str[i];
				buf[1] = '\0';
				strcat(key_value[0],buf);
			}
		}
	}

}

