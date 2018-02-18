all: ser.o cmds.o cli.o
	gcc ser.o cmds.o -lsocket -lnsl -o telnetserv 
	gcc cli.o -lsocket -lnsl -o telnetcli
ser.o: ser.c
	gcc -c ser.c
cli.o: cli.c
	gcc -c cli.c
cmds.o: cmds.c
	gcc -c cmds.c
clean:
	rm *.o
	rm telnetserv
	rm telnetcli
