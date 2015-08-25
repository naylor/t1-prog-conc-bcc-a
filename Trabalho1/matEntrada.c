#include <stdio.h>
#include <stdlib.h>
#include "matEntrada.h"

// --- Funções de Alocação de Memória ---
MAT_ENTRADA* criarMatEntrada(){

    MAT_ENTRADA* m = (MAT_ENTRADA*)calloc(1,sizeof(MAT_ENTRADA));

    return(m);
}

void alocarMatA(MAT_ENTRADA* m){

    int i;

    m->matA = (int**)malloc((m->ordemMat)*sizeof(int*));

    for(i=0;i<(m->ordemMat);i++){
        m->matA[i] = (int*)malloc((m->ordemMat)*sizeof(int));
    }
}

void alocarMatB(MAT_ENTRADA* m){
    m->matB = (int*)malloc((m->ordemMat)*sizeof(int));
}

// --- Funções de Inserção de Valores ---

void inserirOrdem(MAT_ENTRADA* m, int ordem){
    m->ordemMat = ordem;
}
void inserirFilaAval(MAT_ENTRADA* m, short fila){
    m->filaAval = fila;
}
void inserirErroPerm(MAT_ENTRADA* m, double erro){
    m->erroPerm = erro;
}
void inserirMaxIt(MAT_ENTRADA* m, long maxIt){
    m->maxIt = maxIt;
}
void inicializarValsMatEntrada(MAT_ENTRADA* m, int ordem, short fila, double erro, long maxIt){
    inserirOrdem(m,ordem);
    inserirFilaAval(m,fila);
    inserirErroPerm(m,erro);
    inserirMaxIt(m,maxIt);
}
void inserirElemMatA(MAT_ENTRADA* m, int elem, int posX, int posY){
    m->matA[posX][posY] = elem;
}

void inserirElemMatB(MAT_ENTRADA* m, int elem, int pos){
    m->matB[pos] = elem;
}

// --- Funções de Recuperação de Valores
int getOrdem(MAT_ENTRADA* m){
    return(m->ordemMat);
}
short getFilaAval(MAT_ENTRADA* m){
    return(m->filaAval);
}
double getErroPerm(MAT_ENTRADA* m){
    return(m->erroPerm);
}
long getMaxIt(MAT_ENTRADA* m){
    return(m->maxIt);
}
int getElemMatA(MAT_ENTRADA* m, int posX, int posY){
    return(m->matA[posX][posY]);
}
int getElemMatB(MAT_ENTRADA* m, int pos){
    return(m->matB[pos]);
}

// --- Funções de Liberação de Memória
void desalocarMatA(MAT_ENTRADA* m){

    int i;
    for(i=0;i<(m->ordemMat);i++){
        if(m->matA[i] != NULL){
            free(m->matA[i]);
        }
    }
    if(m->matA != NULL){
        free(m->matA);
    }
}

void desalocarMatB(MAT_ENTRADA* m){
    if(m->matB != NULL){
        free(m->matB);
    }
}

void destruirMatEntrada(MAT_ENTRADA* m){

    desalocarMatA(m);
    desalocarMatB(m);

    if(m != NULL){
        free(m);
    }
}

// --- Funções de Impressão ---
void imprimirMatA(MAT_ENTRADA* m){
    int i, j;
    for(i=0;i<getOrdem(m);i++){
        for(j=0;j<getOrdem(m);j++){
            printf("%d",getElemMatA(m, i, j));
        }
        printf("\n");
    }
}

void imprimirMatB(MAT_ENTRADA* m){

    int i;
    for(i=0;i<getOrdem(m);i++){
        if(i%15==0){
            printf("%d\n", getElemMatB(m,i));
        }
        else{
            printf("%d ", getElemMatB(m,i));
        }
    }
}

void imprimirInfosMatEntrada(MAT_ENTRADA* m){

    printf("Ordem da Matriz: %d\n", getOrdem(m));
    printf("Fila a ser Avaliada: %hd\n", getFilaAval(m));
    printf("Erro permitido: %.4lf\n", getErroPerm(m));
    printf("Numero maximo de iteracoes: %ld\n", getMaxIt(m));

}
