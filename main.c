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
#include "./commandHandler/basics/basic.h"
#include "./nodes/node.h"

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
		if(strcmp (command, "newline") == 0){     }
			
		else if(strcmp (command, "hello") == 0){
			printf("Executing built-in [hello]");
			printf("\nHELLO\n"); 
		}  
		else if(strcmp (command, "exit") == 0){
			printf("Executing built-in [exit]\n");
			break;
		}
		else if(strcmp (command, "which") == 0){
			printf("Executing built-in [which]\n");
			which(para[0], pathlist);
		}
		else if( strcmp(command, "where") == 0){
			printf("Executing built-in [where]\n");
			where(para[0], pathlist);
		}
		else if( strcmp(command, "cd") == 0){
			printf("Executing built-in [cd]\n");
			if(cdaint % 2 == 1){
				prev = getcwd(NULL,0);   
				cd(para, numParameters, homedir,save);
			}else{
				save = getcwd(NULL,0);
			cd(para,numParameters,homedir,prev);
			}
			cdaint = cdaint + 1;
		}
		  //checks and runs pwd
  		else if(strcmp(command, "pwd") == 0){
   			printf("Executing built-in [pwd]\n");
   			printf("%s\n" , pwd);
       	}
		  //gets the first parameter of the passed command
  		else if(strcmp(command, "para") == 0){
   			printf("\n%s" , para[0]);
			printf("\n%d" , numParameters);
			printf("\n%s", command);
  		}
		else if(strcmp(command, "args") ==0){
			int iterArgs =0; 
			while(args[iterArgs] != NULL){
				printf("%s\n" , args[iterArgs]);
				iterArgs ++;
			}
  		}
		else if( strcmp(command, "ls") == 0){
		printf("Executing built-in [ls]");
			if(numParameters == 0){
				printls(pwd);}
			else if(numParameters == 1){
				printls(para[0]);
			}
		}
		  //check for kill command
		else if( strcmp(command, "kill") == 0){
			printf("Executing built-in [kill]");
			mykill(para, numParameters);
		}
		else if( strcmp(command, "pid") == 0){
			printf("Executing built-in [pid]\n");
			printf("%ld \n",(long)getpid());
		}
		else if( strcmp(command, "prompt") == 0){
      		if(numParameters == 0){
				printf("\tinput prompt prefix:");
				fgets(prompt, 64, stdin);
				prompt = strtok(prompt, " \n");
    		}
    		else
      			strcpy(prompt,para[0]);
  		}	
		else if( strcmp(command, "printenv") == 0){
    		printf("Executing built-in [printenv]\n");
    		printenv(envp,para,numParameters);
  		}
		else if( strcmp(command, "setenv") == 0){
			if(numParameters == 0){
				printenv(envp,para,numParameters);
			}
			else if(numParameters == 1){
				putenv(para[0]);
			}
			else if(numParameters == 2){
				setenv(para[0],para[1],1);
			}
			else
				printf("Error\n");
 		}
		  //watch user
  		else if(strcmp(command, "watchuser") == 0){
			if(numParameters > 2 || numParameters == 0){
				printf("Incorrect arguemnts for watchuser");
			}
			else{
				if(numParameters == 1){
					watchuser(para[0],0);
				}
				else if((numParameters == 2) && (strcmp(para[1],"off"))){
					watchuser(para[0],1);
				}
			}
		}
		else if(command[0] == '.' || command[0] == '/'){
      		absolute_command(command, args, envp, pid, numParameters);
			continue;
		}
		else {
			while (pathlist) {         // search for the command
				sprintf(search,"%s/%s", pathlist->element,command);
				//if command found will run the command
				if (access(search, X_OK) == 0) {
					printf("Executing [%s]" , search);
				
				//fork returns the parent id to the parent and for the child if the child is made
				pid = fork();
					if(pid == 0){
				//execvp will run command
				//note for later expand funtionality to include commands with no parameters
				//set_redirect(command, para, &numParameters, args, envp);
				execve(search, args, envp);
				}
				//waitpid with 0 as option so that the parent will
				//wait for the child to finish before any other
				//commands will be taken in
				else {                          /* parent */
					waitpid(pid, NULL, 0); 
				}
				printf("\n");
					break;
				}
				pathlist = pathlist->next;
				}
				//if the command is not found will return a message
				if(pathlist == NULL){
				printf("\n%s: Command not found.", command);
			}
		}
	}
	 //free mem here
	free(command);
	free(para);
	free(args);
	free(prompt);
	free(search);
	pthread_join(watchUse,NULL);
	return 0;
}