all : client server

client : client.c
	gcc -o client client.c -lm

server : server.c
	gcc -o server server.c -lm -pthread

clean:
	rm client server client.o server.o
