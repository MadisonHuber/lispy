#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

// if we are compiling on windows compile these functions
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

// fake readline function
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1]='\0';
    return cpy;
}

// fake add_history function
void add_history(char* unused) {}

// otherwise include the editline headers
#else

#include <editline/readline.h>
// #include <editline/history.h> // not required
#endif

/* Declare a buffer for user input of size 2048 */
// static char input[2048]; // removed since using editline
/*
above line declares a global array of 2048 characters 
static makes it local to this file
[2048] declares the size
*/

int main(int argc, char** argv) {

    /* Print Version and Exit Information */
    puts("Lispy Version 0.0.0.0.1");
    puts("Press Ctrl+c to Exit\n");

    /* In a never ending loop */
    while (1) {

        /* Output our prompt */
        // fputs("lispy> ", stdout);
        /* fputs is a variation on puts that does not append a newline character*/

        char* input = readline("lispy> ");
        // instead of prompting, and getting input with fgets we do it all in one line with readline then pass this result to add_history to record it and print it using printf
        // readline like fputs but lets you edit --from Editline
        /* Read a line of user input of maximum size 2048 */
        // fgets(input, 2048, stdin);

        add_history(input); // add input to history, from Editline

        /* Echo input back to user */
        printf("No you're a %s\n", input);
        // newline added since readline strips it off so we have to put it back
        /* %s will be replaced by whatever argument passed in next */


        free(input); // Free retrieved input, with Editline
        // using free we delete the input given to us by the readline function
        // we do this because unlike fgets, which writes to some existing buffer, the readline function allocates new memory when it is called

        /* stdin and stdout represent input to/from command line */
    }

    return 0;
}