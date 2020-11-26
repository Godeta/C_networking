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
void allUDP();
int UDPserver(int port);
int UDPclient(int port);

// not very standard function, defined in <sys/socket.h> <netinet/in.h> <arpa/inet.h>, I put it in the header to not get a warning when compiling
int inet_aton(const char *__cp, struct in_addr *__inp);