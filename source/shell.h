/* Luiz Felipe Raveduti Zafiro - RA: 120513 */
/* Leon Tenório da Silva - RA: 120--- */
/* Operating Systems - Unifesp (SJC) - 2020 */

/* Headder file for the shell implementation project */

#ifndef _SHELL_H_
#define _SHELL_H_

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
////////////////////////////////////////////

/* Constant definitions */
////////////////////////////////////////////
#define READ_SIDE 0
#define WRITE_SIDE 1
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
void simpleCommands();

/* Executes piped commands */
void pipedCommands();
////////////////////////////////////////////

#endif _SHELL_H_