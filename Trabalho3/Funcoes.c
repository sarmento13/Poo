//
// Created by Maria Joao Teixeira Sarmento 2018279801
//contém todas as funções necessárias ao trabalho explicadas individualmente com comentários.
//para a listagem por letra ou gama criei as funcoes:
// compara_strings --> vai ver se a palavra que esta no nó da raiz começa pela letra/gama de letras inserida
// verifica_letra-> verifica se a letra ou conjunto de letras inserido esta correto
// print_gama_tree--> vai imprimir apenas os nós da árvore que correspondem a esse gama
// nao consegui fazer a parte da palavra e respetivo contexto porque não consegui gerir bem o meu tempo.
//

#include "Funcoes.h"
#include "lib-utf8.h"
#include <stdio.h>
#include <string.h>
#include "locale.h"
#include <stdlib.h>
#define fichpalavras "palavras.txt"


//funcao de erro
void erro(char *error){
    fprintf(stderr,"Erro em %s. Nao foi possivel realizar a operacao.\n",error);
}
//menu, vai pedir ao utilizador a opção e nao sai enquanto nao obtiver um valor viável
int menu(){
    int opc;
    printf("***********BEM VINDO************\n\n---MENU---\n1) Mostrar palavra e respetivo contexto.\n2) Listar palavras comecadas por x letra(s).\n3) Mostrar árvore. \n4) Sair\n");
    do {
        printf("Insira a opcao desejada(1,2 ou 3):" );
        scanf("%d", &opc);
    }while(opc<1 || opc>4);
    return opc;
}

//funcao que le o ficheiro de origem e guarda as palavras e posições noutro
void lerficheiro(){
    setlocale(LC_ALL, "pt_PT.utf8");

    FILE *fo, *fd; //ficheiros de origem e de destino
    char linha[100];
    char *palavra, palavrapos[20];
    char pos[5];
    int countpos=0;
    char nomefich[15];
    //pedir ao user o nome do ficheiro (que será param2.txt)
    printf("Qual o nome do ficheiro a tratar(.txt)?");
    scanf("%s",nomefich);
    fo=fopen(nomefich, "r");
    if(fo==NULL) //verificar se os ficheiros existem e se foram abertos corretamente
    {
        erro("Abertura do ficheiro origem\n");
        return;
    }
    fd=fopen("palavras.txt","w");
    if(fd==NULL)
    {
        erro("Abertura do ficheiro destino\n");
        return;
    }
    palavrapos[0]='\0'; //tirar o lixo
    while(fgets_u8(linha,1024,fo)!=NULL){ //retirar linha a linha do ficheiro de origem
        palavra=strtok(linha, " ");
        while(palavra!=NULL) { //palavra a palavra
            itoa(countpos, pos, 10); //guarda a posição em string
            countpos += (1 + (int) strlen_u8(palavra)); //atualiza a posição tendo em conta o tamanho da palavra ja guardada ( acrescenta 1 para compensar o espaço retirado)
            //retirar o lixo da primeira palavra(agora que ja foi guardada a posição)
            tiralixo(palavra,',');
            tiralixo(palavra, ' ');
            tiralixo(palavra, '\n');
            //colocar a string no formato pedido palavra=posição
            strcat(palavrapos, palavra);
            strcat(palavrapos, "=");
            strcat(palavrapos, pos);
            strcat(palavrapos, "\n");
            //colocar no ficheiro, devolve erro se nao foi possivel
            if(strlen_u8(palavra)>3){ //verificar se a palavra tem mais de 3 caracteres
                if (fputs(palavrapos, fd) == EOF) {
                    erro("Escrita no ficheiro de destino");
                    return;
                }
            }

            palavrapos[0]='\0';
            palavra = strtok(NULL, " ,!.?;:\"\n");
        }
    }
    printf("Ficheiro convertido com sucesso.\n\n");
    fclose(fo);
    fclose(fd);

}
//funcao que vai retirar os caracteres que o utilizador desejar
void tiralixo(char *palavra, char carater){
    int i=0,j=0;
    while(palavra[i]!='\0')
    {
        if(palavra[i]!=carater){
            palavra[j]=palavra[i];
            j++;
        }
        i++;
    }
    palavra[j]='\0';
}

void inicializar_arvore(struct arvore *tree){
    tree->raiz= NULL;
}

void inicializar_lista(struct listapos *lista){
    lista->tam = TAMLISTA;
    lista->entrada_lista= TAMLISTA-1;
    for(int i=0; i<TAMLISTA ; i++){
        lista->no[i].ocupado=false;
    }
}

//cria uma struct palavra com as informaçoes recebidas
struct palavra Criarpalavra(char * pal, int pos){
    struct palavra word;
    strcpy(word.pal,pal);
    word.pos=pos;
    return word;
}

//funcao que passa o conteudo do ficheiro palavras.txt para a arvore
void construir_arvore(struct arvore *tree){
    FILE *fp;
    char *palavra, *posicao;
    char linha[TAMPAL];
    struct palavra word;
    fp= fopen(fichpalavras,"r");
    if(fp==NULL){
        erro("Ao abrir o palavras.txt");
        return;
    }
    while(fgets_u8(linha,100,fp) != NULL){ //lê linha a linha guardado o par palavra posicao nas respetivas variaveis
        palavra=strtok(linha, "=");
        posicao=strtok(NULL, "\n");
        word=Criarpalavra(palavra,atoi(posicao)); //chama entao a funcao do Criarpalavra com a palavra e posicao pretendida
        put_tree_node(tree,word); // vai adicionar à arvore essa estrutura palavra
    }
    fclose(fp);
}

//cria e inicializa o nó a colocar e chama a add_tree_node para o colocar
void put_tree_node(struct arvore * tree, struct palavra pal )
{
    struct no *nodetree; //struct no criada para guardar a palavra retirada do ficheiro palavras.txt que vai ser inserida mais tarde no no da arvore
    nodetree=(struct no *)malloc(sizeof(struct no ));
    nodetree->posicoes=(struct listapos *) malloc(sizeof(struct listapos));
    nodetree->pal=pal;
    nodetree->pesq= nodetree->pdir = NULL;
    inicializar_lista(nodetree->posicoes);
    tree->raiz=add_tree_node(tree->raiz,nodetree); //vai inserir entao esse nó no nó da arvore

}

struct no *add_tree_node(struct no * ptreeroot, struct no * addnode){
    int aux;
    char paltree[50],paladd[50];
    struct posicao pos;
    if(ptreeroot == NULL){ //se a arvore esta vazia entao coloca-se o nó no inicio da raiz
        ptreeroot=addnode;
    }
    else{ //se nao vamos verificar a ordem alfabetica
        strtobase_u8(paltree,ptreeroot->pal.pal);
        strtobase_u8(paladd,addnode->pal.pal);
        if((aux=strcmp(paladd,paltree))>0){
            ptreeroot->pdir= add_tree_node(ptreeroot->pdir, addnode);
        }
        if(aux<0){
            ptreeroot->pesq = add_tree_node(ptreeroot->pesq, addnode);
        }
        if(aux==0){
            pos.pos=addnode->pal.pos;
            adicionaposicaolista(ptreeroot,pos); // se as palavras forem equivalentes vai adicionar na lista posicoes a sua posicao
        }
    }
    return ptreeroot;
}


void adicionaposicaolista(struct no *node, struct posicao pos){
    coloca(node->posicoes,pos);
}

int coloca(struct listapos *lista, struct posicao pos){
    int i, prox;
    for( i=lista->tam-1; i>=0 ; i-- ){
        if(i<0) {
            printf("Lista cheia!\n");
            return 1;
        }
        lista->no[i].pos=pos;

        if(!(lista->no[lista->entrada_lista].ocupado)){ //Fila vazia
            lista->entrada_lista=i;
            lista->no[i].nextmens = -1;
            lista->no[i].ocupado=1;
        }else {
            prox=lista->entrada_lista;
            lista->entrada_lista=i;
            lista->no[i].nextmens=prox;
            lista->no[i].ocupado=1;

        }

    }
    return 0;
}


void print_tree(struct no *raiz){
    if(raiz != NULL){
        printf("%s = %d \n",raiz->pal.pal, raiz->pal.pos);
        int i=raiz->posicoes->entrada_lista;
        if(raiz->posicoes->no[i].ocupado != false)
            printf("Restantes posicoes: ");
        while(raiz->posicoes->no[i].ocupado){
            printf("%d \n",raiz->posicoes->no[i].pos.pos);
            i=raiz->posicoes->no[i].nextmens;
            raiz->posicoes->no[i].ocupado=false;
        }
        printf("\n");
        print_tree(raiz->pesq);
        print_tree(raiz->pdir);
    }
}

//funcoes usadas para a listagem de palavras começadas c x letras

bool compara_strings(struct no *raiz, char * gama){
    if(strlen(raiz->pal.pal) == strlen(gama)){
        if(strcmp(raiz->pal.pal, gama) == 0)
            return true;
        else
            return false;
    }
    else
        for(int i=0; i< strlen(gama); i++){
            if((raiz->pal.pal[i] == gama[i]) == false){
                return false;
            }
        }
        return true;
}

void print_gama_tree(struct no *raiz, char * gama){
    if(raiz != NULL){

        if(compara_strings(raiz,gama)){

            printf("%s = %d \n",raiz->pal.pal, raiz->pal.pos);
            int i=raiz->posicoes->entrada_lista;
            if(raiz->posicoes->no[i].ocupado!=false){
                printf("Restantes posicoes: ");
            }
            while(raiz->posicoes->no[i].ocupado){
                printf("%d ",raiz->posicoes->no[i].pos.pos);
                i=raiz->posicoes->no[i].nextmens;
                raiz->posicoes->no[i].ocupado=false;
            }
            printf("\n");
        }

        print_gama_tree(raiz->pesq, gama);
        print_gama_tree(raiz->pdir, gama);
    }
}

bool verificaletra(char *letra){
    for (int i=0; i< strlen(letra) ; i++){
        if(((letra[i]>='a' && letra[i]<='z') || (letra[i]>='A' && letra[i]<='Z'))==false){
            return false;
        }
    }
    return true;
}

void mostrapalecontexto(){
    printf("mostra pal e contexto\n");
}
