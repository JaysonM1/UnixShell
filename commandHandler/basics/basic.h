#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "../../getPath/get_path.h"

void which(char *command, struct pathelement *p);