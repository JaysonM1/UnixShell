#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "output.h"
#include "pipeFunction.h"

void redirect_terminal(){
    int fid = open("/dev/tty", O_WRONLY);
    close(1);
    dup(fid);
    dup2(fid, STDERR_FILENO);
    //dup2(fid, STDIN_FILENO);
    close(fid);
}

void set_redirect(char* cmd, char** par, int *numParameters, char **args, char** envp){
        char symbols[7][5] = {">" , ">&", ">>", ">>&", "<", "|","|&"};
        int numPara = *numParameters;
        if(numPara > 1){
        for(int i = 0; i < 7; i++){
                //printf("%s\n", symbols[i]);
		if((strcmp("|",args[numPara-1]) == 0) || (strcmp("|&",args[numPara-1]) == 0)){
			pipeFunction(args);
				
		}
		else
           	if(strcmp(symbols[i], args[numPara-1]) == 0){
                        redirect_output(args[numPara], envp, args[numPara-1]);
                        for(int x = numPara-1; x <= numPara; x++){
                                args[x] = NULL;
                                par[x-1] = NULL;
                        }
                        *numParameters = numPara-2;
                        return;
                }
        }
        }
        return;

}