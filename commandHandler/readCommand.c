#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./wildcard/wildcard.h"
#include "readCommand.h"
void read_command(char cmd[], char** par, int *numParameters, char **args){
    char line[1024];
    int count = 0;
    int iter = 0;
    int iterWild =0;
    char *token;
    char **wildcard;
    char *parCopy[20];
    //Read line and return a single string of the entered characters
    //fgets (line, 1024, stdin);
    if(fgets (line, 1024, stdin) == NULL){
        cmd = "newline";
        numParameters = 0;
        args[0] == 0;
        printf("%s1" , cmd);
        return;
    }
     //Pars the line to get the command and parameters
    //Get the first word for the command
    token = strtok(line, " \n");
    if (token == NULL){
        strcpy(cmd,"newline");
        numParameters = 0;
        args[0] == 0;
        return;
    } 

    strcpy(cmd, fixWildcard(token));
    args[count] = fixWildcard(token);

    while( token != NULL ) {
        token = strtok(NULL, " \n");
        par[count] = token;
        args[count+1] = token;
        count ++;
    }

    if( token == NULL){
        par[count] = NULL;
        args[count+1] = NULL;
    }

     //sets the total number of parameters
    count --;
    *numParameters = count;

    while(par[iter] != NULL){
        parCopy[iter] = par[iter];
        iter++;
    }
    
    parCopy[iter] = NULL;
    iter = 0;
    //loop to fix and wildcards in args
    if(count >= 1){
    count = 0;
    while(parCopy[iter] != NULL){
        if( strchr (parCopy[iter], '*') != NULL || strchr (parCopy[iter], '?') != NULL){
            wildcard = fixSingleWildcardArg(parCopy[iter]);
            iterWild =0;
            while(wildcard[iterWild] != NULL){
                par[count] = wildcard[iterWild];
                args[count+1] = wildcard[iterWild];
                count ++;
                iterWild ++;
            }
            iter ++;
        }
        else{
        count++;
        iter++;
        }
    }
    par[count] = NULL;
    args[count+1] = NULL;
    *numParameters = count;
    }
}