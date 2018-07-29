#include "26445549_pipe.h"

// Function that removes trailing newline character from each line in FIFO ("line" variable) as a result of the fgets()
// 1. Replace the newline character with null character if there is a newline character at the end of the "line" variable
char *removeTrailingNewlineChar(char *line) {
  size_t lineLength = strlen(line);
  if (line[lineLength - 1] == '\n')
    line[lineLength - 1] = '\0';
  return line;
}

// Function that gets command from FIFO (assign the command and its argument(s) as element(s) of the command array)
void getCommandFromLine(char *line, char *command[BUFFER_SIZE], int *argumentCounter) {
  int counter = 0; // Counter to keep track of the number of command and its argument(s) to be assigned as element(s) of the command array
  char tmpLine[BUFFER_SIZE]; // Temporary variable that also holds the selected line in FIFO ("line" variable)
  char *token; // Represent each substring of the selected line in FIFO ("line" variable) delimited/separated by " "

  // Copy the content of the selected line in FIFO ("line" variable) to the temporary variable ("tmpLine" variable)
  // Temporary variable is required because when using strtok(), the content of the given string will get modified
  // Therefore, the temporary variable is required to preserve the original content of the string
  strcpy(tmpLine, removeTrailingNewlineChar(line));

  // Get a substring of the selected line in FIFO delimited/separated by " "
  // Keep iterating until there is no more substring to be retrieved from the selected line
  token = strtok(tmpLine, " ");
  while (token != NULL) {
    command[counter] = (char *) malloc(BUFFER_SIZE + 1); // Allocate memory in heap to store the substring
    strcpy(command[counter], token); // Copy the content of the substring to the appropriate element in the command array
    counter++; // Increment the counter accordingly
    *argumentCounter += 1; // Increment the argument counter accordingly
    token = strtok(NULL, " "); // Get the next substring
  }
}

// Function that spawns a child process and execute the appropriate command
void spawnAndExecuteChildProcess(char *commandName, char *params[]) {
  pid_t pid; // Represent the process ID of the child process

  // Check whether fork() successfully created a child process or not
  // If fork() failed to create a child process then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  // If fork() successfully created a child process then the child process will execute the appropriate command with the corresponding parameters
  // If fork() successfully created a child process then the parent process will wait for the termination of the child process
  if ((pid = fork()) < 0) {
    perror("fork error");
    exit(1);
  }
  else if (pid == 0) {
    printf("server: ");
    fflush(stdout); // Need to flush the standard output in order for the printf("server: ") to be displayed properly
    execvp(commandName, params);
    exit(0);
  }
  else {
    wait(NULL);
  }
}

// Function that executes command from FIFO
void executeCommand(char *command[BUFFER_SIZE], int argumentCounter) {

  // Check the number of command arguments (in this case, the command name itself is considered as an argument)
  // If the number of command arguments is 0 (i.e. no command given (i.e. empty line in commands.txt))
  //    then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  // If the number of command arguments is 1 (i.e. command with no parameters (e.g. "date" command))
  //    then spawn a child process to execute the given command
  // If the number of command arguments is greater than 1 (i.e. command with parameters (e.g. ls -l commands.txt))
  //    then spawn a child process to execute the given command with the corresponding parameters
  if (argumentCounter == 0) {
    printf("Command must not be empty...\n");
    exit(1);
  }
  else if (argumentCounter == 1) {
    char *commandName = command[0]; // Get the command name
    char *params[] = {commandName, 0}; // Indicate that there is no parameters for the command (e.g. executing "date" command)
    spawnAndExecuteChildProcess(commandName, params); // Spawn a child process and execute the given command
  }
  else {
    char *commandName = command[0]; // Get the command name

    // Represent the parameters for the given command
    char *params[argumentCounter+1]; // +1 to accomodate for 0 or NULL at the end of the parameters array

    // Loop through all command arguments and assign the appropriate command and its parameters to the parameters array
    for (int i = 0; i < argumentCounter; i++) {
      params[i] = command[i];
    }
    params[argumentCounter] = 0; // Assign 0 or NULL at the end of the parameters array

    // Spawn a child process and execute the given command with the corresponding parameters
    spawnAndExecuteChildProcess(commandName, params);
  }

}

// Function that deallocates memory allocation pointed to by element(s) in command array
// 1. Only deallocate memory allocation if the element in command array is not NULL (i.e. contains a memory address)
// 2. Assign NULL to char pointer that has been deallocated
void freeCommandArray(char *command[BUFFER_SIZE], int argumentCounter) {
  for (int i = 0; i < argumentCounter; i++) {
    if (command[i] != NULL) {
      free(command[i]);
      command[i] = NULL;
    }
  }
}