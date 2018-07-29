#ifndef PIPE_H
#define PIPE_H

// Constants
#define FIFO_NAME "myfifo" // Represent the name of the FIFO
#define FIFO_PERMISSION 0666 // Represent the permission for the FIFO (Read and Write for owner, group, and others)
#define BUFFER_SIZE 1024 // Represent the size of the buffer

// Libraries
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Functions
char *removeTrailingNewlineChar(char *line); // Remove trailing newline character from the FIFO
void getCommandFromLine(char *line, char *command[BUFFER_SIZE], int *argumentCounter); // Get command from FIFO
void spawnAndExecuteChildProcess(char *commandName, char *params[]); // Spawn a child process and execute the appropriate command
void executeCommand(char *command[BUFFER_SIZE], int argumentCounter); // Execute command from FIFO
void freeCommandArray(char *command[BUFFER_SIZE], int argumentCounter); // Deallocate memory allocation pointed to by element(s) in command array

#endif