
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
    while(choice <0 || choice >1) {
        printf("Enter '0' to make a TCP server or '1' for a TCP client\n");
        inputTreatement(scanf("%d",&choice));
    }
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
  int taille = sizeof(ad);
  //ipv4, type de transmission, protocole unique par défaut
	int s1 = socket(AF_INET,SOCK_STREAM, 0); 
	erreur(s1, "socket");
	//bind
	err = bind(s1, (struct sockaddr *)&ad, taille);
	erreur(err, "bind");
	//listen
	err = listen(s1,2);
	erreur(err, "listen");
	//accept
	while(run<1) { 
		int cli = accept(s1, (struct sockaddr *)&ad, &taille );
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