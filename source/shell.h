/* Luiz Felipe Raveduti Zafiro       - RA: 120513 */
/* Leon Tenório da Silva             - RA: 120488 */
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

/* Executes simple commands (non piped and non file types) */
/*void simpleCommands();//Doesn't need it*/

/* Executes piped commands */
void pipedCommands();
////////////////////////////////////////////