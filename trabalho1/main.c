#include <stdio.h>
#include <stdbool.h>
#include "Funcoes.h"


int main() {
    int lin,col;
    do {
        printf("Insira o tam de linhas e colunas: ");
        scanf("%d %d", &lin, &col);
    }while(verifica(lin,col)==false);
    char matriz[lin][col];
    desenha(lin, col,matriz);
    alteram(lin,col,matriz);
    printm(lin,col,matriz);

    return 0;
}

