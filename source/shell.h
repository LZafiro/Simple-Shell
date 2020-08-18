/* Luiz Felipe Raveduti Zafiro       - RA: 120513 */
/* Leon Tenório da Silva             - RA: 120488 */
/* Alexandre Camargo Andreoli        - RA: 119943 */
/* Operating Systems - Unifesp (SJC) - 2020       */

/* Headder file for the shell implementation project */

/* Libs. */
////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
////////////////////////////////////////////

/* Constant definitions */
////////////////////////////////////////////
#define STR_LEN 10000
////////////////////////////////////////////

/* Global Variables */
////////////////////////////////////////////
/* Number of comments presented on the input */
extern int numCommands;
/* List of matrixes. Each one is a command matrix */
extern char ***matList;
////////////////////////////////////////////

/* Function Headders */
////////////////////////////////////////////
/* Creates a vector os matrixes. Each matrix refers to a command (in case of pipe) */
void commandMatrixGenerator(int argc, char **argv);

/* Executes piped and non piped commands */
void commandsExec();
////////////////////////////////////////////


/* Trash */

/* Executes simple commands (non piped and non file types) */
/*void simpleCommands();//Doesn't need it*/

/*
void simpleCommands(){

    int status;
    pid_t pid = fork();
    
    //Child
    if(pid == 0){
        //Creates child process 
        //Passes the first command and first matrix, related to that command
        
        execvp(matList[0][0], matList[0]);
        perror("Simple Command Execution Error");
    }

    //Parent
    else 
        waitpid(-1, &status, 0);

    return;
}*/