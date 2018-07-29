/*
  Name: Ray Krishardi Layadi
  Student ID: 26445549
  Start date: 9 October 2017
  End date: 20 October 2017
  High-level description: Refer to the introduction section of the user documentation
*/

#include "26445549_mq.c"

int main(void) {
  key_t key; // Represent the message queue key
  int n, msqid; // Represent the message queue ID and the number of bytes stored in the message buffer referenced by msgbuf (n)
  struct msgbuf mbuf; // Represent the message buffer
  int argumentCounter; // Represent the number of command arguments (in this case, the command name itself is considered as an argument)
  char *command[BUFFER_SIZE]; // Represent command to be executed

  // Attempt to create a message queue by specifying the message queue key and permission
  // IPC_CREAT -> Create the message queue
  // IPC_EXCL -> Check if the message queue to be created is already exists
  // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
  key = MSQ_KEY;
  if ((msqid = msgget(key, IPC_CREAT | IPC_EXCL | MSQ_PERMISSION)) < 0) {
    perror("server: msgget");
    exit(1);
  }

  // Add a delay to the server to allow the client to finish its execution first
  // After the client has finished its execution then clear the screen
  sleep(1); // Sleep for 1 second
  printf("\e[1;1H\e[2J"); // Clear the screen

  // Keep iterating until there is no more message to be read from the message queue
  while ((n = msgrcv(msqid, &mbuf, MSQ_SIZE, 0, 0)) > 0) {
    if (mbuf.mtype == 1) {
      argumentCounter = 0; // Reset the argument counter to 0 for each iteration
      getCommandFromLine(mbuf.mtext, command, &argumentCounter); // Get command from message queue
      printf("client: %s\n", mbuf.mtext); // Print the command sent by the client
      executeCommand(command, argumentCounter); // Execute command from message queue
      freeCommandArray(command, argumentCounter); // Deallocate memory allocation pointed to by element(s) in command array
    }
    else if (mbuf.mtype == 2) {
      // Attempt to remove message queue from the system by specifying the message queue ID
      // IPC_RMID -> Remove message queue from the kernel
      // If an error occurs then display the appropriate error message and exit with status code of 1 (indicating error has occured)
      if (msgctl(msqid, IPC_RMID, (struct msqid_ds *) 0) < 0) {
        perror("server: msgctl");
        exit(1);
      }
    }
  }

  printf("Press enter to exit the program..."); // Print the appropriate termination message
  exit(0); // Exit with status code of 0 (indicating no error has occured)
}
