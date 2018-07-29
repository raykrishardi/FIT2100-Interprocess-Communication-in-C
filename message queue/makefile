PARAM = 26445549_mq.c 26445549_mq.h
CC = gcc
LFLAGS = -Wall

all: 26445549_mqclient 26445549_mqserver

26445549_mqclient: $(PARAM)
	$(CC) $(LFLAGS) 26445549_mqclient.c -o 26445549_mqclient

26445549_mqserver: $(PARAM)
	$(CC) $(LFLAGS) 26445549_mqserver.c -o 26445549_mqserver

clean:
	touch *