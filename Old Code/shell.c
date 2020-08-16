/* Luiz Felipe Raveduti Zafiro - RA: 120513 */
/* Leon Tenório da Silva - RA: 120--- */
/* Operating Systems - Unifesp (SJC) - 2020 */

/* Code for the implementations of the shell.h functions */

/* Headder file */
#include "shell.h"

/* Initialize queue */
void Tfila_inicia(Tfila *fila){
    fila->tamanho=0;
    fila->comeco=NULL;
    fila->fim=NULL;
}

/* Remove from queue */
char* Tfila_retira(Tfila *fila){
    char *elem;
    Tapontador aux;
    aux=fila->comeco;
    fila->comeco=fila->comeco->prox;
	elem = aux->info;
    fila->tamanho--;
    free(aux);
    return elem;
}

/* Insert on queue */
void Tfila_insere(Tfila *fila,char* x){
    Tapontador novo;
    novo=(Tapontador)malloc(sizeof(Tcelula));
    if(novo!=NULL){
		novo->info=x;
		if(fila->tamanho!=0){
            fila->fim->prox=novo;
            fila->fim=novo;
            novo->prox=NULL;
            fila->tamanho++;
        }
        else{
            fila->comeco=novo;
            fila->fim=novo;
            fila->comeco->prox=NULL;
            fila->tamanho++;
        }
		novo=NULL;
    }
    else
        Tfila_insere(fila,x);
}

char** child_args(Tfila *fila){
    printf("Iria para a criacao de mais um pipe: ");
    char **ch_args = (char**)malloc(fila->tamanho*sizeof(char*));
    int i=0;
    while(fila->tamanho>0){
        ch_args[i] = Tfila_retira(fila);
        printf("%s ", ch_args[i]);
    }
    printf("\n");
    return ch_args;
}

int create_child_process(Tfila *fila, bool *first, int ch_in[2], int ch_out[2]){
    char **ch_args = child_args(fila);
    __pid_t child;
    if(first){//So preciso de um pipe para o filho escrever
        if(pipe(ch_out) >= 0){
            child = fork();
            if(child==0){
                close(ch_out[0]);
                if(dup2(STDOUT_FILENO, ch_out[1])>=0){//Aqui ta o role, trocar a saida padrao do processo filho para ch_out[1]
                    printf("aqui\n");
                    execvp(ch_args[0], ch_args);
                }
                else{
                    perror("dup2()");
                    return (-1);
                }
            }
            else if(child > 0){
                close(ch_out[1]);
                int status;
                waitpid(-1, &status, 0);
                char msg[STR_LEN];
                if(read(ch_out[0], msg, STR_LEN)>0){
                    printf("Saida do primeiro processo foi: %s \n", msg);
                    sleep(5);
                }
            }
            else{

            }
        }
        else{
            perror("pipe()");
            return (-1);
        }
        *first = false;
    }
    else{//Preciso de um pipe para o filho escrever e para o pai passar as informacoes
        if(pipe(ch_in) > 0 || pipe(ch_out) > 0){

        }
        else{
            perror("pipe()");
            return (-1);
        }
    }
    Tfila_inicia(fila);
    return 0;
}
