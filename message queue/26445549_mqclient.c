/*
  Name: Ray Krishardi Layadi
  Student ID: 26445549
  Start date: 9 October 2017
  End date: 20 October 2017
  High-level description: Refer to the introduction section of the user documentation
*/

#include "26445549_mq.c"

int main(int argc, char const *argv[]) {
  key_t key; // Represent the message queue key
  int msqid; // Represent the message queue ID
  struct msgbuf mbuf; // Represent the message buffer
  char line[MSQ_SIZE]; // Represent each line in the input file (e.g. commands.txt)

  // Attempt to get a reference to the message queue by using the message queue key and permission (message queue was created by the server)
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  key = MSQ_KEY;
  if ((msqid = msgget(key, MSQ_PERMISSION)) < 0) {
    perror("client: msgget");
    exit(1);
  }

  // Check the number of program arguments given by the user (in this case, the program name itself is considered as an argument)
  // If the number of program arguments is greater than 1 (i.e. the client program takes input file(s) as command line input)
  //    then read the content of the input file(s) and send the content to the message queue
  // If the number of program arguments is equal to 1 (i.e. the client program takes input file(s) as input redirection)
  //    then read the content of the standard input file and send the content to the message queue
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
        // If the input file is successfully opened for reading then send messages of type 1
        // which contains the unix commands obtained from the input file to the message queue
        sendMessageType1FromInput(line, infile, &mbuf, msqid);

        fclose(infile); // Close the input file
      }
    }
  }
  else {
    // Send messages of type 1 which contains the unix commands
    // obtained from the standard input file to the message queue
    sendMessageType1FromInput(line, stdin, &mbuf, msqid);
  }

  // Send messages of type 2 which indicates the end of the unix commands to the message queue
  sendMessageType2(&mbuf, msqid);

  exit(0); // Exit with status code of 0 (indicating no error has occured)
}