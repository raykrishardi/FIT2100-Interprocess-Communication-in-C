CC = gcc
LFLAGS = -Wall

all: 26445549_pipeclient 26445549_pipeserver

26445549_pipeclient: 26445549_pipe.h
	$(CC) $(LFLAGS) 26445549_pipeclient.c -o 26445549_pipeclient

26445549_pipeserver: 26445549_pipe.c 26445549_pipe.h
	$(CC) $(LFLAGS) 26445549_pipeserver.c -o 26445549_pipeserver

clean:
	touch *