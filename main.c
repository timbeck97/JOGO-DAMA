#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINHAS "ABCDEFGH"
const int COLUNAS[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

typedef struct {
    int coordenadaCaptura[2];

} Capturar;
typedef struct {
    int coordenada[2];
    Capturar podeCapturar[3];
} Coordenada;



// 0 = vazio,
// 1 = branca,
// 2 = preta,
// 3 = dama branca,
// 4 = dama preta
typedef struct {
    int conteudo;
    Coordenada posicao;
} Posicao;

void imprimeMatriz();
void preencheMatrizInicial();
void movePeca();
Coordenada *calculaPosicoesPossiveis();
void realizaMovimento();
int verificaPosicaoDigitada();
Coordenada retornaCoordernada();
void limpaBuffer();

int main(int argc, char **argv[]) {
    Posicao tabuleiro[8][8];
    int *posicaoInt;
    int jogadorAtual = 0;

    // checa se tem 2 argumentos
    // if (argc != 2) {
    //     printf("Erro: quantidade de argumentos invalida\n");
    //     return 1;
    // }

    preencheMatrizInicial(tabuleiro);


    while (true) {
        imprimeMatriz(tabuleiro);
        movePeca(tabuleiro, jogadorAtual);
        jogadorAtual++;

    }

    return 0;
}

void preencheMatrizInicial(Posicao tabuleiro[8][8]) {
    int flag = 2;

    // fill array with empty positions

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tabuleiro[i][j].conteudo = 0;
            tabuleiro[i][j].posicao.coordenada[0] = i;
            tabuleiro[i][j].posicao.coordenada[1] = j;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            if ((j % 2 == 0 & i % 2 == 0) || (j % 2 == 1 & i % 2 == 1)) {
                tabuleiro[i][j].conteudo = 1;
            }
        }
    }
    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((j % 2 == 0 & i % 2 == 0) || (j % 2 == 1 & i % 2 == 1)) {
                tabuleiro[i][j].conteudo = 2;
            }
        }
    }
}

void imprimeMatriz(Posicao tabuleiro[8][8]) {
    system("clear||cls");
    // codigo abaixo para imprimi a matriz
    printf("    ");
    for (int a = 1; a <= 8; a++) printf("%d   ", a);
    printf("\n");
    for (int i = 0; i < 8; i++) {
        printf(" %c| ", i + 65);
        for (int j = 0; j < 8; j++) {
            if (tabuleiro[i][j].conteudo == 1 || tabuleiro[i][j].conteudo == 2) {
                if (tabuleiro[i][j].conteudo == 1) printf("B | ");
                if (tabuleiro[i][j].conteudo == 2) printf("P | ");

            } else {
                printf("  | ");
            }
        }

        printf("\n");
    }
}

// retorna um array de coordenada [linha, coluna]
int *digitaPosicao(int jogada, int posicao) {
    char dado[2];
    static int posicaoInicial[2];
    static int posicaoFinal[2];
    if (jogada == 1) printf("Digite a posicao da peça a ser movida (ex: a5)");
    if (jogada == 2) printf("Digite a posicao que deseja mover (ex: b4)");
    scanf("%[^\n]", dado);
    limpaBuffer();
    dado[0] = toupper(dado[0]);
    while ((dado[0] < 65 || dado[0] > 72)) {  // verifica se o primeiro digito é letra e o segundo se é um numero de 1 a 9 (2 digitos, ex: a8)
        printf("Digite uma posicao correta: ");
        scanf("%[^\n]", dado);
        limpaBuffer();
        dado[0] = toupper(dado[0]);
    }
    while (dado[1] < 49 || dado[1] > 56) {  // verifica se o primeiro digito é letra e o segundo se é um numero de 1 a 9 (2 digitos, ex: a8)
        printf("Digite uma posicao correta: ");
        scanf("%[^\n]", dado);
        limpaBuffer();
        dado[1] = toupper(dado[1]);
    }
    if(posicao==1){
        posicaoInicial[0] = dado[0] - 64 - 1;
        posicaoInicial[1] = dado[1] - 48 - 1;
        //printf("posicoes digitadas: %d %d\n", posicaoInicial[0], posicaoInicial[1]);
        return posicaoInicial;
    }else{
        posicaoFinal[0] = dado[0] - 64 - 1;
        posicaoFinal[1] = dado[1] - 48 - 1;
        //printf("posicoes digitadas: %d %d\n", posicaoFinal[0], posicaoFinal[1]);
        return posicaoFinal;
    }

}



Coordenada *calculaPosicoesPossiveis(int coordenada[2], Posicao tabuleiro[8][8], int jogadorAtual, int *tamanhoArray, int *qttPecasComiveis) {


    static Coordenada posicoesPossiveis[10];
    int contador = 0;
    int corDoJogador;
    int captura=0;
    // 1 = branca, 2 = preta
    if (jogadorAtual % 2 == 0) {
        corDoJogador = 1;
    } else {
        corDoJogador = 2;
    }

    // peças brancas
    if (corDoJogador == 1) {

            if (tabuleiro[coordenada[0] + 1][coordenada[1] + 1].conteudo == 2) {

                if (tabuleiro[coordenada[0] + 2][coordenada[1] + 2].conteudo == 0 && coordenada[1]<=5) {
                    // jogada possivel
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] + 2;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] + 2;

                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[0]=coordenada[0]+1;
                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[1]=coordenada[1]+1;
                    captura++;
                    contador++;
                }
            }

            if (tabuleiro[coordenada[0] + 1][coordenada[1] - 1].conteudo == 2) {
                if (tabuleiro[coordenada[0] + 2][coordenada[1] - 2].conteudo == 0 && coordenada[1]>=2) {
                    // jogada possivel
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] + 2;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] - 2;

                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[0]=coordenada[0]+1;
                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[1]=coordenada[1]-1;
                    captura++;

                    contador++;
                }
            }

        // movimentos simples - branca
            if(coordenada[1]<=7){
                if (tabuleiro[coordenada[0] + 1][coordenada[1] + 1].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] + 1;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] + 1;

                    contador++;
                }
            }
            if(coordenada[1]>=1){
                if (tabuleiro[coordenada[0] + 1][coordenada[1] - 1].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] + 1;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] - 1;
                    contador++;
                }
            }
    }
    // peças pretas
    if (corDoJogador == 2) {

            if (tabuleiro[coordenada[0] - 1][coordenada[1] - 1].conteudo == 1 && coordenada[1]>=2) {
                if (tabuleiro[coordenada[0] - 2][coordenada[1] - 2].conteudo == 0 ) {
                    // jogada possivel
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] - 2;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] - 2;

                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[0]=coordenada[0]-1;
                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[1]=coordenada[1]-1;
                    captura++;
                    contador++;
                }
            }

            if (tabuleiro[coordenada[0] - 1][coordenada[1] + 1].conteudo == 1 && coordenada[1]<=5) {
                if (tabuleiro[coordenada[0] - 2][coordenada[1] + 2].conteudo == 0 ) {
                    // jogada possivel
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] - 2;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] + 2;

                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[0]=coordenada[0]-1;
                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[1]=coordenada[1]+1;
                    captura++;
                    contador++;
                }
            }

        // movimentos simples - preta
            if(coordenada[1]<=7){
                if (tabuleiro[coordenada[0] - 1][coordenada[1] + 1].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] - 1;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] + 1;
                    contador++;
                }
            }
            if(coordenada[1]>=1){
                if (tabuleiro[coordenada[0] - 1][coordenada[1] - 1].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] - 1;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] - 1;
                    contador++;
                }
            }


    }
    printf("\n\nquantiodade de movimentos possiveis : %d\n",contador);
        *qttPecasComiveis=captura;
        *tamanhoArray=contador;

        return posicoesPossiveis;
}
void realizaMovimento(Coordenada *movimentosPossiveis, Posicao tabuleiro[8][8], int jogadorAtual, int tamanhoArray,int qttPecasComiveis,int coordenadaInicial[2],int coordenadaFinal[2]){


    tabuleiro[coordenadaInicial[0]][coordenadaInicial[1]].conteudo=0;
    if(jogadorAtual%2==1){
        tabuleiro[coordenadaFinal[0]][coordenadaFinal[1]].conteudo=2;
        if(qttPecasComiveis>0){
           Coordenada coordenadaComida = retornaCoordernada(movimentosPossiveis, tamanhoArray, coordenadaFinal);
           tabuleiro[coordenadaComida.podeCapturar[0].coordenadaCaptura[0]][coordenadaComida.podeCapturar[0].coordenadaCaptura[1]].conteudo=0;

        }

    }else{
        tabuleiro[coordenadaFinal[0]][coordenadaFinal[1]].conteudo=1;
        if(qttPecasComiveis>0){
           Coordenada coordenadaComida = retornaCoordernada(movimentosPossiveis, tamanhoArray, coordenadaFinal);
           tabuleiro[coordenadaComida.podeCapturar[0].coordenadaCaptura[0]][coordenadaComida.podeCapturar[0].coordenadaCaptura[1]].conteudo=0;
        }
    }



}
int verificaPosicaoDigitada(Coordenada *movimentosPossiveis, int tamanhoArray, int coordenadaFinal[2]){
    int flagLinha=0;
    int flagColuna=0;

    for(int i=0;i<tamanhoArray;i++){
        if(movimentosPossiveis[i].coordenada[0]==coordenadaFinal[0])flagLinha=1;
        if(movimentosPossiveis[i].coordenada[1]==coordenadaFinal[1])flagColuna=1;
    }
    //printf("\n\nflag linha: %d\nFlag coluna: %d\n\n",flagLinha,flagColuna);
    if(flagColuna==0 || flagLinha==0) return 0;
    else return 1;
}
Coordenada retornaCoordernada(Coordenada *movimentosPossiveis, int tamanhoArray, int coordenadaFinal[2]) {
    for(int i=0;i<=tamanhoArray;i++){
        if(movimentosPossiveis[i].coordenada[0]== coordenadaFinal[0] && movimentosPossiveis[i].coordenada[1]== coordenadaFinal[1] ){
            return movimentosPossiveis[i];
        }
    }

}
void movePeca(Posicao tabuleiro[8][8], int jogadorAtual) {
    int *coordenadaInicial;
    int *coordenadaFinal;
    int tamanhoArray;
    int qttPecasComiveis;
    Coordenada *movimentosPossiveis;

    coordenadaInicial = digitaPosicao(1,1);
    while (tabuleiro[coordenadaInicial[0]][coordenadaInicial[1]].conteudo == 0) {
        printf("\nPosicao invalida\n");
        coordenadaInicial = digitaPosicao(1,1);
    }

    movimentosPossiveis = calculaPosicoesPossiveis(coordenadaInicial, tabuleiro, jogadorAtual, &tamanhoArray, &qttPecasComiveis);

    printf("\n");
    //for apenas para verificar os possiveis movimentos
    for(int i=0;i<tamanhoArray;i++){
        printf("Movimentos possiveis: %d, %d\n", movimentosPossiveis[i].coordenada[0], movimentosPossiveis[i].coordenada[1]);
    }
    if(qttPecasComiveis>0){
        for(int i=0;i<qttPecasComiveis;i++){
            printf("Pecas comíveis: %d, %d\n", movimentosPossiveis[i].podeCapturar[i].coordenadaCaptura[0], movimentosPossiveis[i].podeCapturar[i].coordenadaCaptura[1]);
        }
    }

     coordenadaFinal=digitaPosicao(2,2);

    int verifica= verificaPosicaoDigitada(movimentosPossiveis, tamanhoArray, coordenadaFinal);
    while(!verifica){
        printf("DIGITE UMA POSICAO VALIDA DENTRE AS OPCOES\n");
        coordenadaFinal =digitaPosicao(2,2);
        verifica= verificaPosicaoDigitada(movimentosPossiveis, tamanhoArray, coordenadaFinal);
    }

    realizaMovimento(movimentosPossiveis, tabuleiro, jogadorAtual, tamanhoArray,qttPecasComiveis, coordenadaInicial,coordenadaFinal);




}

void limpaBuffer() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}
