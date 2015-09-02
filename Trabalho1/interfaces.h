#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

char* getCaminhoArquivo(short opcao);
struct caminhoTipo telaInicial();

struct caminhoTipo {
    char* caminho;
    char tipo;
    int threads;
};

#endif // INTERFACES_H_INCLUDED
