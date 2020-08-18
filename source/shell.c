/* Luiz Felipe Raveduti Zafiro       - RA: 120513 */
/* Leon Tenório da Silva             - RA: 120488 */
/* Operating Systems - Unifesp (SJC) - 2020       */

/* Headder file implementation for the shell implementation project */

#include "shell.h"

/* Global variable definition */
int numCommands = 0;
char ***matList;

bool file_in = false;
char arq_in[STR_LEN];
bool file_out = false;
bool out_append = false;
char arq_out[STR_LEN];

void commandMatrixGenerator(int argc, char **argv){
    
    bzero(arq_in, STR_LEN);
    bzero(arq_out, STR_LEN);
    
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
    i = 0;
    while(i < n){
        if(strcmp(cmd[i], "<")==0){
            file_in = true;
            strcpy(arq_in, cmd[i+1]);
            i = i + 2;
        }
        else if(strcmp(cmd[i], ">")==0){
            file_out = true;
            out_append = false;
            strcpy(arq_out, cmd[i+1]);
            i = i + 2;
        }
        else if(strcmp(cmd[i], ">>")==0){
            file_out = true;
            out_append = true;
            strcpy(arq_out, cmd[i+1]);
            i = i + 2;
        }
        else if(strcmp(cmd[i], "|") != 0){
            /* Reallocs the matrix with one more line */
            matList[j] = (char **)realloc(matList[j], (k + 1) * sizeof(char*));
        
            /* Stores the string in the k line of the j matrix */
            matList[j][k] = cmd[i];
            k++;
            i++;
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
            i++;
        }
    }
}


void commandsExec(){
    /* File Descriptors */
    int fd[numCommands - 1][2];
    pid_t pid;
    int i, status;

    int out_fd, in_fd;

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
                if(i > 0){
                    close(fd[i - 1][1]);
                    dup2(fd[i - 1][0], STDIN_FILENO);
                }
                
                else if(file_in){
                    in_fd = open(arq_in, O_RDONLY);
                    dup2(in_fd, STDIN_FILENO);
                }
                
                if(file_out){
                    if(out_append){
                        out_fd = open(arq_out, O_WRONLY|O_APPEND|O_CREAT, 0777);
                    }
                    
                    else{
                        out_fd = open(arq_out, O_WRONLY|O_TRUNC|O_CREAT, 0777);
                    }
                    
                    dup2(out_fd, STDOUT_FILENO);
                }
            }

            /* If it is a "middle" child */
            else{
                if(i > 0)
                    close(fd[i - 1][1]);

                close(fd[i][0]);
                
                if(i > 0)
                    dup2(fd[i - 1][0], STDIN_FILENO);
                
                else if(file_in){
                    in_fd = open(arq_in, O_RDONLY);
                    dup2(in_fd, STDIN_FILENO);
                }
                
                dup2(fd[i][1], STDOUT_FILENO);
            }

            /* Execution of the child */
            execvp(matList[i][0], matList[i]);
            
            if(file_out && i==numCommands-1){
                close(out_fd);
            }
            
            if(i==0 && file_in){
                close(in_fd);
            }
        }

        /* Parent */
        else{
                /* Not the first onde */
                if(i != 0){
                    close(fd[i - 1][0]);
                    close(fd[i - 1][1]);
                }
                
            /* Wait for all children */
            waitpid(-1, &status, 0);
            /*  
            ! Lembrar o que fazer com a variável status
            */
        }
    }
}