#ifndef SKT_H
#define SKT_H

// Constants
#define SOCKET_NAME "mysocket" // Represent the name of the socket
#define BACKLOG 15 // Represent the number of pending connection requests allowed
#define BUFFER_SIZE 1024 // Represent the size of the buffer

// Libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Functions
char *removeTrailingNewlineChar(char *line); // Remove trailing newline character from the socket
void getCommandFromLine(char *line, char *command[BUFFER_SIZE], int *argumentCounter); // Get command from socket
void spawnAndExecuteChildProcess(char *commandName, char *params[]); // Spawn a child process and execute the appropriate command
void executeCommand(char *command[BUFFER_SIZE], int argumentCounter); // Execute command from socket
void freeCommandArray(char *command[BUFFER_SIZE], int argumentCounter); // Deallocate memory allocation pointed to by element(s) in command array

#endif