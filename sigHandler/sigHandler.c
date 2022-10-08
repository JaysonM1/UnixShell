#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "sigInt.h"

void sigintHandler(int sig_num)
{  
    signal(SIGINT, sigintHandler);
    printf("\n");
}

void sig_handlerSTP(int sig_num){
	signal(SIGTSTP,sig_handlerSTP);
	printf("\n");
}
 
void sig_handlerTERM(int sig_num){
	signal(SIGTERM,sig_handlerTERM);
	printf("\n");
}