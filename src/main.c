
#include "main.h"

/*
A small networking in C project : You choose a protocol (UDP,TCP),
if it's Server or client, which port number,
char* or int/ get a webpage, send another message ? 
*/
int main () {
    //start of the program, you choose a protocol and it acts differently depending on that
    chooseProtocol();
    return 0;
}

/*
Allow the user to choose a transmission protocol and execute different actions depending on what he choose
*/
void chooseProtocol() {
    printf("Welcome here sir ! Which protocol would you like to use today ?\n");
    int choice = -1;
    while(choice <0 || choice >1) {
        printf("Enter '0' for UDP or '1' for TCP\n");
        inputTreatement(scanf("%d",&choice));
    }
    //UDP
    if(choice ==0) {
        
    }
    //TCP
    else {
        allTCP();
    }

}