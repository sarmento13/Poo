//
// Created by Acer on 18/03/2021.
//


#include "Funcoes.h"
#include <stdio.h>
#include <stdbool.h>

//funcao que verifica se os nrs sao validos
bool verifica(int n, int m){
    if(n<10 || n>40) return false;
    if(m<10 || m>40) return false;
    return true;
}
//desenhar triangulo com 1 e 0
void desenha(int lin, int col, char m[lin][col]){
    int centro;
    //colocar primeiro a matriz toda a 0
    for(int i=0; i<lin;i++){
        for(int j=0; j<col ;j++){
            m[i][j]='0';
        }
    }

    //vamos ver onde é o ponto central do triangulo para este ser isosceles
    if(col%2==0)
        centro=((col-1)/2)+1;
    else
        centro=(col/2)+1;

    //colocar a primeira linha toda a 1
    if(col%2==0){
        for(int c=0; c<col-1; c++) m[0][c]='1';
    }
    else
        for(int c=0; c<col; c++) m[0][c]='1';

    //colocar o vertice do triangulo no centro para este ser isosceles
    m[centro-1][centro-1]='1';

    //ocupar as restantes posicoes
    int aux=col-3; //col-1 dimensao -1 centro -1 pos final
    //lado direito do triangulo
    for(int l=1;l<centro-1;l++){
        m[l][l+aux-1]='1';
        aux-=2;
    }
    //lado esquerdo
    for(int l=1;l<centro-1;l++){
        m[l][l]='1';
    }

    printm(lin,col,m);
}

void alteram(int lin, int col,char m[lin][col]){
    for(int l=0; l<lin ;l++){
        for(int c=0; c<col-1 ; c++){
            if(m[l][c]=='1') {
                m[l][c] = 'W';
                if(m[l][c+1]=='0')
                    m[l][c+1]='!';
                else m[l][c+1] = 'W';
            }
            if(m[l][c]=='0')
                m[l][c]=';';

            if(m[l][c]==';' && m[l][c+1]=='1')
                m[l][c]='!';
        }

        //colocar os valores certos na ultima col caso col par
        if(col%2==0){
            for(int l=1; l<lin ; l++){
                m[l][col-1]=';';
            }
        }
    }
}

void printm(int lin, int col,char m[lin][col]){
    printf("\n");
    for(int l=0; l<lin ;l++){
        for (int c=0;c<col;c++){
            printf("%c ",m[l][c]);
        }
        printf("\n");
    }
    printf("(0,0)");
}
