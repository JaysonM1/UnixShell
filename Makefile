main : main.c sshell.h
	gcc -o main main.c ./getPath/get_path.c -lpthread
clean :
	rm -f *.exe *~ *.o *.out
	rm sshell