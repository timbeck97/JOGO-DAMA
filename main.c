#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int coordenadaCaptura[2];

} Capturar;
typedef struct {
    int coordenada[2];
    Capturar podeCapturar[3];
    int qttPecasPermiteCaptuar;
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
void imprimeTurnoJogador();
void movimentosDama();
void limpaBuffer();
int verificaFimDoJogo();
void formataMovimentosPossiveis();

int main() {
    Posicao tabuleiro[8][8];
    int *posicaoInt;
    int jogadorAtual = 0;
    int pontosBrancas = 0, pontosPretas = 0;
    int continua = 0;

    // checa se tem 2 argumentos
    // if (argc != 2) {
    //     printf("Erro: quantidade de argumentos invalida\n");
    //     return 1;
    // }

    preencheMatrizInicial(tabuleiro);

    while (!continua) {
        imprimeMatriz(tabuleiro, pontosBrancas, pontosPretas);
        movePeca(tabuleiro, jogadorAtual, &pontosBrancas, &pontosPretas);
        imprimeMatriz(tabuleiro, pontosBrancas, pontosPretas);
        continua = verificaFimDoJogo(jogadorAtual, tabuleiro);
        jogadorAtual++;
        if (continua == 1) printf("\n\n--->Nao existem mais movimentos para a cor Branca<---\n");
        if (continua == 2) printf("\n\n--->Nao existem mais movimentos para a cor Preta<---\n");
    }
    if (pontosBrancas > pontosPretas) {
        printf("--->BRANCAS GANHARAM<---");
    } else {
        printf("--->PRETAS GANHARAM<---");
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
    /*
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            // for (int j = 5; j < 8; j++) { // ALTEREI ESSA LINHA PRA PODER TESTAR AS DAMAS MAIS RAPIDO SACASTES?
            if ((j % 2 == 0 & i % 2 == 0) || (j % 2 == 1 & i % 2 == 1)) {
                tabuleiro[i][j].conteudo = 1;
            }
        }
    }
    for (int i = 5; i < 8; i++) {
        // for (int j = 5; j < 8; j++) {
        for (int j = 0; j < 8; j++) {
            if ((j % 2 == 0 & i % 2 == 0) || (j % 2 == 1 & i % 2 == 1)) {
                tabuleiro[i][j].conteudo = 2;
            }
        }
    }
    */

    /*
    tabuleiro[4][2].conteudo=2;
    tabuleiro[3][5].conteudo=1;
    tabuleiro[1][3].conteudo=1;
    tabuleiro[1][5].conteudo=1;
    tabuleiro[2][4].conteudo=4;
    */

    /*
    //testar branca diagonal direita
    tabuleiro[1][2].conteudo=2;
    tabuleiro[3][4].conteudo=2;
    tabuleiro[0][1].conteudo=1;
    */
    /*
    //testar branca diagonal esquerda
    tabuleiro[1][5].conteudo=1;
    tabuleiro[4][2].conteudo=2;
    tabuleiro[2][4].conteudo=2;
    */

    /*
    //testar preta diagonal esquerda
    tabuleiro[7][4].conteudo=2;
    tabuleiro[6][3].conteudo=1;
    tabuleiro[4][1].conteudo=1;
    tabuleiro[0][0].conteudo=1;
    */

    // testar preta diagonal direita
    // tabuleiro[7][2].conteudo = 2;
    // tabuleiro[6][3].conteudo = 1;
    // tabuleiro[4][5].conteudo = 1;
    // tabuleiro[0][2].conteudo = 1;

    // testar preta diagonal direta come 2 pecas ===============================BUG 1
    // tabuleiro[7][2].conteudo = 2;
    // tabuleiro[6][3].conteudo = 1;
    // tabuleiro[4][5].conteudo = 1;
    // tabuleiro[0][2].conteudo = 1;
    // tabuleiro[4][3].conteudo = 1;

    // testar dama preta come dama branca ================================ BUG 2
    // tabuleiro[0][7].conteudo = 4;
    // tabuleiro[4][3].conteudo = 3;
    // tabuleiro[0][0].conteudo = 1;

    // testar dama preta come peca branca normal
    // tabuleiro[0][7].conteudo = 4;
    // tabuleiro[4][3].conteudo = 1;
    // tabuleiro[0][0].conteudo = 1;

    // testar dama branca come peca preta normal
    tabuleiro[0][7].conteudo = 3;
    tabuleiro[4][3].conteudo = 2;
    tabuleiro[0][0].conteudo = 1;

    // testar
}

void imprimeMatriz(Posicao tabuleiro[8][8], int pontosBrancas, int pontosPretas) {
    system("clear||cls");
    // codigo abaixo para imprimi a matriz
    printf("    ");
    for (int a = 1; a <= 8; a++) printf("%d   ", a);
    printf("\n");
    for (int i = 0; i < 8; i++) {
        printf(" %c| ", i + 65);
        for (int j = 0; j < 8; j++) {
            if (tabuleiro[i][j].conteudo == 1 || tabuleiro[i][j].conteudo == 2 || tabuleiro[i][j].conteudo == 3 || tabuleiro[i][j].conteudo == 4) {
                if (tabuleiro[i][j].conteudo == 1) printf("B | ");
                if (tabuleiro[i][j].conteudo == 2) printf("P | ");
                if (tabuleiro[i][j].conteudo == 3) printf("X | ");
                if (tabuleiro[i][j].conteudo == 4) printf("Y | ");

            } else {
                printf("  | ");
            }
        }
        if (i == 2) {
            printf("  BRANCAS -> %d pontos", pontosBrancas);
        }
        if (i == 3) {
            printf("  PRETAS  -> %d pontos", pontosPretas);
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
    if (posicao == 1) {
        posicaoInicial[0] = dado[0] - 64 - 1;
        posicaoInicial[1] = dado[1] - 48 - 1;
        // printf("posicoes digitadas: %d %d\n", posicaoInicial[0], posicaoInicial[1]);
        return posicaoInicial;
    } else {
        posicaoFinal[0] = dado[0] - 64 - 1;
        posicaoFinal[1] = dado[1] - 48 - 1;
        // printf("posicoes digitadas: %d %d\n", posicaoFinal[0], posicaoFinal[1]);
        return posicaoFinal;
    }
}

Coordenada *calculaPosicoesPossiveis(int coordenada[2], Posicao tabuleiro[8][8], int jogadorAtual, int *tamanhoArray, int *qttPecasComiveis) {
    static Coordenada posicoesPossiveis[20];
    int contador = 0;
    int corDoJogador;
    int captura = 0;
    // 1 = branca, 2 = preta
    if (jogadorAtual % 2 == 0) {
        corDoJogador = 1;
    } else {
        corDoJogador = 2;
    }
    int i = coordenada[0];
    int j = coordenada[1];
    // precisa do for abaixo pq o C tava bugando a soma das pecas q permite capturar, linguagem lixo do caralho
    for (int i = 0; i < 20; i++) {
        posicoesPossiveis[i].qttPecasPermiteCaptuar = 0;
    }
    // peças brancas
    if (corDoJogador == 1) {
        if (tabuleiro[i][j].conteudo == 1) {  // logica abaixo para verificar movimentos de pc normal (nao dama)
            if (i <= 6 && j <= 5) {
                if (tabuleiro[i + 1][j + 1].conteudo == 2) {
                    if (tabuleiro[i + 2][j + 2].conteudo == 0) {
                        // jogada possivel
                        posicoesPossiveis[contador].coordenada[0] = i + 2;
                        posicoesPossiveis[contador].coordenada[1] = j + 2;

                        posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = i + 1;
                        posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = j + 1;
                        posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                        captura++;
                        contador++;
                        // logica abaixo para comer duas pc em sequencia se for possível
                        if (tabuleiro[i + 3][j + 3].conteudo == 2 && j <= 3) {
                            if (tabuleiro[i + 4][j + 4].conteudo == 0) {
                                posicoesPossiveis[contador].coordenada[0] = i + 4;
                                posicoesPossiveis[contador].coordenada[1] = j + 4;

                                posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = i + 1;
                                posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = j + 1;
                                posicoesPossiveis[contador].qttPecasPermiteCaptuar++;

                                posicoesPossiveis[contador].podeCapturar[1].coordenadaCaptura[0] = i + 3;
                                posicoesPossiveis[contador].podeCapturar[1].coordenadaCaptura[1] = j + 3;
                                posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                                contador++;
                            }
                        }
                    }
                }
            }
            if (i <= 6 && j >= 2) {
                if (tabuleiro[i + 1][j - 1].conteudo == 2) {
                    if (tabuleiro[i + 2][j - 2].conteudo == 0) {
                        // jogada possivel
                        posicoesPossiveis[contador].coordenada[0] = i + 2;
                        posicoesPossiveis[contador].coordenada[1] = j - 2;

                        posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = i + 1;
                        posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = j - 1;
                        posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                        captura++;
                        contador++;

                        // logica abaixo para comer duas pc em sequencia se for possível
                        if (tabuleiro[i + 3][j - 3].conteudo == 2 && j >= 4) {
                            if (tabuleiro[i + 4][j - 4].conteudo == 0) {
                                posicoesPossiveis[contador].coordenada[0] = i + 4;
                                posicoesPossiveis[contador].coordenada[1] = j - 4;

                                posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = i + 1;
                                posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = j - 1;
                                posicoesPossiveis[contador].qttPecasPermiteCaptuar++;

                                posicoesPossiveis[contador].podeCapturar[1].coordenadaCaptura[0] = i + 3;
                                posicoesPossiveis[contador].podeCapturar[1].coordenadaCaptura[1] = j - 3;
                                posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                                contador++;
                            }
                        }
                    }
                }
            }

            // movimentos simples - branca
            if (i <= 6 && j <= 6) {
                if (tabuleiro[i + 1][j + 1].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = i + 1;
                    posicoesPossiveis[contador].coordenada[1] = j + 1;

                    contador++;
                }
            }
            if (i <= 6 && j >= 1) {
                if (tabuleiro[i + 1][j - 1].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = i + 1;
                    posicoesPossiveis[contador].coordenada[1] = j - 1;
                    contador++;
                }
            }
        }
        if (tabuleiro[i][j].conteudo == 3) {
            movimentosDama(posicoesPossiveis, tabuleiro, coordenada, &captura, &contador, 2);
        }
    }
    // peças pretas
    if (corDoJogador == 2) {
        if (tabuleiro[i][j].conteudo == 2) {  // logica abaixo para verificar movimentos de pc normal (nao dama)
            if (i >= 2 && j >= 2) {
                if (tabuleiro[i - 1][j - 1].conteudo == 1) {
                    if (tabuleiro[i - 2][j - 2].conteudo == 0) {
                        // jogada possivel

                        posicoesPossiveis[contador].coordenada[0] = i - 2;
                        posicoesPossiveis[contador].coordenada[1] = j - 2;

                        posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = i - 1;
                        posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = j - 1;
                        posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                        captura++;
                        contador++;

                        // logica abaixo para comer duas pc em sequencia se for possível
                        if (tabuleiro[i - 3][j - 3].conteudo == 1 && j >= 4) {
                            if (tabuleiro[i - 4][j - 4].conteudo == 0) {
                                posicoesPossiveis[contador].coordenada[0] = i - 4;
                                posicoesPossiveis[contador].coordenada[1] = j - 4;

                                posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = i - 1;
                                posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = j - 1;
                                posicoesPossiveis[contador].qttPecasPermiteCaptuar++;

                                posicoesPossiveis[contador].podeCapturar[1].coordenadaCaptura[0] = i - 3;
                                posicoesPossiveis[contador].podeCapturar[1].coordenadaCaptura[1] = j - 3;
                                posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                                contador++;
                            }
                        }
                    }
                }
            }
            if (i >= 2 && j <= 5) {
                if (tabuleiro[i - 1][j + 1].conteudo == 1) {
                    if (tabuleiro[i - 2][j + 2].conteudo == 0) {
                        // jogada possivel
                        posicoesPossiveis[contador].coordenada[0] = i - 2;
                        posicoesPossiveis[contador].coordenada[1] = j + 2;

                        posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = i - 1;
                        posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = j + 1;
                        posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                        captura++;
                        contador++;
                        // logica abaixo para comer duas pc em sequencia se for possível (preta diagonal direita)
                        if (tabuleiro[i - 3][j + 3].conteudo == 1 && j <= 3) {
                            if (tabuleiro[i - 4][j + 4].conteudo == 0) {
                                posicoesPossiveis[contador].coordenada[0] = i - 4;
                                posicoesPossiveis[contador].coordenada[1] = j + 4;

                                posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = i - 1;
                                posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = j + 1;
                                posicoesPossiveis[contador].qttPecasPermiteCaptuar++;

                                posicoesPossiveis[contador].podeCapturar[1].coordenadaCaptura[0] = i - 3;
                                posicoesPossiveis[contador].podeCapturar[1].coordenadaCaptura[1] = j + 3;
                                posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                                contador++;
                            }
                        }
                    }
                }
            }

            // movimentos simples - preta
            if (i >= 1 && j < 7) {
                if (tabuleiro[i - 1][j + 1].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = i - 1;
                    posicoesPossiveis[contador].coordenada[1] = j + 1;
                    contador++;
                }
            }
            if (i >= 1 && j >= 1) {
                if (tabuleiro[i - 1][j - 1].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = i - 1;
                    posicoesPossiveis[contador].coordenada[1] = j - 1;
                    contador++;
                }
            }
        }
        if (tabuleiro[i][j].conteudo == 4) {
            movimentosDama(posicoesPossiveis, tabuleiro, coordenada, &captura, &contador, 1);
        }
    }

    *qttPecasComiveis = captura;
    *tamanhoArray = contador;

    return posicoesPossiveis;
}
void movimentosDama(Coordenada *posicoesPossiveis, Posicao tabuleiro[8][8], int coordenada[2], int *capturaPonteiro, int *contadorPonteiro, int corJogador) {
    int captura = 0;
    int contador = 0;  //<---- VERIFICAR SE DA PRA DEIXAR INICIAR EM 0 OU PRECISA ATRIBUIR O VALOR DO CONTADORPONTEIRO DE INIICIO!!!!!!!!!!
    int i = 1;
    if (tabuleiro[coordenada[0] + 1][coordenada[1] + 1].conteudo == corJogador) {
        if (tabuleiro[coordenada[0] + 2][coordenada[1] + 2].conteudo == 0) {
            posicoesPossiveis[contador].coordenada[0] = coordenada[0] + 2;
            posicoesPossiveis[contador].coordenada[1] = coordenada[1] + 2;

            posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = coordenada[0] + 1;
            posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = coordenada[1] + 1;
            posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
            captura++;
            contador++;
        }
    } else {
        while (tabuleiro[coordenada[0] + i][coordenada[1] + i].conteudo == 0 && coordenada[1] + i <= 7 && coordenada[0] + i <= 7) {  // logica diagonal direita baixo
            posicoesPossiveis[contador].coordenada[0] = coordenada[0] + i;
            posicoesPossiveis[contador].coordenada[1] = coordenada[1] + i;
            contador++;

            if (tabuleiro[coordenada[0] + i + 1][coordenada[1] + i + 1].conteudo == corJogador) {
                if (tabuleiro[coordenada[0] + i + 2][coordenada[1] + i + 2].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] + i + 2;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] + i + 2;

                    posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = coordenada[0] + i + 1;
                    posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = coordenada[1] + i + 1;
                    posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                    captura++;
                    contador++;
                }
            }
            i++;
        }
    }

    i = 1;
    if (tabuleiro[coordenada[0] + 1][coordenada[1] - 1].conteudo == corJogador) {
        if (tabuleiro[coordenada[0] + 2][coordenada[1] - 2].conteudo == 0) {
            posicoesPossiveis[contador].coordenada[0] = coordenada[0] + 2;
            posicoesPossiveis[contador].coordenada[1] = coordenada[1] - 2;

            posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = coordenada[0] + 1;
            posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = coordenada[1] - 1;
            posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
            captura++;
            contador++;
        }
    } else {
        while (tabuleiro[coordenada[0] + i][coordenada[1] - i].conteudo == 0 && coordenada[1] - i >= 0 && coordenada[0] + i <= 7) {  // logica diagonal esquerda baixo
            posicoesPossiveis[contador].coordenada[0] = coordenada[0] + i;
            posicoesPossiveis[contador].coordenada[1] = coordenada[1] - i;
            contador++;
            if (tabuleiro[coordenada[0] + i + 1][coordenada[1] - i - 1].conteudo == corJogador) {
                if (tabuleiro[coordenada[0] + i + 2][coordenada[1] - i - 2].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] + i + 2;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] - i - 2;

                    posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = coordenada[0] + i + 1;
                    posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = coordenada[1] - i - 1;

                    posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                    captura++;
                    contador++;
                }
            }
            i++;
        }
    }

    i = 1;
    if (tabuleiro[coordenada[0] - 1][coordenada[1] - 1].conteudo == corJogador) {
        if (tabuleiro[coordenada[0] - 2][coordenada[1] - 2].conteudo == 0) {
            posicoesPossiveis[contador].coordenada[0] = coordenada[0] - 2;
            posicoesPossiveis[contador].coordenada[1] = coordenada[1] - 2;

            posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = coordenada[0] - 1;
            posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = coordenada[1] - 1;
            posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
            captura++;
            contador++;
        }
    } else {
        while (tabuleiro[coordenada[0] - i][coordenada[1] - i].conteudo == 0 && coordenada[1] - i >= 0 && coordenada[0] - i >= 0) {  // logica diagonal esquerda cima
            posicoesPossiveis[contador].coordenada[0] = coordenada[0] - i;
            posicoesPossiveis[contador].coordenada[1] = coordenada[1] - i;
            contador++;
            if (tabuleiro[coordenada[0] - i - 1][coordenada[1] - i - 1].conteudo == corJogador) {
                if (tabuleiro[coordenada[0] - i - 2][coordenada[1] - i - 2].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] + i - 2;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] + i - 2;

                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[0] = coordenada[0] - i - 1;
                    posicoesPossiveis[contador].podeCapturar[captura].coordenadaCaptura[1] = coordenada[1] - i - 1;
                    posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                    captura++;
                    contador++;
                }
            }
            i++;
        }
    }
    i = 1;
    if (tabuleiro[coordenada[0] - 1][coordenada[1] + 1].conteudo == corJogador) {
        if (tabuleiro[coordenada[0] - 2][coordenada[1] + 2].conteudo == 0) {
            posicoesPossiveis[contador].coordenada[0] = coordenada[0] - 2;
            posicoesPossiveis[contador].coordenada[1] = coordenada[1] + 2;

            posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = coordenada[0] - 1;
            posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = coordenada[1] + 1;
            posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
            captura++;
            contador++;
        }
    } else {
        while (tabuleiro[coordenada[0] - i][coordenada[1] + i].conteudo == 0 && coordenada[1] + i <= 7 && coordenada[0] - i >= 0) {  // logica diagonal direita cima
            posicoesPossiveis[contador].coordenada[0] = coordenada[0] - i;
            posicoesPossiveis[contador].coordenada[1] = coordenada[1] + i;
            contador++;
            if (tabuleiro[coordenada[0] - i - 1][coordenada[1] + i + 1].conteudo == corJogador) {
                if (tabuleiro[coordenada[0] - i - 2][coordenada[1] + i + 2].conteudo == 0) {
                    posicoesPossiveis[contador].coordenada[0] = coordenada[0] + i - 2;
                    posicoesPossiveis[contador].coordenada[1] = coordenada[1] + i + 2;

                    posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[0] = coordenada[0] - i - 1;
                    posicoesPossiveis[contador].podeCapturar[0].coordenadaCaptura[1] = coordenada[1] + i + 1;
                    posicoesPossiveis[contador].qttPecasPermiteCaptuar++;
                    captura++;
                    contador++;
                }
            }
            i++;
        }
    }

    *capturaPonteiro = *capturaPonteiro + captura;
    *contadorPonteiro = *contadorPonteiro + contador;
}
void realizaMovimento(Coordenada *movimentosPossiveis, Posicao tabuleiro[8][8], int jogadorAtual, int tamanhoArray, int qttPecasComiveis, int coordenadaInicial[2], int coordenadaFinal[2], int *pontosBrancas, int *pontosPretas) {
    // retira a peça da posição anterior
    int linhaInicial = coordenadaInicial[0];
    int colunaInicial = coordenadaInicial[1];
    int linhaFinal = coordenadaFinal[0];
    int colunaFinal = coordenadaFinal[1];

    if (jogadorAtual % 2 == 1) {
        // PRETAS
        if (tabuleiro[linhaInicial][colunaInicial].conteudo == 4) {
            tabuleiro[linhaFinal][colunaFinal].conteudo = 4;
        } else {
            tabuleiro[linhaFinal][colunaFinal].conteudo = 2;
        }

        Coordenada coordenadaComida = retornaCoordernada(movimentosPossiveis, tamanhoArray, coordenadaFinal);
        if (coordenadaComida.qttPecasPermiteCaptuar > 0 && qttPecasComiveis) {
            for (int j = 0; j < coordenadaComida.qttPecasPermiteCaptuar; j++) {
                *pontosPretas += 1;
                tabuleiro[coordenadaComida.podeCapturar[j].coordenadaCaptura[0]][coordenadaComida.podeCapturar[j].coordenadaCaptura[1]].conteudo = 0;
            }
        }
        // preta chegou no final to tabuleiro (DAMA)
        if (linhaFinal == 0) {
            tabuleiro[linhaFinal][colunaFinal].conteudo = 4;  // DAMA PRETA
        }

    } else {
        // BRANCAS
        if (tabuleiro[linhaInicial][colunaInicial].conteudo == 3) {
            // se a peça não for dama branca, atribui uma peça branca normal
            tabuleiro[linhaFinal][colunaFinal].conteudo = 3;
        } else {
            tabuleiro[linhaFinal][colunaFinal].conteudo = 1;
        }
        Coordenada coordenadaComida = retornaCoordernada(movimentosPossiveis, tamanhoArray, coordenadaFinal);
        if (coordenadaComida.qttPecasPermiteCaptuar > 0 && qttPecasComiveis) {
            for (int j = 0; j < coordenadaComida.qttPecasPermiteCaptuar; j++) {
                *pontosBrancas += 1;
                tabuleiro[coordenadaComida.podeCapturar[j].coordenadaCaptura[0]][coordenadaComida.podeCapturar[j].coordenadaCaptura[1]].conteudo = 0;
            }
        }
        if (linhaFinal == 7) {
            tabuleiro[linhaFinal][colunaFinal].conteudo = 3;  // DAMA BRANCA
        }
    }
    tabuleiro[coordenadaInicial[0]][coordenadaInicial[1]].conteudo = 0;  // coordenada inicial fica sem pc depois do movimento.
}

int verificaPosicaoDigitada(Coordenada *movimentosPossiveis, int tamanhoArray, int coordenadaFinal[2]) {
    int linhaValida = 0;
    int colunaValida = 0;

    for (int i = 0; i < tamanhoArray; i++) {
        if (movimentosPossiveis[i].coordenada[0] == coordenadaFinal[0]) linhaValida = 1;
        if (movimentosPossiveis[i].coordenada[1] == coordenadaFinal[1]) colunaValida = 1;
    }
    // printf("\n\nflag linha: %d\nFlag coluna: %d\n\n",linhaValida,colunaValida);
    if (colunaValida == 0 || linhaValida == 0)
        return 0;
    else
        return 1;
}
Coordenada retornaCoordernada(Coordenada *movimentosPossiveis, int tamanhoArray, int coordenadaFinal[2]) {
    for (int i = 0; i <= tamanhoArray; i++) {
        if (movimentosPossiveis[i].coordenada[0] == coordenadaFinal[0] && movimentosPossiveis[i].coordenada[1] == coordenadaFinal[1]) {
            return movimentosPossiveis[i];
        }
    }
}
void imprimeTurnoJogador(int jogadorAtual) {
    if (jogadorAtual % 2 == 0) {
        printf("\n---------->BRANCAS JOGAM<----------\n\n");
    } else {
        printf("\n---------->PRETAS JOGAM<----------\n\n");
    }
}

void movePeca(Posicao tabuleiro[8][8], int jogadorAtual, int *pontosBrancas, int *pontosPretas) {
    int *coordenadaInicial;
    int *coordenadaFinal;
    int tamanhoArray;
    char capturadasLegivel[2];
    int qttPecasComiveis;
    int pecaCerta = 0;
    int damaCerta;
    Coordenada *movimentosPossiveis;
    imprimeTurnoJogador(jogadorAtual);
    /*
    if(jogadorAtual%2==0){ //logica necessaria pois estava deixando jogador mover pc de outro jogaro (kkkk)
        pecaCerta=2;
        damaCerta=4;
    }else {
        pecaCerta=1;
        damaCerta=3;
    }*/

    coordenadaInicial = digitaPosicao(1, 1);
    if (jogadorAtual % 2 == 0) {  // brancas jogando
        while (tabuleiro[coordenadaInicial[0]][coordenadaInicial[1]].conteudo != 1 && tabuleiro[coordenadaInicial[0]][coordenadaInicial[1]].conteudo != 3) {
            printf("---->Posicao invalida<----\n");
            coordenadaInicial = digitaPosicao(1, 1);
        }
        // brancas jogando
    } else {
        while (tabuleiro[coordenadaInicial[0]][coordenadaInicial[1]].conteudo != 2 && tabuleiro[coordenadaInicial[0]][coordenadaInicial[1]].conteudo != 4) {
            printf("---->Posicao invalida<----\n");
            coordenadaInicial = digitaPosicao(1, 1);
        }
    }

    movimentosPossiveis = calculaPosicoesPossiveis(coordenadaInicial, tabuleiro, jogadorAtual, &tamanhoArray, &qttPecasComiveis);
    while (tamanhoArray == 0) {
        printf("---->Digite uma posicao que possa realizar movimento!<----\n");
        coordenadaInicial = digitaPosicao(1, 1);
        while (tabuleiro[coordenadaInicial[0]][coordenadaInicial[1]].conteudo == 0) {
            printf("---->Posicao invalida<----\n");
            coordenadaInicial = digitaPosicao(1, 1);
        }
        movimentosPossiveis = calculaPosicoesPossiveis(coordenadaInicial, tabuleiro, jogadorAtual, &tamanhoArray, &qttPecasComiveis);
    }

    printf("\n");

    formataMovimentosPossiveis(tamanhoArray, movimentosPossiveis);
    /*
    if(qttPecasComiveis>0){
        for(int i=0;i<qttPecasComiveis;i++){
            for(int a=0;a<7;a++){
                if(movimentosPossiveis[i].podeCapturar[i].coordenadaCaptura[0] ==a){
                    capturadasLegivel[0]= a+65;
                }
                if(movimentosPossiveis[i].podeCapturar[i].coordenadaCaptura[1] ==a){
                    capturadasLegivel[1] = a + 1+'0';
                }
            }
            printf("Pecas comíveis: %c%c\n",capturadasLegivel[0],capturadasLegivel[1]);
        }
    }
    */

    if (qttPecasComiveis > 0) {
        printf("PODE COMER: ");
        for (int i = 0; i < tamanhoArray; i++) {
            if (movimentosPossiveis[i].qttPecasPermiteCaptuar > 0) {
                for (int j = 0; j < movimentosPossiveis[i].qttPecasPermiteCaptuar; j++) {
                    capturadasLegivel[0] = movimentosPossiveis[i].podeCapturar[j].coordenadaCaptura[0] + 65;
                    capturadasLegivel[1] = movimentosPossiveis[i].podeCapturar[j].coordenadaCaptura[1] + 49;
                    printf("%c%c ", capturadasLegivel[0], capturadasLegivel[1]);
                }
            }
        }
        printf("\n");
    }

    coordenadaFinal = digitaPosicao(2, 2);

    int verifica = verificaPosicaoDigitada(movimentosPossiveis, tamanhoArray, coordenadaFinal);
    while (!verifica) {
        printf("DIGITE UMA POSICAO VALIDA DENTRE AS OPCOES\n");
        coordenadaFinal = digitaPosicao(2, 2);
        verifica = verificaPosicaoDigitada(movimentosPossiveis, tamanhoArray, coordenadaFinal);
    }

    realizaMovimento(movimentosPossiveis, tabuleiro, jogadorAtual, tamanhoArray, qttPecasComiveis, coordenadaInicial, coordenadaFinal, pontosBrancas, pontosPretas);
}
// verifica o fim do jogo (olha se nao existe mais movimentos possiveis pra algum dos jogadores
int verificaFimDoJogo(int jogadorAtual, Posicao tabuleiro[8][8]) {
    int pcComidas;
    int movimentosBrancas = 0, movimentosPretas = 0;
    int coordernada[2];
    int arrayBranca = 0, arrayPreta = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            coordernada[0] = i;
            coordernada[1] = j;
            if (tabuleiro[i][j].conteudo == 1 || tabuleiro[i][j].conteudo == 3) {
                // abaixo foi necessario chamar 2 vezes o metodo pq dentro do metodo ele verifica a rodada, ai precisou chamar 2 vezes pra contabilizar as jogadas de cada cor
                calculaPosicoesPossiveis(coordernada, tabuleiro, 1, &arrayBranca, &pcComidas);
                movimentosBrancas += arrayBranca;
                calculaPosicoesPossiveis(coordernada, tabuleiro, 2, &arrayBranca, &pcComidas);
                movimentosBrancas += arrayBranca;
                arrayBranca = 0;
            }
            if (tabuleiro[i][j].conteudo == 2 || tabuleiro[i][j].conteudo == 4) {
                // abaixo foi necessario chamar 2 vezes o metodo pq dentro do metodo ele verifica a rodada, ai precisou chamar 2 vezes pra contabilizar as jogadas de cada cor
                calculaPosicoesPossiveis(coordernada, tabuleiro, 1, &arrayPreta, &pcComidas);
                movimentosPretas += arrayPreta;
                calculaPosicoesPossiveis(coordernada, tabuleiro, 2, &arrayPreta, &pcComidas);
                movimentosPretas += arrayPreta;
                arrayPreta = 0;
            }
        }
    }

    // printf("Movimentos pretas: %d\nMovimentos brancas: %d\n",movimentosPretas, movimentosBrancas);

    if (movimentosBrancas == 0) return 1;  // se nao existir nenhum movimento para as brancas retorna 1

    if (movimentosPretas == 0) return 2;  // se nao existir nenhum movimento para as pretas retorna 2

    return 0;  // se as duas tiverem movimento retorna false
}
void formataMovimentosPossiveis(int tamanhoArray, Coordenada *movimentosPossiveis) {
    char coordenadaLegivel[2];
    printf("Movimentos possiveis: ");
    for (int i = 0; i < tamanhoArray; i++) {
        for (int a = 0; a < 8; a++) {
            if (movimentosPossiveis[i].coordenada[0] == a) {
                coordenadaLegivel[0] = a + 65;
            }
            if (movimentosPossiveis[i].coordenada[1] == a) {
                coordenadaLegivel[1] = a + 1 + '0';
            }
        }
        printf("%c%c ", coordenadaLegivel[0], coordenadaLegivel[1]);
    }
    printf("\n");
}
void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}
