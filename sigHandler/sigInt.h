#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void sigintHandler(int sig_num);
void sig_handlerSTP(int sig_num);
void sig_handlerTERM(int sig_num);