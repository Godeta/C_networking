#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
//some usefulFunctions that I made
#include "usefulFunctions.h"

//the functions in the program :
void allTCP();
int TCPserver(int port);
int TCPclient(int port);