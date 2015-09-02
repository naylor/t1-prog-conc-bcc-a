#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matEntrada.h"
#include "interfaces.h"
#define MAX_DOUBLE 2

int main (int argc, char* argv[]){

    // Vari�veis auxiliares para leitura do arquivo
    int i, j;
    int auxInt;
    short auxShort;
    double auxDouble;
    long auxLong;
    struct caminhoTipo ct = telaInicial();
    double* resultado = NULL;
    double* x0 = NULL;

    // Ponteiro para o arquivo que ser� aberto
    FILE* arqMat = NULL;
    // Cria a estrutura que armazenar� as matrizes
    MAT_ENTRADA* m = criarMatEntrada();

    arqMat = fopen(ct.caminho,"r");

    if(arqMat == NULL){
        printf("Erro ao abrir arquivo.");
    }
    else{
        // Le as primeiras informa��es do arquivo
        fscanf(arqMat, "%d", &auxInt);
        fscanf(arqMat, "%hd", &auxShort);
        fscanf(arqMat, "%lf", &auxDouble);
        fscanf(arqMat, "%ld", &auxLong);
        // Salva os valores na estrutura
        inicializarValsMatEntrada(m,auxInt,auxShort,auxDouble,auxLong,0);
        // Aloca espa�o para as matrizes A e B, agora que sabemos sua dimens�o
        alocarMatA(m);
        alocarMatB(m);
        // Insere os elementos na Matriz A
        for(i=0;i<getOrdem(m);i++){
            for(j=0;j<getOrdem(m);j++){
                fscanf(arqMat,"%lf",&auxDouble);
                inserirElemMatA(m,auxDouble,i,j);
            }
        }
        // Insere os elementos na Matriz B
        for(i=0;i<getOrdem(m);i++){
            fscanf(arqMat,"%lf",&auxDouble);
            inserirElemMatB(m,auxDouble,i);
        }
        // Fecha o arquivo agora que n�o precisamos mais dele
        fclose(arqMat);

        //imprimirInfosMatEntrada(m);
    }

    x0 = (double*)malloc(getOrdem(m)*sizeof(double));
    /*
    srand((unsigned int)time(NULL));
    for(i=0;i<getOrdem(m);i++){
        x0[i] = ((float)rand()/(float)(RAND_MAX))*MAX_DOUBLE;
    }
*/
    x0[0] = 0.7;
    x0[1] = -1.6;
    x0[2] = 0.6;


    if (ct.tipo == 's')
       resultado = jacobiRichardsonSerial(m,x0);

    if (ct.tipo == 'p')
       resultado = jacobiRichardsonParalelo(m,x0);

    imprimirResultado(resultado,getOrdem(m));
    imprimirInfosMatEntrada(m);

    // Libera a mem�ria alocada pela estrutura
    destruirMatEntrada(m);

    return 0;
}
