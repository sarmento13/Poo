//
// Created by Acer on 22/04/2021.
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "lib-utf8.h"
#include "estruturas.h"

#ifndef TRABALHO2_FUNCOES_H
#define TRABALHO2_FUNCOES_H
//
// NOTA: alterei o fopen da funcao ler texto
//

//vai adicionar as palavras do texto já partidas a cada nó da fila para a qual pf aponta
void colocar_ordenado(char *texto, struct fila *pf){
    char *aux;
    aux=strtok(texto," ");
    while(aux!=NULL){
        int i=TAMFILA-1;
        if(pf->no[TAMFILA-1].ocupado==0){ //se a fila esta vazia
            pf->no[TAMFILA-1].ocupado=1;
            pf->no[TAMFILA-1].p.pal=aux;
            i--;
        }
        pf->tam=tamLista(pf);
        if(pf->tam == TAMFILA) { //ve se a fila esta cheia
            printf("Fila cheia");
        }
        //comparar a nova palavra com as existentes na lista
        while(pf->no[i].ocupado){
            if(comparachars(aux,pf->no[i].p.pal)==1){
                trocapals(pf,i,aux);
                break;
            }
            if(comparachars(aux,pf->no[i].p.pal)==0){ //se forem iguais coloca a na posição a sua frente
                trocapals(pf,i+1,aux);
                break;
            }
            if(comparachars(aux,pf->no[i].p.pal)==2){ //se nao houver palavras "maiores" do que a nova palavra vamos procurar pela ultima posicao a para colocar
                if(pf->no[i-1].p.pal==NULL && i!=0){ //se é a ultima posicao e se nao é o fim da fila
                    pf->no[i-1].ocupado=1;
                    pf->no[i-1].p.pal=aux;
                }
            }
            i--;
        }
        aux=strtok(NULL, " ,.!?\";:\n()");
    }
}
int comparachars(char *pal1, char *pal2){ //vai ver se a pal1 vem primeiro do que a pal2 se sim retorna 1 se iguais 0 se pal2 for primeiro retorna 2
    if((strlen(pal1)>2) && (strlen(pal2)>2)) { //verifica primeiro se ambas tem comprimento necessario
        if (pal1[0] < pal2[0]) return 1;
        if (pal1[0] > pal2[0]) return 2;
        if (pal1[0] == pal2[0]) {
            if (pal1[1] < pal2[1]) return 1;
            if (pal1[1] > pal2[1]) return 2;
            if (pal1[1] == pal2[1]) {
                if (strlen(pal1) > strlen(pal2))
                    return 1;
                if (strlen(pal1) < strlen(pal2))
                    return 2;
                if (strlen(pal1) == strlen(pal2))
                    return 0;
            }
        }
    }
    else{ //se as palavras tiverem menos de 2 caracteres.
        if (pal1[0] < pal2[0]) return 1;
        if (pal1[0] > pal2[0]) return 2;
        if (pal1[0] == pal2[0]) {
            if (strlen(pal1) > strlen(pal2))
                return 1;
            if (strlen(pal1) < strlen(pal2))
                return 2;
            if (strlen(pal1) == strlen(pal2))
                return 0;
        }
    }


    return -1;
}

int trocapals(struct fila *pf, int indicep1 ,char * pal2) {
    int tam=TAMFILA-tamLista(pf); // tam guarda a ultima posicao ocupada da lista
    pf->no[tam-1].ocupado=1; //coloca a posicao anterior à ultima ocupada

    //vai mover a lista toda 1 casa para tras de modo a arranjar espaço para a nova palavra que se vai inserir na lista na posicao do indicep1
    for(int i=tam-1; i<indicep1 && pf->no[i].ocupado ; i++){
        pf->no[i].p = pf->no[i+1].p;
        pf->no[i].ocupado=1;
    }
    pf->no[indicep1].p.pal=pal2;
    return 1;
}
//vai contar quantas sao as repeticoes de cada palavra e retirar a pal repetida
void contaRepeticoes(struct fila *pf){

    int count=0;
    int j,i,k;
    if(pf->no[TAMFILA-1].ocupado==0){
        printf("Fila esta vazia");
        return;
    }
    for(i=TAMFILA-1; i>=0 && pf->no[i].ocupado; i--){
        count++;
        pf->no[i].p.nr_ocorrencias=count; //conta logo 1 palavra
        for(j=i-1; j>=0 && pf->no[j].ocupado; j--){
            if(strcmp(pf->no[i].p.pal,pf->no[j].p.pal)==0) {
                count++;
                pf->no[i].p.nr_ocorrencias = count;
                for(k=j-1; k>=0 && pf->no[k].ocupado ; k--){ //anda-se com a fila para a frente de modo a retirar o no j
                    pf->no[k+1].p = pf->no[k].p;
                }
                pf->no[k+1].ocupado=0;
            }
        }
        count=0;

    }

}



//retira um a um elemento da fila
bool retirar(struct fila *pf,struct palavra *pal){
    int i;
    if(pf->no[TAMFILA-1].ocupado == 0){ //se a fila esta vazia
        return false;
    }
    *pal=pf->no[TAMFILA-1].p; //guarda o ultimo elemento
    for(i=TAMFILA-2; i>=0 && pf->no[i].ocupado ; i--){ //move a lista para a frente
        pf->no[i+1].p = pf->no[i].p;
    }
    pf->no[i+1].ocupado=0;
    return true;
}

//devolve o tamanho da lista
int tamLista(struct fila *pf){
    int i=TAMFILA-1;
    int count=0;
    while((pf->no[i].p.pal!= NULL) && (pf->no[i].ocupado==1)) {
        count++;
        i--;
    }
    return count;
}

void maior_ocorr(struct fila *pf, struct palavra *pal){
    int i;
    int ocorr=pf->no[TAMFILA-1].p.nr_ocorrencias;
    for(i=TAMFILA-2; i>TAMFILA-(pf->tam) && pf->no[i].ocupado ;i--){
        if(pf->no[i].p.nr_ocorrencias>ocorr){
            ocorr=pf->no[i].p.nr_ocorrencias;
            *pal=pf->no[i].p;
        }
    }
    printf("A palavra com maior ocorrencia e: \"%s\" com %d ocorrencias\n",pal->pal,pal->nr_ocorrencias);

}

//coloca numa string, a partir do ponteiro recebido, o conteúdo do ficheiro "texto.txt"
//o espaço para que "ptexto" aponta tem de ter pelo menos MAX_TEXTO+1 bytes
//devolve true se a leitura correu bem
//devolve false se o ficheiro não existe, ou é grande demais (tem mais de MAX_TEXTO bytes)

bool ler_texto(char *ptexto) {
    FILE *fich1;
    int i, c;
    fich1 = fopen("C:\\Users\\Acer\\Desktop\\2Ano\\2semestre\\CLionProjects\\Trabalho2\\texto.txt", "r"); //******Alterei isto pois o meu clion nao carregava o ficheiro
    if (fich1 == NULL) {
        // Ficheiro texto.txt não existe
        return false;
    }
    i = 0;
    while (i < (MAX_TEXTO) && (c = fgetc(fich1)) != EOF) {
        ptexto[i] = (char) c;
        // detetar e eliminar o UTF BOM
        if (i == 2 && ptexto[0] == (char)0xEF && ptexto[1] == (char) 0xBB && ptexto[2] == (char) 0xBF)
            i = 0;
        else
            i++;
    }
    ptexto[i] = 0;
    i++;
    fclose(fich1);
    if (i <= MAX_TEXTO)
        return true;
    else
        // limite de bytes ultrapassado
        return false;
}

#endif //TRABALHO2_FUNCOES_H
