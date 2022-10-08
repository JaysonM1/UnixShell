#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void redirect_output(char* filename, char **envp, char* symbol){
        int fid;

        if(strcmp(getenv("noclobber"), "0") == 0){
                if(strcmp(symbol, ">") ==0 || strcmp(symbol, ">&") == 0){
                        fid = open(filename, O_WRONLY|O_TRUNC);
                        close(1);
                        dup(fid);
                        if(strcmp(symbol, ">&") == 0){
                                dup2(fid, STDERR_FILENO);
                        }
                        close(fid);
                }
                if(strcmp(symbol, ">>") == 0 || strcmp(symbol, ">>&") == 0){
                        fid = open(filename, O_WRONLY|O_APPEND);
                        close(1);
                        dup(fid);
                        if(strcmp(symbol, ">>&") == 0){
                                dup2(fid, STDERR_FILENO);
                        }
                        close(fid);
                        printf("\n");

                }
                if(strcmp(symbol, "<") == 0){
                        fid = open(filename, O_RDONLY|O_TRUNC);
                        close(1);
                        dup(fid);
                        dup2(fid, STDIN_FILENO);
                        close(fid);
                }
        }
        else{
                if(open(filename, O_RDONLY) < 0){
                        perror("File exists");
                }
                else{
                        perror("File does not exist");
                }
        }

}