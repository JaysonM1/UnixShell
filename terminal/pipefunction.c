#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


//function to handle ipc
void pipeFunction(char **para){
	   int pipefd[2], bytes;
           pid_t cpid;
           char buf;
           char *eString;
		char readBuffer[80];

	    int pfds[2];

    pipe(pfds);

    if (!fork()) {
        close(1);       
        dup(pfds[1]);   
        close(pfds[0]); 
        execlp("ls", "ls", NULL);
    } else {
        close(0);       
        dup(pfds[0]);   
        close(pfds[1]); 
      	execlp("wc", "wc", "-l", NULL);
    }    
}