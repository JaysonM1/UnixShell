#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <wordexp.h>
#include <utmpx.h>
#include <pthread.h>
#include "sshell.h"


int main(int argc, char **argv, char **envp){
    //Shell variables:
    char *prompt = calloc(PROMPTMAX, sizeof(char));
    char *pwd;
    setenv("noclobber", "0", 1);
    printf("Hello World\n");
    return 0;
}