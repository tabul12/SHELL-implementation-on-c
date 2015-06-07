#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sig.h"
#include "kill_m.h"
// viyeneb sig.h da sig.c filebs romlebic flagebis char* mnishvnelobistvis shesabamisi int mnishvnelobis minichebisatvis
void kill_m(char* line[],int numParams){
    int temp = 0;
    int signalID = 15;
    if(strcmp(line[temp],"-l") == 0){
        int i;
        for(i = 1; i < 64; i++){
            printf("%d",i);
            printf("%s",") " );
            printf("%s",signal_number_to_name(i));
            printf("%s"," ");
            if((i%5)==0){
                printf("%s\n","");
            }
        }
        return;
    }
    if(strcmp(line[temp],"-s") == 0){
        temp++;
        char* sigName = line[temp];
        temp++;
        char* curr = malloc(64);
        memcpy(curr,sigName,3);
        if(strcmp(curr,"SIG") == 0){
            sigName = sigName + 3;
        }
        signalID = signal_name_to_number(sigName);
    } 

    char c = *line[temp];
    if(c == '-'){
        c = *((char*)line[temp] + 1);
        if('1'<=c && c<='9'){
            char *p = malloc(64);
            strcpy(p,(char*)line[temp] + 1);
            temp++;
            int curr = atoi(p);
            if(1<=curr && curr<=64){
                signalID = curr;
            }
        }else{
            char* sigName = line[temp];
            sigName = sigName + 1;
            temp++;
            char* curr = malloc(64);
            memcpy(curr,sigName,3);
            if(strcmp(curr,"SIG") == 0){
                sigName = sigName + 3;
            }
            signalID = signal_name_to_number(sigName);
        }
    }
    if(signalID<0){
        printf("%s\n","failed");
        return;
    }
    int i;
    for(i = temp; i < numParams; i++){
        int pid = atoi(line[i]);
        if(pid>0 || pid<-1){
            kill(pid,signalID);
        }
    } 
}
