//
// Created by Maria João Teixeira Sarmento 2018279801
//

#ifndef TRABALHO3_FUNCOES_H
#define TRABALHO3_FUNCOES_H
#include <stdbool.h>
#include <stdio.h>
#define TAMLISTA 50
#define TAMPAL 30


//arvorebinaria
struct palavra{
    char pal[TAMPAL];
    int pos;
};

struct no{
    struct palavra pal;
    struct listapos *posicoes;
    struct no *pdir;
    struct no *pesq;
};

struct arvore{
    struct no *raiz;
};


//listaligada
struct posicao{
    int pos;
};

struct no_listapos{
    struct posicao pos;
    bool ocupado;
    int nextmens;
};

struct listapos{
    struct no_listapos no[TAMLISTA];
    int tam;
    int entrada_lista;
};

bool compara_strings(struct no *, char *);
void inicializar_lista(struct listapos *);
void construir_arvore(struct arvore *);
int coloca(struct listapos *, struct posicao );
void print_tree(struct no *);
void adicionaposicaolista(struct no * , struct posicao);
void put_tree_node(struct arvore * , struct palavra);
struct no *add_tree_node(struct no *, struct no *);
void inicializar_arvore(struct arvore *);
void tiralixo(char *, char);
int menu();
void erro(char *);
void mostrapalecontexto();
bool verificaletra(char *);
void print_gama_tree(struct no *, char *);
void lerficheiro();

#endif //TRABALHO3_FUNCOES_H
