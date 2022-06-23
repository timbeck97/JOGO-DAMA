#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
typedef struct{
    char cor;

}Peca;


void imprimeMatriz();
void preencheMatrizInicial();
Peca criaPeca(char cor);
void limpaBuffer();

Peca tabuleiro[8][8];
int main()
{   int posicao[2];


    preencheMatrizInicial();
    imprimeMatriz();


    return 0;
}
Peca criaPeca(char cor){
    Peca peca;
    peca.cor=cor;
    return peca;
}
void preencheMatrizInicial(){
    int flag=2;

    for(int i=0;i<3;i++){
        for(int j=0;j<8;j++){
            if((j%2==0 & i%2==0) || (j%2==1 & i%2==1)){
                    tabuleiro[i][j].cor='B';
            }

        }
    }
     for(int i=5;i<8;i++){
        for(int j=0;j<8;j++){
            if((j%2==0 & i%2==0) || (j%2==1 & i%2==1)){
                    tabuleiro[i][j].cor='P';
            }


        }
    }
}
void imprimeMatriz(){
    //codigo abaixo para imprimi a matriz
    printf("    ");
    for(int a=1;a<=8;a++) printf("%d   ",a);
    printf("\n");
    for(int i=0;i<8;i++){
        printf(" %c| ",i+65);
        for(int j=0;j<8;j++){
            if(tabuleiro[i][j].cor==66 ||tabuleiro[i][j].cor==80){
                printf("%c | ",tabuleiro[i][j].cor);
            }else{
                printf("  | ");
            }
        }

    printf("\n");
    }
}

void digitaPosicao(int posicao[]){
    char dado[2];
    printf("Digite a posicao (ex: a5)");
    scanf("%[^\n]",dado);
    limpaBuffer();
    dado[0]=toupper(dado[0]);
    while((dado[0]<65 || dado[0]>72) ){ // verifica se o primeiro digito é letra e o segundo se é um numero de 1 a 9 (2 digitos, ex: a8)
        printf("Digite uma posicao correta: ");
        scanf("%[^\n]",dado);
        limpaBuffer();
        dado[0]=toupper(dado[0]);
    }
     while(dado[1]<49 || dado[1] >56){ // verifica se o primeiro digito é letra e o segundo se é um numero de 1 a 9 (2 digitos, ex: a8)
        printf("Digite uma posicao correta: ");
        scanf("%[^\n]",dado);
        limpaBuffer();
        dado[1]=toupper(dado[1]);
    }
    posicao[0]=dado[0]-64;
    posicao[1]=dado[1]-48;

}
void limpaBuffer(){
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}
