/*
  Name: Ray Krishardi Layadi
  Student ID: 26445549
  Start date: 9 October 2017
  End date: 20 October 2017
  High-level description: Refer to the introduction section of the user documentation
*/

#include "26445549_skt.c"

int main(void) {
  // Represent:
  // sock -> Socket for accepting other connection requests from the client
  // nsock -> Socket for communicating with the client process
  // n -> The number of bytes stored in the socket
  int n, sock, nsock;
  socklen_t len; // Represent the length of the server socket name/address
  struct sockaddr_un name; // Represent the server socket name/address
  char line[BUFFER_SIZE]; // Represent each line in the socket
  int argumentCounter; // Represent the number of command arguments (in this case, the command name itself is considered as an argument)
  char *command[BUFFER_SIZE]; // Represent command to be executed


  // Attempt to create a stream socket with unix domain
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("server: socket");
    exit(1);
  }

  // Create the name/address of the server socket
  memset(&name, 0, sizeof(struct sockaddr_un)); // Initialise the server socket name/address
  name.sun_family = AF_UNIX; // Set the address family to AF_UNIX
  strcpy(name.sun_path, SOCKET_NAME); // Set the path name to the socket name
  len = sizeof(name.sun_family) + strlen(name.sun_path); // Get the length of the server socket name/address


  // Remove any previous socket
  unlink(name.sun_path);

  // Attempt to bind the socket to the server socket name/address
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  if (bind(sock, (struct sockaddr *) &name, SUN_LEN(&name)) < 0) {
    perror("server: bind");
    exit(1);
  }

  // Attempt to listen for connection requests from the client (in this case, backlog is 15)
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  if (listen(sock, BACKLOG) < 0) {
    perror("server: listen");
    exit(1);
  }

  // Attempt to accept connection requests from the client
  // If client connection request has been accepted successfully
  //    then get a new socket descriptor to communicate with the client (nsock)
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  if ((nsock = accept(sock, (struct sockaddr *) &name, &len)) < 0) {
    perror("server: accept");
    exit(1);
  }

  // Add a delay to the server to allow the client to finish its execution first
  // After the client has finished its execution then clear the screen
  usleep(500000); // Sleep for 0.5 second
  printf("\e[1;1H\e[2J"); // Clear the screen

  // Keep iterating until there is no more line to be read from the new socket
  while ((n = recv(nsock, line, sizeof(line), 0)) > 0) {
    argumentCounter = 0; // Reset the argument counter to 0 for each iteration
    getCommandFromLine(line, command, &argumentCounter); // Get command from new socket
    printf("client: %s\n", line); // Print the command sent by the client
    executeCommand(command, argumentCounter); // Execute command from new socket
    freeCommandArray(command, argumentCounter); // Deallocate memory allocation pointed to by element(s) in command array
  }

  printf("Press enter to exit the program..."); // Print the appropriate termination message
  close(nsock); // Close the new socket
  close(sock); // Close the socket
  exit(0); // Exit with status code of 0 (indicating no error has occured)
}
