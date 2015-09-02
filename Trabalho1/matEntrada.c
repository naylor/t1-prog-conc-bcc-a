#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matEntrada.h"
#include <pthread.h>

// --- Fun��es de Aloca��o de Mem�ria ---
MAT_ENTRADA* criarMatEntrada(){

    MAT_ENTRADA* m = (MAT_ENTRADA*)calloc(1,sizeof(MAT_ENTRADA));

    return(m);
}

void alocarMatA(MAT_ENTRADA* m){

    int i;

    m->matA = (double**)malloc(getOrdem(m)*sizeof(double*));

    for(i=0;i<getOrdem(m);i++){
        m->matA[i] = (double*)malloc(getOrdem(m)*sizeof(double));
    }
}

void alocarMatB(MAT_ENTRADA* m){
    m->matB = (double*)malloc(getOrdem(m)*sizeof(double));
}

// --- Fun��es de Inser��o de Valores ---

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
void inserirRealIt(MAT_ENTRADA* m, long realIt){
    m->realIt = realIt;
}
void inicializarValsMatEntrada(MAT_ENTRADA* m, int ordem, short fila, double erro, long maxIt, long realIt){
    inserirOrdem(m,ordem);
    inserirFilaAval(m,fila);
    inserirErroPerm(m,erro);
    inserirMaxIt(m,maxIt);
    inserirRealIt(m,realIt);
}
void inserirElemMatA(MAT_ENTRADA* m, double elem, int posX, int posY){
    m->matA[posX][posY] = elem;
}

void inserirElemMatB(MAT_ENTRADA* m, double elem, int pos){
    m->matB[pos] = elem;
}

// --- Fun��es de Recupera��o de Valores
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
long getRealIt(MAT_ENTRADA* m){
    return(m->realIt);
}
double getElemMatA(MAT_ENTRADA* m, int posX, int posY){
    return(m->matA[posX][posY]);
}
double getElemMatB(MAT_ENTRADA* m, int pos){
    return(m->matB[pos]);
}

// --- Fun��es de Libera��o de Mem�ria
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

// --- Fun��es de Impress�o ---
void imprimirMatA(MAT_ENTRADA* m){
    int i, j;
    for(i=0;i<getOrdem(m);i++){
        for(j=0;j<getOrdem(m);j++){
            printf("%lf",getElemMatA(m, i, j));
        }
        printf("\n");
    }
}

void imprimirMatB(MAT_ENTRADA* m){

    int i;
    for(i=0;i<getOrdem(m);i++){
        if(i%15==0){
            printf("%lf\n", getElemMatB(m,i));
        }
        else{
            printf("%lf ", getElemMatB(m,i));
        }
    }
}

void imprimirInfosMatEntrada(MAT_ENTRADA* m){

    printf("Ordem da Matriz: %d\n", getOrdem(m));
    printf("Fila a ser Avaliada: %hd\n", getFilaAval(m));
    printf("Erro permitido: %.4lf\n", getErroPerm(m));
    printf("Numero maximo de iteracoes: %ld\n", getMaxIt(m));
    printf("Numero real de iteracoes: %ld\n", getRealIt(m));
}

void imprimirResultado(double *res, int tam){

    int i;

    for(i=0;i<tam;i++){
        printf("%.4lf\n", res[i]);
    }

}

// --- Fun��es Relativas ao M�todo de Jacobi-Richardson

void prepararMatriez(MAT_ENTRADA* m){

    int i, j;
    double *diagonal = (double*)malloc(getOrdem(m)*sizeof(double));

    // Salvamos os valores da diagonal da matriz A
    // em um vetor auxiliar
    for(i=0;i<getOrdem(m);i++){
        diagonal[i] = getElemMatA(m,i,i);
    }

    // Dividimos cada linha da matriz A pelo elemento da diagonal
    // e invertemos o sinal
    for(i=0;i<getOrdem(m);i++){
        for(j=0;j<getOrdem(m);j++){
            inserirElemMatA(m,-(getElemMatA(m,i,j)/diagonal[i]),i,j);
        }
    }
    // Dividimos cada elemento[i] da matriz B (que � um vetor)
    // pelo respectivo elemento[i] da diagonal de A
    for(i=0;i<getOrdem(m);i++){
        inserirElemMatB(m,getElemMatB(m,i)/diagonal[i], i);
    }

    // Agora que a diagonal auxiliar n�o � mais necess�ria
    // liberamos a mem�ria ocupada
    free(diagonal);
}

double* jacobiRichardsonSerial(MAT_ENTRADA* m, double *x0){

    int i, j, k;
    long l;
    double erroRelativo;
    double *xk = (double*)malloc(getOrdem(m)*sizeof(double));

    for(l=0;l<getMaxIt(m);l++){
        if(l%1000 == 0 ){
            printf("Iniciando a iteracao %ld.\n", l);
        }
        // Inicializa os valores de xk como "0"
        for(i=0;i<getOrdem(m);i++){
            xk[i] = 0;
        }

        k = 0;

        for(i=0;i<getOrdem(m);i++){
            for(j=0;j<getOrdem(m);j++){
                if(j!=k){
                    xk[k] += x0[j]*getElemMatA(m,i,j);
                }
            }
            k++;
        }

        for(i=0;i<getOrdem(m);i++){
            xk[i]+=getElemMatB(m,i);
        }

        erroRelativo = calcErro(x0,xk,getOrdem(m));

        if(erroRelativo <= getErroPerm(m)){
            inserirRealIt(m,l+1);
            break;
        }

        for(i=0;i<getOrdem(m);i++){
            x0[i] = xk[i];
        }
    }

    inserirRealIt(m,l+1);
    return(xk);
}

double* jacobiRichardsonParalelo(MAT_ENTRADA* m, double *x0){

}

/*
    Calculamos aqui o erro relativo que �:
    ||x(k+1)-x(k)|| / ||x(k+1)||
*/
double calcErro(double *xk, double *xkMaisUm, int tam){

    double erroRelativo = 0;
    double *aux = NULL;
    double numerador, denominador;

    aux = subtracaoVetores(xk,xkMaisUm,tam);
    numerador = calcNormaVetor(aux,tam);
    denominador = calcNormaVetor(xkMaisUm,tam);

    erroRelativo = numerador/denominador;

    return(erroRelativo);
}

/*
    Aqui escolhemos por calcular a Norma Euclidiana do vetor
    P/ calcular basta somarmos o quadrado do valor dos elementos do vetor
    e depois extrair a raiz quadrada desse total
*/
double calcNormaVetor(double *vet, int tam){

    int i;
    double norma = 0;

    for(i=0;i<tam;i++){
        norma += vet[i]*vet[i];
    }
    norma = sqrt(norma);
    return(norma);
}

double* subtracaoVetores(double *vet1, double *vet2, int tam){

    int i;
    double *resultado = (double*)malloc(tam*sizeof(double));

    for(i=0;i<tam;i++){
        resultado[i] = vet1[i]-vet2[i];
    }
    return(resultado);
}

