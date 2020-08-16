/* Luiz Felipe Raveduti Zafiro - RA: 120513 */
/* Leon Tenório da Silva - RA: 120--- */
/* Operating Systems - Unifesp (SJC) - 2020 */

/* Code for the shell process */

#include "shell.h"

int main(int argc, char **argv){
    int ch_in[2], ch_out[2];

    bool first = true;

    Tfila fila;
    Tfila_inicia(&fila);
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i], "|")==0){
            create_child_process(&fila, &first, ch_in, ch_out);
        }
        else{
            Tfila_insere(&fila, argv[i]);
        }
    }
    create_child_process(&fila, &first, ch_in, ch_out);
    return 0;
}