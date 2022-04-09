//Created by Maria João Teixeira Sarmento 2018279801

#include "Funcoes.h"
#include <locale.h>

int main( )
{
    setlocale(LC_ALL, "pt_PT.utf8");

    int opc;
    char letras[10];
    letras[0]='\0';

    lerficheiro();
    struct arvore tree;
    inicializar_arvore(&tree);
    //tree.raiz->posicoes=NULL;
    construir_arvore(&tree);

    do {
        opc= menu();
        switch (opc) {
            case 1:
                mostrapalecontexto();
                break;
            case 2:
                do{
                    printf("Insira a letra ou gama de letras desejada: ");
                    scanf("%s", letras);
                }while(verificaletra(letras) == false);
                print_gama_tree(tree.raiz,letras);
                break;
            case 3:
                print_tree(tree.raiz);
            default:
                break;
        }
    }while(opc != 4);
    return 0;
}
