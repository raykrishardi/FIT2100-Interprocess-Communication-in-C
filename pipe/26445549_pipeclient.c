/*
  Name: Ray Krishardi Layadi
  Student ID: 26445549
  Start date: 9 October 2017
  End date: 20 October 2017
  High-level description: Refer to the introduction section of the user documentation
*/

#include "26445549_pipe.h"

int main(int argc, char const *argv[]) {
  FILE *fifo; // Represent the FIFO
  char line[BUFFER_SIZE]; // Represent each line in the input file (e.g. commands.txt)

  // Attempt to open the FIFO for writing (FIFO was created by the server)
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  if ((fifo = fopen(FIFO_NAME, "w")) == NULL) {
    perror("client: open FIFO");
    exit(1);
  }

  // Check the number of program arguments given by the user (in this case, the program name itself is considered as an argument)
  // If the number of program arguments is greater than 1 (i.e. the client program takes input file(s) as command line input)
  //    then read the content of the input file(s) and write the content to the FIFO
  // If the number of program arguments is equal to 1 (i.e. the client program takes input file(s) as input redirection)
  //    then read the content of the standard input file and write the content to the FIFO
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
          fputs(line, fifo); // Put each line in input file to the FIFO
        }

        fclose(infile); // Close the input file
      }
    }
  }
  else {
    // Keep iterating until there is no more line to be read from the standard input file
    while (fgets(line, BUFFER_SIZE, stdin)) {
      fputs(line, fifo); // Put each line in standard input file to the FIFO
    }
  }

  fclose(fifo); // Close the FIFO
  exit(0); // Exit with status code of 0 (indicating no error has occured)
}