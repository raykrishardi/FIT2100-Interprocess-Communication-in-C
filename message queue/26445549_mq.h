#ifndef MQ_H
#define MQ_H

// Constants
#define MSQ_KEY 34863 // Represent the message queue key
#define MSQ_SIZE 32 // Represent the message queue size
#define MSQ_PERMISSION 0666 // Represent the permission for the message queue (Read and Write for owner, group, and others)
#define BUFFER_SIZE 1024 // Represent the size of the buffer

// Libraries
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Data structure that represents a message buffer
struct msgbuf {
  long mtype;
  char mtext[MSQ_SIZE];
};

// Functions
void sendMessageType1FromInput(char *line, FILE *fp, struct msgbuf *mbuf, int msqid); // Send messages of type 1 which contains the unix commands to the message queue
void sendMessageType2(struct msgbuf *mbuf, int msqid); // Send messages of type 2 which indicates the end of the unix commands to the message queue
char *removeTrailingNewlineChar(char *line); // Remove trailing newline character from the message buffer text
void getCommandFromLine(char *line, char *command[BUFFER_SIZE], int *argumentCounter); // Get command from message queue
void spawnAndExecuteChildProcess(char *commandName, char *params[]); // Spawn a child process and execute the appropriate command
void executeCommand(char *command[BUFFER_SIZE], int argumentCounter); // Execute command from message queue
void freeCommandArray(char *command[BUFFER_SIZE], int argumentCounter); // Deallocate memory allocation pointed to by element(s) in command array

#endif