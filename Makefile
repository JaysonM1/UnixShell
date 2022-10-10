main : main.c sshell.h
	gcc -o main main.c ./getPath/get_path.c ./commandHandler/readCommand.c ./commandHandler/wildcard/wildcard.c ./sigHandler/sigHandler.c ./terminal/output.c ./terminal/pipefunction.c ./terminal/redirect.c ./commandHandler/basics/basic.c ./nodes/node.c -lpthread
clean :
	rm -f *.exe *~ *.o *.out
	rm sshell