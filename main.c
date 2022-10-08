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
#include "./sigHandler/sigHandler.h"
#include "./commandHandler/readCommand.h"
#include "./terminal/redirect.h"
#include "./terminal/pipefunction.h"
#include "./terminal/output.h"

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

    //char command[100];
    char *command = calloc(PROMPTMAX, sizeof(char));
    int numParameters;


    //command and parameter variables
    char **args = calloc(MAXARGS, sizeof(char*));
    //char *para[20];
    char **para = calloc(MAXARGS, sizeof(char*));


    //external command variables
    //char search[128];
    char *search = calloc(PROMPTMAX, sizeof(char));
    signal(SIGINT, sigintHandler); 
    signal(SIGTSTP, sig_handlerSTP);
    signal(SIGTERM, sig_handlerTERM);


    //set pathlist
    pathlist = get_path();


    uid = getuid();
    password_entry = getpwuid(uid);               /* get passwd info */
    homedir = password_entry->pw_dir;

    //shell loop
     while(1){

        //update pathlist and current directory
        redirect_terminal();
        pathlist = get_path();
        pwd = getcwd(NULL, 0);
        //prompt msg to user
        printf("%s [%s]>", prompt, pwd);

          //read command that the user enters and parses the command
        read_command(command, para, &numParameters, args);
        set_redirect(command, para, &numParameters, args, envp);
     }
}