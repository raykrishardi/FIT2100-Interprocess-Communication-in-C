/*
  Name: Ray Krishardi Layadi
  Student ID: 26445549
  Start date: 9 October 2017
  End date: 20 October 2017
  High-level description: Refer to the introduction section of the user documentation
*/

#include "26445549_pipe.c"

int main(void) {
  FILE *fifo; // Represent the FIFO
  char line[BUFFER_SIZE]; // Represent each line in the FIFO
  int argumentCounter; // Represent the number of command arguments (in this case, the command name itself is considered as an argument)
  char *command[BUFFER_SIZE]; // Represent command to be executed

  // Remove any previous FIFO
  unlink(FIFO_NAME);

  // Attempt to create FIFO with the specified name and permission
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  if (mkfifo(FIFO_NAME, FIFO_PERMISSION) < 0) {
    perror("server: mkfifo");
    exit(1);
  }

  // Attempt to open the FIFO for reading
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  if ((fifo = fopen(FIFO_NAME, "r")) == NULL) {
    perror("server: open FIFO");
    exit(1);
  }

  // Add a delay to the server to allow the client to finish its execution first
  // After the client has finished its execution then clear the screen
  usleep(100000); // Sleep for 0.1 second
  printf("\e[1;1H\e[2J"); // Clear the screen

  // Keep iterating until there is no more line to be read from the FIFO
  while (fgets(line, BUFFER_SIZE, fifo)) {
    argumentCounter = 0; // Reset the argument counter to 0 for each iteration
    getCommandFromLine(line, command, &argumentCounter); // Get command from FIFO
    printf("client: %s\n", line); // Print the command sent by the client
    executeCommand(command, argumentCounter); // Execute command from FIFO
    freeCommandArray(command, argumentCounter); // Deallocate memory allocation pointed to by element(s) in command array
  }

  printf("Press enter to exit the program..."); // Print the appropriate termination message
  fclose(fifo); // Close the FIFO
  exit(0); // Exit with status code of 0 (indicating no error has occured)
}