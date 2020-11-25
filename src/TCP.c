
#include "TCP.h"
//questions 1, 2 et 3
int TCPservQ1();
int UDPcliQ2();
int TCPcliQ3();
int EnvoieMessageTcpUdp(char mode [3], int port);

/*
All the TCP related interactions, choose server/client, port number, int-char-get page, loop send-receive
*/
void allTCP() {
  int choice = -1;
    while(choice !=0 && choice !=1 && choice !=6) {
        printf("Enter '0' to make a TCP server, '1' for a TCP client or '6' to scrap a webpage\n");
        inputTreatement(scanf("%d",&choice));
    }
    //if it's client or server
    if(choice<6) {
    int port = choosePortNumber();
    //server
    if(choice ==0) {
      TCPserver(port);
    }
    // client
    else {
      TCPclient(port);
    }
    }
    //choice ==6, scrapping
    else {
      char domain [100];
      printf("Enter the domain name for example 'google.com'\n");
      inputTreatement(scanf("%[^\n]",domain));
      TCPscraping(domain);
    }
}

/*
Open a TCP server listening to the port we gave him
It ask you what message is it supposed to wait for (char or int)
Then it accept it, show it to you, ask what you want to send to the client
Wait for another message or close the server
*/
int TCPserver(int port) {
	int err, run =0;
	
	struct sockaddr_in ad;
	//ipv4
	ad.sin_family = PF_INET;
  ad.sin_port = htons(port);
  err = inet_aton("127.0.0.1", &ad.sin_addr);
  erreur(err, "inet_aton");
  unsigned int taille = sizeof(ad);
  //ipv4, type de transmission, protocole unique par défaut
	int s1 = socket(AF_INET,SOCK_STREAM, 0); 
	erreur(s1, "socket");
	//bind
	err = bind(s1, (struct sockaddr *)&ad, taille);
	erreur(err, "bind");
  //if the bind isn't successful
  if(err<0){
    return err;
  }
	//listen
	err = listen(s1,2);
	erreur(err, "listen");
	//accept
	while(run<1) { 
    unsigned int * ptaille = &taille;
		int cli = accept(s1, (struct sockaddr *)&ad, ptaille );
		erreur(cli, "accept");
		printf("Client @ : %s:%d\n", inet_ntoa(ad.sin_addr), ntohs(ad.sin_port));
    //reading the client message
    char lec [500];
		read(cli,lec,500);
		printf("The client sent : %s\n", lec);
    //message to send back to the client
		char data [500];
    printf("What do you want to send to the client ?\n");
    inputTreatement(scanf("%[^\n]",data));
		write(cli, data, sizeof(data));
    printf("Do you want to wait for another client ? (0) YES (1) NO\n");
    inputTreatement(scanf("%d",&run));
	}
  printf("Shutting down the server...");
	close(s1) ;
	return 1;
}

/*
Open a TCP client listening to the port we gave him
It ask you what message is it supposed to send (char or int)
Then it wait and show you the answer of the server
Finally you can repeat or close the client
*/
int TCPclient(int port) {
		//création du socket
    int err;
    struct sockaddr_in ad;
    ad.sin_family = PF_INET;
    ad.sin_port = htons(port);
    err = inet_aton("127.0.0.1", &ad.sin_addr);
    erreur(err, "inet_aton");
    int run = -1;
    while(run <1) {
    int s = socket(PF_INET, SOCK_STREAM, 0);
    erreur(s, "socket");
    
      //connection du socket
      err = connect(s, (struct sockaddr *)&ad, sizeof(ad));
      erreur(err, "connect");
      //if the connection isn't successful
      if(err <0) {
        return err;
      }
      //send message
      char data [500];
      printf("What do you want to send to the server ?\n");
      inputTreatement(scanf("%[^\n]",data));
      write(s, data, sizeof(data));
      //reading the server message
      char lec [500];
      read(s,lec,500);
      printf("The server sent : \n%s", lec);
      printf("\nDo you want to send another message ? (0) YES (1) NO\n");
      inputTreatement(scanf("%d",&run));
    }
    return 1;
}

/*
Gets the content of a web page based on an url given by the user
*/
int TCPscraping(char * url) {
  char ip [100];
  if( getIpAddress(url,ip) ==-1) {
    return -1;
  }
  if(connectToAddress(ip) !=0) {
    return -1;
  }
    //Exemple :
    // getIpAddress("google.com");
    // connectToAddress("216.58.201.238");
  return 0;
}

/*
 Gets the ip address of a given domain name for exemple : google.com -> 216.58.201.238
 */
int getIpAddress(char *hostname,char ip[100] )
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ((he = gethostbyname(hostname)) == NULL)
    {
        //gethostbyname failed
        perror("gethostbyname");
        return -1;
    }

    //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
    addr_list = (struct in_addr **)he->h_addr_list;

    for (i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip, inet_ntoa(*addr_list[i]));
    }

    printf("%s resolved to : %s", hostname, ip);
    return 0;
}

/*
Connects to the ip address and ask for the main webpage to print it in the shell
*/
int connectToAddress(char *add)
{
    int socket_desc;
    struct sockaddr_in server;
    // Address Family - AF_INET (this is IP version 4)
    // Type - SOCK_STREAM (this means connection oriented TCP protocol)
    // Protocol - 0 [ or IPPROTO_IP This is IP protocol]
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -3)
    {
        printf("Echec de la création de socket");
    }
    server.sin_addr.s_addr = inet_addr(add);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    //Connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("connect error");
        return -1;
    }
    //Send some data
    char *message = "GET / HTTP/1.1\r\n\r\n";
    // The message is actually a http command to fetch the mainpage of a website.
    if (send(socket_desc, message, strlen(message), 0) < 0)
    {
        puts("Send failed");
        return -2;
    }
    puts("\nData Send\n");

    //Receive a reply from the server
    char server_reply[2000];
    if (recv(socket_desc, server_reply, 2000, 0) < 0)
    {
        puts("recv failed");
    }
    puts("Reply received\n");
    puts(server_reply);

    puts("\nConnected");
    return 0;
}

// gérer les short :
	//lecture des informations reçues
  //   char lec[3];
  //   read(s1, lec, 3);
  //   printf("%s\n", lec);
	// //reception du short
	// struct sockaddr_in distant;
	// unsigned short tmp[2];
  //   unsigned int lg = sizeof(distant);
  //   int recu = recvfrom(s1, tmp, sizeof(tmp) - 1, 0, (struct sockaddr *)&distant, &lg);
  //   if (recu < 0) //si on ne reçoit rien, erreur
  //   {
  //     perror("reception");
  //     close(s1);
  //     exit(2);
  //   }
  //   int x1 = tmp[0];
  //   //conversion en little endian
  //   int x2 = ntohs(tmp[0]);
	// printf("\nValeur : %d %d\n",x1, x2);