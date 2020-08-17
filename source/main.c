/* Luiz Felipe Raveduti Zafiro - RA: 120513 */
/* Leon Tenório da Silva - RA: 120--- */
/* Operating Systems - Unifesp (SJC) - 2020 */

/* Main file for the shell implementation project */

#include "shell.h"

int main(int argc, char **argv){

    /* No commands passed */
    if(argc == 1){
        printf("No commands found!\n");
        return 0;
    }

    commandMatrixGenerator(argc, argv);  

    

    return 0;
}