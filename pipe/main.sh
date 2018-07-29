#!/bin/bash

# Represent the client and server program
server="26445549_pipeserver"
client="26445549_pipeclient"

# Execute the server program in background
./$server &

# Add a delay of 0.25 second to ensure that the server and client program does not execute immediately
# This is because the program might not work properly if the server and client program is executed immediately after each other
sleep .25

# Check whether standard input file descriptor is open and associated with a terminal
# If the standard input file descriptor is NOT open and associated with a terminal then the program takes input file(s) as command line input
# If the standard input file descriptor is open and associated with a terminal then the program takes input file(s) as input redirection
if [ -t 0 ]; then
  # Represent the input file(s) received from the command line input
  args=""

  # Get the input file(s) received from the command line input
  for arg in "$@"; do
    args+="$arg "
  done

  # Execute the client program with the associated input file(s) received from the command line input
  ./$client $args
else
  # Execute the client program with the associated input file(s) received from the input redirection
  ./$client <&0
fi