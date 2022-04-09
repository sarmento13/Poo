#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lib-utf8.h"
#include "estruturas.h"
#include "funcoes.h"
#include <locale.h>



int main() {
    char textoaux[MAX_TEXTO+1];
    char texto[MAX_TEXTO+1];
    struct palavra pal,palocorr;

    setlocale(LC_ALL, ""); //nao funciona no meu CLION, acabei por resolver o exercicio com o texto auxiliar

    if(ler_texto(texto)==true)
        printf("\nTexto lido c sucesso\n");
    else
        printf("\nTexto n lido");

    strtobase_u8(textoaux,texto);

    printf("*****TEXTO******\n%s\n******FIM DE TEXTO*****\n\n\n", textoaux);
    struct fila fifo;

    for (int i = 0; i < TAMFILA; i++)
        fifo.no[i].ocupado = false;

    colocar_ordenado(textoaux,&fifo);

    fifo.tam=tamLista(&fifo);
    printf("NR palavras: %d\n",fifo.tam);
    contaRepeticoes(&fifo);


    //ver qual tem o maior nr de ocorrencias
    maior_ocorr(&fifo,&palocorr);

    //imprime no formato pedido
    for(int i=0; i<fifo.tam+1; i++) {
        if (retirar(&fifo, &pal)){
            if(pal.nr_ocorrencias-(int)strlen(pal.pal)>0){
                if(strcmp(pal.pal,palocorr.pal)!=0){
                    int espacos=pal.nr_ocorrencias-(int)strlen(pal.pal);
                    while(espacos!=0){
                        printf(" ");
                        espacos--;
                    }
                }
                else{
                    int count=90-(int)strlen(pal.pal);
                    while(count!=0){
                        printf(" ");
                        count--;
                    }

                }


            }
            printf("%s\n", pal.pal);
        }
        else {
            printf("A fila esta vazia!");
            break;
        }

    }
    return 0;
}