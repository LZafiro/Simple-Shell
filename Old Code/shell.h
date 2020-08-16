/* Luiz Felipe Raveduti Zafiro - RA: 120513 */
/* Leon Tenório da Silva - RA: 120--- */
/* Operating Systems - Unifesp (SJC) - 2020 */

/* Headder file for the shell implementation project */

#ifndef _SHELL_
#define _SHELL_

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

/* Declarations */                             // structs variaveis etc aqui
////////////////////////////////////////////  
#define STR_LEN 1000

/* Queue struct */
typedef struct Scelula{
	char* info;
    Tapontador prox;
}Tcelula;

typedef struct Scelula *Tapontador;

typedef struct{
    int tamanho;
    Tapontador comeco;
    Tapontador fim;
}Tfila;
////////////////////////////////////////////

/* Function Declarations */                    // declarar aqui os cabeçalhos
////////////////////////////////////////////]

/**/ 
void Tfila_inicia(Tfila *fila);

char* Tfila_retira(Tfila *fila);

void Tfila_insere(Tfila *fila,char* x);

//Cria uma matrix de strings para o argumentos da funcao
char** child_args(Tfila *fila);
 
int create_child_process(Tfila *fila, bool *first, int ch_in[2], int ch_out[2]);
////////////////////////////////////////////

#endif _SHELL_