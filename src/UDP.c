#include "UDP.h"

/*
All the UDP related interactions, choose server/client, port number, message, loop send-receive
*/
void allUDP() {
  int choice = -1;
    while(choice <0 ||choice >1) {
        printf("Enter '0' to make a UDP server or '1' for a UDP client\n");
        inputTreatement(scanf("%d",&choice));
    }
    int port = choosePortNumber();
    //server
    if(choice ==0) {
      UDPserver(port);
    }
    // client
    else {
      UDPclient(port);
    }
}

/*
Open a UDP server listening to the port we gave him
It ask you what message is it supposed to wait for (char or int)
Then it accept it, show it to you, ask what you want to send to the client
Wait for another message or close the server
*/
int UDPserver(int port) {
    printf("Creating server...\n");
    int err;
    struct sockaddr_in ad;
    //ipv4
    ad.sin_family = PF_INET;
    ad.sin_port = htons(port);
    err = inet_aton("127.0.0.1", &ad.sin_addr);
    erreur(err, "inet_aton");
    int taille = sizeof(ad);
    //ipv4, UDP, default ->unique protocol
    int s1 = socket(AF_INET, SOCK_DGRAM, 0);
    erreur(s1, "socket");
    //bindq
    err = bind(s1, (struct sockaddr *)&ad, taille);
    erreur(err, "bind");

    int run = 0;
    while (run == 0)
    {
        printf("Reading data...\n");
        unsigned int addrlen = sizeof(ad); /* must be initialized */
        char data_received[500];
        recvfrom(s1, data_received,
                                      sizeof(data_received), 0, (struct sockaddr *)&ad, &addrlen);
        char client[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ad.sin_addr, client, sizeof(client));
        printf("Le client %s a envoyé : %s", client, data_received);
        //send data
        char data_sent [500];
        printf("What do you want to send to the client ?\n");
        inputTreatement(scanf("%[^\n]",data_sent));
        printf("Sending : %s\n", data_sent);
        sendto(s1, data_sent, sizeof(data_sent), 0,
                                (struct sockaddr *)&ad, sizeof(ad));
        printf("Do you want to wait for another client ? Yes (0) No(1)\n");
        scanf("%d", &run);
    }
    printf("Shutting down the server...");
    close(s1);
    return 0;
}

/*
Open a UDP client listening to the port we gave him
It ask you what message is it supposed to send (char or int)
Then it wait and show you the answer of the server
Finally you can repeat or close the client
*/
int UDPclient(int port) {
    int err;
    //defining the server
    struct sockaddr_in ad;
    ad.sin_family = PF_INET;
    ad.sin_port = htons(port);
    err = inet_aton("127.0.0.1", &ad.sin_addr);
    erreur(err, "inet_aton");
        int run = -1;
    while(run <1) {
    //creating the socket
    int s = socket(PF_INET, SOCK_DGRAM, 0);
    erreur(s, "socket");
    //envoie données
    printf("Sending the data...\n");
    //send data
    char data_sent [500];
    printf("What do you want to send to the server ?\n");
    inputTreatement(scanf("%[^\n]",data_sent));
    sendto(s, data_sent, sizeof(data_sent), 0,
                            (struct sockaddr *)&ad, sizeof(ad));
    //lecture données
    printf("Reading the data\n");
    unsigned int addrlen = sizeof(ad); /* must be initialized */
    char data_received[500];
    recvfrom(s, data_received,
                                  sizeof(data_received), 0, (struct sockaddr *)&ad, &addrlen);
    printf("Message received from the server : %s", data_received);
    printf("\nDo you want to send another message ? (0) YES (1) NO\n");
    inputTreatement(scanf("%d",&run));
    }
    return 0;
}