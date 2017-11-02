#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define TAM 3

int checagem(char mat[][TAM]);
void jogada(char mat[][TAM], char nome[], char simb);
void exibe(char mat[][TAM]);
void jogo2P(char mat[][TAM], char nome[], char nome2[]);
void jogoD(char mat[][TAM], char nome[]);
void jogoF(char mat[][TAM], char nome[]);
int jogadaC(char mat[][TAM], char simb);
void compAleatorio(char mat[][TAM]);
void pcJogada(char mat[][TAM], int *qtd);
void limpaJogo(char mat[][TAM]);

int main() {
    char mat[TAM][TAM] = { ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' '}, op, opJ, nome[100], nome2[100], dificuldade;
    int i, j;
    do {
        limpaJogo(mat);
        printf("\nJogo da velha \n1 - Jogar \n2 - sair \nDigite a sua opcao: ");
        op = getche(); fflush(stdin);
        switch (op) {
            case '1': do { // jogar
                    printf("\n1 - Jogador \n2 - Dois jogadores \nDigite uma opcao: ");
                    opJ = getche(); fflush(stdin);
                    switch (opJ) {
                        case '1': printf("\nInforme o nome do jogador: ");   //1 Jogador
                            gets(nome); gets(nome);
                            do {
                                printf("\nNivel do Jogo \n1 - Facil \n2 - Dificil \nDigite sua opcao: ");
                                dificuldade = getche(); fflush(stdin);
                                printf("\n");
                                switch (dificuldade) {
                                    case '1': system("cls");
                                        jogoF(mat, nome); //Facil
                                        break;
                                    case '2': system("cls");
                                        jogoD(mat, nome); //Dificil
                                        break;
                                    default: printf("\nopcao invalida \n");
                                        break;
                                }
                            } while (dificuldade < '1' || dificuldade > '2');
                            break;

                        case '2' : system("cls");
                            printf("\nInforme o nome do jogador 1: ");  //2 Jogadores
                            gets(nome); gets(nome); fflush(stdin);
                            printf("\nInforme o nome do jogador 2: ");
                            gets(nome2); gets(nome2); fflush(stdin);
                            printf("\nSortenado quem vai comecar ... ");
                            srand((unsigned)time(NULL));
                            if (rand() % 2 != 0) {
                                printf("%s comeca \n", nome);
                                printf("\nX - %s \nO - %s \n", nome, nome2);
                                jogo2P(mat, nome, nome2);
                            }
                            else {                                    //Jogador 2 começa
                                printf("%s comeca \n", nome2);
                                printf("\nX - %s \nO - %s \n", nome2, nome);
                                jogo2P(mat, nome2, nome);
                            }
                            break;
                        default: printf("\nopcao invalida \n");
                            break;
                    }
                } while (opJ < '1' || opJ > '2');
                break;
            case '2': printf("\n");
                break;
            default: printf("\nopcao invalida \n");
                break;
        }
    } while (op != '2');
    return 0;
}

void jogo2P(char mat[][TAM], char nome[], char nome2[]) {
    int i, j, ver = 0, qtd = 0;
    char simb1 = 'X', simb2 = 'O';
    do {
        exibe(mat);
        jogada(mat, nome, simb1);
        qtd = qtd + 1;
        ver = checagem(mat); // veri se alguem ganhou
        exibe(mat);
        if (ver != 0) {
            printf("%s Ganhou \n", nome);
            break;
        }
        if (qtd == 9) {
            break;
        }
        jogada(mat, nome2, simb2);
        qtd = qtd + 1;
        ver = checagem(mat);
        if (ver != 0) {
            printf("%s Ganhou \n", nome2);
            break;
        }
    } while (ver == 0 || qtd < 9);
    if(qtd == 9 && ver == 0) // entao tds os espacos estao preenchidos e ninguem ganhou
    {
        printf("Ninguem ganhou \n");
    }

}

void exibe(char mat[][TAM]) {
    int i, j;
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%c", mat[i][j]);
            if (j < 2) {
                printf(" | ");
            }
        }
        printf("\n");
    }
}

int checagem(char mat[][TAM]) {
    int i, j, verX = 0, verO = 0,verXC = 0, verOC = 0;
    for (i = 0; i < TAM; i++) {
        verX = 0;
        verO = 0;
        verXC = 0;
        verOC = 0;
        for (j = 0; j < TAM; j++) {
            if (mat[i][j] == 'X') {
                verX = verX + 1;
            }
            else if (mat[i][j] == 'O') {
                verO = verO + 1;
            }
            if (mat[j][i] == 'X') {
                verXC = verXC + 1;
            }
            else if (mat[j][i] == 'O') {
                verOC = verOC + 1;
            }
        }
        if (verX == 3 || verO == 3 || verXC == 3 || verOC == 3) {
            return 1;
        }
    }
    verX = 0;
    verO = 0;
    for (i = 0, j = 0; i < TAM; i++, j++) {
        if (mat[i][j] == 'X') {
            verX = verX + 1;
        }
        else if (mat[i][j] == 'O') {
            verO = verO + 1;
        }
    }
    if (verX == 3 || verO == 3) {
        return 1;
    }
    verX = 0;
    verO = 0;
    for (i = 2, j = 0; j < TAM; i--, j++) {
        if (mat[i][j] == 'X') {
            verX = verX + 1;
        }
        else if (mat[i][j] == 'O') {
            verO = verO + 1;
        }
    }
    if (verX == 3 || verO == 3) {
        return 1;
    }
    return 0;
}

void jogoF(char mat[][TAM], char nome[]) {
    int i, j, ver = 0, qtd = 0, vez;
    char simb = 'X';
    printf("\nX - %s \nO - Computador \n", nome);
    printf("\nSortenado quem vai comecar ... ");
    srand((unsigned)time(NULL));
    if (rand() % 2 <= 0.5) {
        printf("%s comeca \n", nome);
        vez = 1;
    }
    else {
        printf("O computador comeca \n");
        vez = 0;
    }
    do {
        if (vez == 1) {
            exibe(mat);
            jogada(mat, nome, simb);
            qtd = qtd + 1;
            ver = checagem(mat);
            if (ver != 0) {
                printf("%s Ganhou \n", nome);
                exibe(mat);
                break;
            }
            if (qtd == 9) {
                break;
            }
            vez = 0;
        }
        else {
            exibe(mat);
            compAleatorio(mat);
            qtd = qtd + 1;
            ver = checagem(mat);
            if (ver != 0) {
                printf("O Computador ganhou \n");
                exibe(mat);
                break;
            }
            vez = 1;
        }
    } while (ver == 0 || qtd < 9);
    if (qtd == 9 && ver == 0) {
        printf("Jogo empatado, nenhum vencedor \n");
    }
}

void jogoD(char mat[][TAM], char nome[]) {
    int i, j, ver = 0, qtd = 0, vez;
    char simb = 'X';
    printf("\nX - %s \nO - Computador \n", nome);
    printf("\nSortenado quem vai comecar ... ");
    srand((unsigned)time(NULL));
    if (rand() % 2 <= 0.5) {
        printf("%s comeca \n", nome);
        vez = 1;
    }
    else {
        printf("O computador comeca \n");
        vez = 0;
    }
    do {
        if (vez == 1) {
            exibe(mat);
            jogada(mat, nome, simb);
            qtd = qtd + 1;
            if (qtd == 9) {
                break;
            }
            ver = checagem(mat);
            if (ver != 0) {
                printf("%s Ganhou \n", nome);
                exibe(mat);
                break;
            }
            vez = 0;
        }
        else {
            exibe(mat);
            printf("\nComputador esta jogando \n");
            pcJogada(mat, &qtd);
            ver = checagem(mat);
            if (ver != 0) {
                printf("O Computador ganhou \n");
                exibe(mat);
                break;
            }
            vez = 1;
        }
    } while (ver == 0 || qtd < 9);
    if (qtd == 9 && ver == 0) {
        exibe(mat);
        printf("Jogo empatado, nenhum vencedor \n");
    }
}

int jogadaC(char mat[][TAM], char simb) {
    int i, j, ver = 0, verC = 0, verDP = 0, verDS = 0, aux;
    for (i = 0; i < TAM; i++) {
        ver = 0;
        verC = 0;
        for (j = 0; j < TAM; j++) {
            if (mat[i][j] == simb) {
                ver = ver + 1;
            }
            if (mat[j][i] == simb) {
                verC = verC + 1;
            }
            if (mat[i][j] == simb && i == j) {
                verDP = verDP + 1;
            }
            if (mat[i][j] == simb && ((i + j) == 2)) {
                verDS = verDS + 1;
            }
        }
        if (ver == 2 || verC == 2 || verDP == 2 || verDS == 2) {
            for (aux = 0; aux < TAM; aux++) {
                for (j = 0; j < TAM; j++) {
                    if (mat[i][j] == ' ' && ver == 2) {
                        mat[i][j] = 'O';
                        return 1;
                    }
                    if (mat[j][i] == ' ' && verC == 2) {
                        mat[j][i] = 'O';
                        return 1;
                    }
                    if (mat[aux][j] == ' ' && verDP == 2 && aux == j) {
                        mat[aux][j] = 'O';
                        return 1;
                    }
                    if (mat[aux][j] == ' ' && verDS == 2 && ((aux + j) == 2)) {
                        mat[aux][j] = 'O';
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void jogada(char mat[][TAM], char nome[], char simb) {
    int i, j;
    printf("%s sua vez de jogar. \n", nome);
    do {
        printf("Informe a linha: ");
        scanf("%d", &i);
        printf("Informe a coluna: ");
        scanf("%d", &j);
    } while (i > 3 || i < 1 || j > 3 || j < 1);
    while (mat[i - 1][j - 1] == 'X' || mat[i - 1][j - 1] == 'O') {
        printf("\nJogada nao efetuada \n");
        printf("%s Escolha outro numero. \n", nome);
        printf("Informe a linha: ");
        scanf("%d", &i);
        printf("Informe a coluna: ");
        scanf("%d", &j);
    }
    mat[i - 1][j - 1] = simb;
}

void compAleatorio(char mat[][TAM]) {
    int l, c;
    printf("Vez do computador jogar: \n");
    do {
        srand((unsigned)time(NULL));
        l = rand() % 3;
        srand((unsigned)time(NULL));
        c = rand() % 3;
    } while (mat[l][c] != ' ');
    mat[l][c] = 'O';
}

void pcJogada(char mat[][TAM], int *qtd) {
    char simb = 'X', simb2 = 'O';
    if (jogadaC(mat, simb2) == 1) {
        *qtd = *qtd + 1;
    }
    else if (jogadaC(mat, simb) == 1) {
        *qtd = *qtd + 1;
    }
    else {
        compAleatorio(mat);
        *qtd = *qtd + 1;
    }
}

void limpaJogo(char mat[][TAM]) {
    int i, j;
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            mat[i][j] = ' ';
        }
    }
}