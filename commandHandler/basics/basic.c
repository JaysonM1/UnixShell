#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
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