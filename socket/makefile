PARAM = 26445549_skt.c 26445549_skt.h
CC = gcc
LFLAGS = -Wall

all: 26445549_sktclient 26445549_sktserver

26445549_sktclient: $(PARAM)
	$(CC) $(LFLAGS) 26445549_sktclient.c -o 26445549_sktclient

26445549_sktserver: $(PARAM)
	$(CC) $(LFLAGS) 26445549_sktserver.c -o 26445549_sktserver

clean:
	touch *