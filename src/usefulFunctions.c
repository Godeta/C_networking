#include "usefulFunctions.h"
/*
Empty the buffer
*/
void empty_stdin () 
{
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}

/*
Take care of scanf after it's call so that it doesn't loop and fail if you put characters instead of integer for exemple
*/
void inputTreatement (int scanf) {
        if (scanf == EOF) {   /* user generates manual EOF */
            fputs ("(user canceled input.)\n", stderr);
        }
        else if (scanf == 0) {    /* matching failure */
            fputs (" error: invalid integer input.\n", stderr);
            empty_stdin();
        }
        else {  /* good input */
            empty_stdin();
        }
}

/*
Print a message if there is an error, meaning err = -1
*/
void erreur(int err, const char *msg)
{
    if (err == -1)
    {
        perror(msg);
        // exit(-1);
    }
    else {
		printf("%s ok\n",msg);
	}
}

/*
Ask the user which port number he wants to use
*/
int choosePortNumber() {
    int choice = -1;
    while(choice <0 || choice >65535) {
        printf("Enter a port number to use\n");
        inputTreatement(scanf("%d",&choice));
    }
    return choice;
}

/*
Check if the chosen port number is available for the server to bind
*/
// int availablePortNumber (int port) {

// }