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
#include "basic.h"
#include "../../getPath/get_path.h"
#include "../../nodes/node.h"


void which(char *command, struct pathelement *p){
  char cmd[128];
  while (p) {         // WHICH
    sprintf(cmd,"%s/%s", p->element,command);
    if (access(cmd, X_OK) == 0) {
      printf("[%s]\n", cmd);
      break;
    }
    p = p->next;
  }
}


void where(char *command, struct pathelement *p){
  char cmd[128];
  while (p) {         // WHERE
    sprintf(cmd,"%s/%s", p->element,command);
    if (access(cmd, X_OK) == 0)
      printf("[%s]\n", cmd);
    p = p->next;
}
}




//cd changes the current directory
void cd(char **para, int numArgs, const char *homedir,char *prev){
	if(numArgs == 0){
    		chdir(getenv("HOME"));
  	}
  	else if(strcmp(para[0], "-") == 0){
      		chdir(prev);   
  	}
  	else{
		if(chdir(para[0]) == -1){
      			perror("Error: Could not change current directory. To many args.\n");
    		}
	}
}

void printls(char *p){
	DIR *dp;
	struct dirent *dirp;
	if(opendir(p) == NULL){
		perror("");
	}
	else{
	  dp = opendir(p);
	  while((dirp = readdir(dp)) != NULL)
                printf("%s\n", dirp->d_name);
          closedir(dp);
	}

}

void mykill(char **args, int argsLength){
	pid_t argPid;
	int arg1, arg2;
	const char *givenSignal;
	if (argsLength == 1){
		arg1 = atoi(args[0]);
		argPid = arg1;
		kill(arg1, SIGTERM);
	}
	else
	if (argsLength == 2){
		if(args[0][0] == '-'){
		givenSignal = &args[0][1];
		arg1 = atoi(givenSignal);
		arg2 = atoi(args[1]);
		argPid = arg2;
		kill(argPid, arg1);
		}
		else{
		perror("Invalid signal sent: must start with (-)");
		}
	}
	else{
		perror("Invalid number of args for kill");}
}

void printenv(char **envp, char** args, int numArgs){
	int i= 0;
	if(numArgs == 0){
		while(envp[i] != NULL){
			printf("%s\n", envp[i]);
			i++;
		}
	}
	else if(numArgs == 1){
		printf("%s=%s\n", args[0], getenv(args[0]));
	}
	else{
		printf("invalid parameters");
	}
}

pthread_mutex_t lock;
void* runWatch(void *arg){
        while(1){
		struct utmpx *up;
		setutxent();			/* start at beginning */
	 	pthread_mutex_lock(&lock);
	
                //pthread_mutex_lock(&lock);
		while (up = getutxent()){	/* get an entry */
    			if ( up->ut_type == USER_PROCESS ){	/* only care about users */
    				if(inLinkedList(up->ut_user)){
					printf("Logged in: %s", up->ut_user);
				}
				else
					printf("here");	

    			}
  		}


		sleep(20);
        }
        pthread_mutex_unlock(&lock);
}

int runsThrough = 0;
//watchuser
void watchuser(char* para,int off){
        if(off == 1){
                removeFromLinkedList(getNode(para));
                //turn off watch
        }
	if(runsThrough == 1){
		struct Node* use =(struct Node*) malloc(sizeof(struct Node));
		use->user = para;
		addToLinkedList(use);
	}
        else{
	     	//printf("here");
		runsThrough++;	
		struct Node* use =(struct Node*) malloc(sizeof(struct Node));
                use->user = para;	
		addToLinkedList(use);
		pthread_t tid[0];
                watchUse = pthread_create(&tid[0],NULL,runWatch,NULL);
                
                
        }
}


//absolute command runs executables that start with '.' or "/"
void absolute_command(char *command, char **argv, char **envp,
	       	pid_t pid, int numParameters ){
  if(access(command, X_OK) == 0){
	  pid = fork();
	  if(pid == 0){
		  printf("%d", execve(command, argv, envp));
	  }
	  else{
		  if(strcmp(argv[numParameters], "&") == 0){
			  waitpid(pid,NULL, WNOHANG);
		  }
		  else{	
			  waitpid(pid,NULL,0); 
		  }
	  }
	  printf("\n");
  } 
  else{
    perror("invalid command");
  }
}