/* Luiz Felipe Raveduti Zafiro - RA: 120513 */
/* Leon Tenório da Silva - RA: 120--- */
/* Operating Systems - Unifesp (SJC) - 2020 */

/* Headder file implementation for the shell implementation project */

#include "shell.h"

/* Global variable definition */
int numCommands = 0;
char ***matList;


void commandMatrixGenerator(int argc, char **argv){
    
    /* Array of pointers to char matrixes (strings) */
    matList = (char***)malloc(sizeof(char**));

    char **cmd = &argv[1];
    int n = argc - 1;

    /* Some indexes 
    * i = argv iterator
    * j = matList index
    * k = matList[j] index
    */
    int i, j = 0, k = 0, matListSize = 1;

    /* At least one command */
    numCommands++;

    /* Check for errors in allocation */
    if(matList == NULL) exit(-1);

    else matList[0] = NULL;

    /* Iterates thru all argc matrix (already without the fisrt line (./shell)) - cmd in main */
    for(int i = 0; i < n; i++){

        if(strcmp(cmd[i], "|") != 0){
            /* Reallocs the matrix with one more line */
            matList[j] = (char **)realloc(matList[j], (k + 1) * sizeof(char*));
        
            /* Stores the string in the k line of the j matrix */
            matList[j][k] = cmd[i];
            k++;
        }

        else{

            matListSize++;

            /* Reallocs the matrix list */
            matList = (char***)realloc(matList, matListSize * sizeof(char**));

            /* new matrix, goes to it's first line  */
            k = 0;   
            j++;
            matList[j] = NULL;
            numCommands++;
        }
    }
}


void simpleCommands(){

    int status;
    pid_t pid = fork();
    
    /* Child */
    if(pid == 0){
        /* 
        * Creates child process 
        * Passes the first command and first matrix, related to that command
        */
        execvp(matList[0][0], matList[0]);
        perror("Simple Command Execution Error");
    }

    /* Parent */
    else 
        waitpid(-1, &status, 0);

    return;
}


void pipedCommands(){
    /* File Descriptors */
    int fd[numCommands - 1][2];
    pid_t pid;
    int i;

    /* Pipes initialization */
    for(i = 0; i < (numCommands - 1); i++){
        /* Creates a pipe based on the file descriptor passed */
        int p = pipe(fd[i]);

        if(pipe < 0){
            perror("Pipe Creation");
            exit(-1);
        }
    }

    /* Creates all child processes of the pipe */
    for(i = 0; i < numCommands; i++){
        /* Forks current process */
        pid = fork();

        /* Child */
        if(pid == 0){

            /* If it is the first child */
            if(i == 0){
                close(fd[i][0]);
                dup2(fd[i][1], STDOUT_FILENO);
            }

            /* If it is the last child */
            if(i == numCommands - 1){
                close(fd[i - 1][1]);
                dup2(fd[i - 1][0], STDIN_FILENO);
            }

            /* If it is a "middle" child */
            else{
                close(fd[i - 1][1]);
                close(fd[i][0]);
                dup2(fd[i - 1][0], STDIN_FILENO);
                dup2(fd[i][1], STDOUT_FILENO);
            }

            /* Execution of the child */
            execvp(matList[i][0], matList[i]);
        }

        /* Parent */
        else{
            /* Pipe closing, important */
            for(i = 0; i < (numCommands - 1); i++)
                close(fd[i][0]);
                close(fd[i][1]);

            wait(NULL);
        }
    }

}