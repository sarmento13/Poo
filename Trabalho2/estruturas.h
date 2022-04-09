//
// Created by Acer on 22/04/2021.
//

#ifndef TRABALHO2_ESTRUTURAS_H
#define TRABALHO2_ESTRUTURAS_H


#define MAX_TEXTO 10000



struct palavra{
    char *pal;
    int nr_ocorrencias;
};
struct no_fila{
    struct palavra p;
    int ocupado;
};

#define TAMFILA (MAX_TEXTO+1)
struct fila{
    struct no_fila no[TAMFILA];
    int tam;
};


bool ler_texto(char *);
bool retirar(struct fila *,struct palavra *);
int tamLista(struct fila *);
void contaRepeticoes(struct fila *);
void colocar_ordenado(char *, struct fila *);
void maior_ocorr(struct fila *, struct palavra *);
int comparachars(char * , char *);
int trocapals(struct fila * ,int , char *);


#endif //TRABALHO2_ESTRUTURAS_H
