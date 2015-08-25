#include <stdio.h>
#include <stdlib.h>
#include "matEntrada.h"
#include <string.h>

char* getCaminhoArquivo(short opcao){

    // Caminhos até cada arquivo das matrizes
    const char caminhoMat250[] = "matrizes/matriz250.txt";
    const char caminhoMat500[] = "matrizes/matriz500.txt";
    const char caminhoMat1000[] = "matrizes/matriz1000.txt";
    const char caminhoMat1500[] = "matrizes/matriz1500.txt";
    const char caminhoMat2000[] = "matrizes/matriz2000.txt";
    const char caminhoMat3000[] = "matrizes/matriz3000.txt";
    const char caminhoMat4000[] = "matrizes/matriz4000.txt";
    char* caminho = NULL;

    switch(opcao){
        case 1:
            caminho = (char*)malloc((strlen(caminhoMat250))*sizeof(char));
            strcpy(caminho,caminhoMat250);
            break;
        case 2:
            caminho = (char*)malloc((strlen(caminhoMat500))*sizeof(char));
            strcpy(caminho,caminhoMat500);
            break;
        case 3:
            caminho = (char*)malloc((strlen(caminhoMat1000))*sizeof(char));
            strcpy(caminho,caminhoMat1000);
            break;
        case 4:
            caminho = (char*)malloc((strlen(caminhoMat1500))*sizeof(char));
            strcpy(caminho,caminhoMat1500);
            break;
        case 5:
            caminho = (char*)malloc((strlen(caminhoMat2000))*sizeof(char));
            strcpy(caminho,caminhoMat2000);
            break;
        case 6:
            caminho = (char*)malloc((strlen(caminhoMat3000))*sizeof(char));
            strcpy(caminho,caminhoMat3000);
            break;
        case 7:
            caminho = (char*)malloc((strlen(caminhoMat4000))*sizeof(char));
            strcpy(caminho,caminhoMat4000);
            break;
    }

    return(caminho);
}

char* telaInicial(short opInicial){

    short opcao = opInicial;
    char* caminho = NULL;

    if(opcao == -1){
        printf("\t\tSSC0143 - Programacao Concorrente - Turma A\n");
        printf("\t\t Trabalho 01 - Metodo de Jacobi-Richardson\n\n");
        printf("\tAlunos: Fabio Alves Martins Pereira (Num.USP: 7987435)\n\n");
        printf("\t\t\t\tMenu Principal\n\n");
        printf("\t1 - Carregar Matriz de 250 elementos\n");
        printf("\t2 - Carregar Matriz de 500 elementos\n");
        printf("\t3 - Carregar Matriz de 1000 elementos\n");
        printf("\t4 - Carregar Matriz de 1500 elementos\n");
        printf("\t5 - Carregar Matriz de 2000 elementos\n");
        printf("\t6 - Carregar Matriz de 3000 elementos\n");
        printf("\t7 - Carregar Matriz de 4000 elementos\n\n");
        printf("\tEscolha uma opcao: ");
        scanf("%hd", &opcao);
    }

    caminho = getCaminhoArquivo(opcao);

    return(caminho);
}

int main (int argc, char* argv[]){

    // Variáveis auxiliares para leitura do arquivo
    int i, j;
    int auxInt;
    short auxShort;
    double auxDouble;
    long auxLong;
    char* caminhoMat = telaInicial(-1);

    // Ponteiro para o arquivo que será aberto
    FILE* arqMat = NULL;
    // Cria a estrutura que armazenará as matrizes
    MAT_ENTRADA* m = criarMatEntrada();

    arqMat = fopen(caminhoMat,"r");

    if(arqMat == NULL){
        printf("Erro ao abrir arquivo.");
    }
    else{
        // Le as primeiras informações do arquivo
        fscanf(arqMat, "%d", &auxInt);
        fscanf(arqMat, "%hd", &auxShort);
        fscanf(arqMat, "%lf", &auxDouble);
        fscanf(arqMat, "%ld", &auxLong);
        // Salva os valores na estrutura
        inicializarValsMatEntrada(m,auxInt,auxShort,auxDouble,auxLong);
        // Aloca espaço para as matrizes A e B, agora que sabemos sua dimensão
        alocarMatA(m);
        alocarMatB(m);
        // Insere os elementos na Matriz A
        for(i=0;i<getOrdem(m);i++){
            for(j=0;j<getOrdem(m);j++){
                fscanf(arqMat,"%d",&auxInt);
                inserirElemMatA(m,auxInt,i,j);
            }
        }
        // Insere os elementos na Matriz B
        for(i=0;i<getOrdem(m);i++){
            fscanf(arqMat,"%d",&auxInt);
            inserirElemMatB(m,auxInt,i);
        }
        // Fecha o arquivo agora que não precisamos mais dele
        fclose(arqMat);

        imprimirInfosMatEntrada(m);
    }

    // Libera a memória alocada pela estrutura
    destruirMatEntrada(m);

    return 0;
}
