#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "../../getPath/get_path.h"
pthread_t watchUse;

void which(char *command, struct pathelement *p);

void where(char *command, struct pathelement *p);

void cd(char **para, int numArgs, const char *homedir,char *prev);

void printls(char *p);

void mykill(char **args, int argsLength);

void printenv(char **envp, char** args, int numArgs);

void watchuser(char* para,int off);

void absolute_command(char *command, char **argv, char **envp, pid_t pid, int numParameters );