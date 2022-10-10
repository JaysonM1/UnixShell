#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include "basic.h"
#include "../../getPath/get_path.h"


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