#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h> //strcpy
#include <netdb.h>  //hostent

//some usefulFunctions that I made
#include "usefulFunctions.h"

//the functions in the program :
void allTCP();
int TCPserver(int port);
int TCPclient(int port);
int TCPscraping(char* url);
int getIpAddress(char *hostname, char ip[100]);
int connectToAddress(char *add);