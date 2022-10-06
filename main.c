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
    
    int uid, i, status, argsct, go = 1;
    struct passwd *password_entry;
    char *homedir;
    struct pathelement *pathlist;

    char *prev = getcwd(NULL,0);
    char *save = getcwd(NULL,0);
    int cdaint=1;



    //command and parameter variables
    char **args = calloc(MAXARGS, sizeof(char*));
    //char *para[20];
    char **para = calloc(MAXARGS, sizeof(char*));

    //command and parameter variables
    char **args = calloc(MAXARGS, sizeof(char*));
    //char *para[20];
    char **para = calloc(MAXARGS, sizeof(char*));

    
    return 0;
}