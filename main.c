#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
typedef struct{
    int conteudo;

}Posicao;
//0 = vazio, 1= branca, 2= preta, 3 dama branca, 4 dama preta

void imprimeMatriz();
void preencheMatrizInicial();

void limpaBuffer();

Posicao tabuleiro[8][8];
int main()
{   int posicao[2];


    preencheMatrizInicial();
    imprimeMatriz();


    return 0;
}

void preencheMatrizInicial(){
    int flag=2;

    for(int i=0;i<3;i++){
        for(int j=0;j<8;j++){
            if((j%2==0 & i%2==0) || (j%2==1 & i%2==1)){
                    tabuleiro[i][j].conteudo=1;
            }

        }
    }
     for(int i=5;i<8;i++){
        for(int j=0;j<8;j++){
            if((j%2==0 & i%2==0) || (j%2==1 & i%2==1)){
                    tabuleiro[i][j].conteudo=2;
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
            if(tabuleiro[i][j].conteudo==1 ||tabuleiro[i][j].conteudo==2){
                if(tabuleiro[i][j].conteudo==1)printf("B | ");
                if(tabuleiro[i][j].conteudo==2)printf("P | ");

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
