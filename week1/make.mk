week1: client.o server.o
	gcc client.o server.o -o week1
server.o: server.c
	gcc -c server.c -o server.o
client.o: client.c
	gcc -c client.c -o client.o
clean:
	rm *.o week1