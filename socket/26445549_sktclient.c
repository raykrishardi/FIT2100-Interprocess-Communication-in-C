/*
  Name: Ray Krishardi Layadi
  Student ID: 26445549
  Start date: 9 October 2017
  End date: 20 October 2017
  High-level description: Refer to the introduction section of the user documentation
*/

#include "26445549_skt.h"

int main(int argc, char const *argv[]) {
  int sock; // Represent the socket to be connected to the server process
  struct sockaddr_un name; // Represent the server socket name/address
  char line[BUFFER_SIZE]; // Represent each line in the input file (e.g. commands.txt)

  // Attempt to create a stream socket with unix domain
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("client: socket");
    exit(1);
  }

  // Create the name/address of the server socket
  memset(&name, 0, sizeof(struct sockaddr_un)); // Initialise the server socket name/address
  name.sun_family = AF_UNIX; // Set the address family to AF_UNIX
  strcpy(name.sun_path, SOCKET_NAME); // Set the path name to the socket name

  // Attempt to connect to the server process
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  if (connect(sock, (struct sockaddr *) &name, SUN_LEN(&name)) < 0) {
    perror("client: connect");
    exit(1);
  }

  // Check the number of program arguments given by the user (in this case, the program name itself is considered as an argument)
  // If the number of program arguments is greater than 1 (i.e. the client program takes input file(s) as command line input)
  //    then read the content of the input file(s) and send the content to the socket
  // If the number of program arguments is equal to 1 (i.e. the client program takes input file(s) as input redirection)
  //    then read the content of the standard input file and send the content to the socket
  if (argc > 1) {
    // Loop through the program arguments (excluding the program name)
    for (int i = 1; i < argc; i++) {
      FILE *infile; // Represent the input file received from the command line input

      // Attempt to open the input file for reading
      if ((infile = fopen(argv[i], "r")) == NULL) {
        // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
        perror("client: open input file");
        exit(1);
      }
      else {
        // If the input file is successfully opened for reading then
        // keep iterating until there is no more line to be read from the input file
        while (fgets(line, BUFFER_SIZE, infile)) {
          send(sock, line, BUFFER_SIZE, 0); // Send each line in input file to the socket
        }

        fclose(infile); // Close the input file
      }
    }
  }
  else {
    // Keep iterating until there is no more line to be read from the standard input file
    while (fgets(line, BUFFER_SIZE, stdin)) {
      send(sock, line, BUFFER_SIZE, 0); // Send each line in standard input file to the socket
    }
  }

  close(sock); // Close the socket
  exit(0); // Exit with status code of 0 (indicating no error has occured)
}