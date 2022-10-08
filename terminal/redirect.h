#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void redirect_terminal();
void set_redirect(char* cmd, char** par, int *numParameters, char **args, char** envp);