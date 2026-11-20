#include <stdio.h>
#include <math.h>

#define MAX 15

/* ============================ (FUN��O SUBTRACAO DE MATRIZES) ============================ */

void subtracao_matriz(float m1[MAX][MAX], float m2[MAX][MAX],
                     int linhas, int colunas, int linhas2, int colunas2) {
    int i, j;
    float m3[MAX][MAX];

    if (linhas != linhas2 || colunas != colunas2) {
        printf("\nERRO: AS MATRIZES DEVEM TER O MESMO TAMANHO!!!\n");
        return;
    }

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            m3[i][j] = m1[i][j] - m2[i][j];
        }
    }

    printf("\n=============================================\n");
    printf("           RESULTADO DA SUBTRACAO            \n");
    printf("=============================================\n");

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("%.2f\t", m3[i][j]);
        }
        printf("\n");
    }

    return;
}

/* ============================ (FUN��O PRODUTO DE MATRIZES) ============================ */

void produto_matriz(float m1[MAX][MAX], float m2[MAX][MAX],
                    int linhas, int colunas, int linhas2, int colunas2) {
    int i, j, k;
    float m3[MAX][MAX];

    if (colunas != linhas2) {
        printf("\nERRO: O NUMERO DE COLUNAS DA PRIMEIRA MATRIZ\n");
        printf("DEVE SER IGUAL AO NUMERO DE LINHAS DA SEGUNDA!!!\n");
        return;
    }

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas2; j++) {
            m3[i][j] = 0;

            for (k = 0; k < colunas; k++) {
                m3[i][j] = m3[i][j] + (m1[i][k] * m2[k][j]);
            }
        }
    }

    printf("\n=============================================\n");
    printf("            RESULTADO DO PRODUTO             \n");
    printf("=============================================\n");

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas2; j++) {
            printf("%.2f\t", m3[i][j]);
        }
        printf("\n");
    }

    return;
}

/* ============================ (FUN��O TRANSPOSICAO DE MATRIZES) ============================ */

void transposta_matriz(float m1[MAX][MAX], int linhas, int colunas) {
    int i, j;
    float mt[MAX][MAX];

    for (j = 0; j < colunas; j++) {
        for (i = 0; i < linhas; i++) {
            mt[j][i] = m1[i][j];
        }
    }

    printf("\n=============================================\n");
    printf("              MATRIZ TRANSPOSTA              \n");
    printf("=============================================\n");

    for (j = 0; j < colunas; j++) {
        for (i = 0; i < linhas; i++) {
            printf("%.2f\t", mt[j][i]);
        }
        printf("\n");
    }

    return;
}

/* ============================ (FUN��O PRINCIPAL) ============================ */

int main(void) {

    /* ============================ (VARI�VEIS) ============================ */

    int escolha;
    int linhas, colunas;
    int linhas2, colunas2;
    int i, j;

    float matriz[MAX][MAX];
    float matriz2[MAX][MAX];

    /* ============================ (MENU) ============================ */

    printf("=============================================\n");
    printf("           CALCULADORA DE MATRIZES           \n");
    printf("=============================================\n");
    printf(" 1 - Adicao de matrizes                      \n");
    printf(" 2 - Subtracao de matrizes                   \n");
    printf(" 3 - Produto de um numero por uma matriz     \n");
    printf(" 4 - Produto de matrizes                     \n");
    printf(" 5 - Calculo de Determinante                 \n");
    printf(" 6 - Matriz inversa                          \n");
    printf(" 7 - Matriz transposta                       \n");
    printf("=============================================\n\n");

    printf("Escolha uma das operacoes (1 a 7): ");
    scanf("%d", &escolha);
    printf("\n");
    printf("=============================================\n\n");
    printf("Opcao escolhida: %d\n\n", escolha);
    printf("=============================================\n\n");

    /* ============================ (MATRIZ 1) ============================ */

    printf("Escolha a quantidade de linhas da sua matriz (1 a 15): ");
    scanf("%d", &linhas);

    printf("Escolha a quantidade de colunas da sua matriz (1 a 15): ");
    scanf("%d", &colunas);

    while (linhas < 1 || linhas > MAX || colunas < 1 || colunas > MAX) {

        printf("\n=============================================\n");
        printf("    OS VALORES DEVEM ESTAR ENTRE 1 E 15!    \n");
        printf("=============================================\n");

        printf("Escolha a quantidade de linhas da sua matriz (1 a 15): ");
        scanf("%d", &linhas);

        printf("Escolha a quantidade de colunas da sua matriz (1 a 15): ");
        scanf("%d", &colunas);
    }

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("Digite o valor para posicao [%d][%d]: ", i, j);
            scanf("%f", &matriz[i][j]);
        }
    }

    /* ============================ (MATRIZ 2) ============================ */

    if (escolha == 1 || escolha == 2 || escolha == 4) {

        printf("\nEscolha a quantidade de linhas da sua matriz (1 a 15): ");
        scanf("%d", &linhas2);

        printf("Escolha a quantidade de colunas da sua matriz (1 a 15): ");
        scanf("%d", &colunas2);

        while (linhas2 < 1 || linhas2 > MAX || colunas2 < 1 || colunas2 > MAX) {

            printf("\n=============================================\n");
            printf("    OS VALORES DEVEM ESTAR ENTRE 1 E 15!    \n");
            printf("=============================================\n");

            printf("Escolha a quantidade de linhas da sua matriz (1 a 15): ");
            scanf("%d", &linhas2);

            printf("Escolha a quantidade de colunas da sua matriz (1 a 15): ");
            scanf("%d", &colunas2);
        }

        for (i = 0; i < linhas2; i++) {
            for (j = 0; j < colunas2; j++) {
                printf("Digite o valor para posicao [%d][%d]: ", i, j);
                scanf("%f", &matriz2[i][j]);
            }
        }
    }

    /* ============================ (ESCOLHAS) ============================ */

    if (escolha == 2) {
        subtracao_matriz(matriz, matriz2, linhas, colunas, linhas2, colunas2);
    }

    if (escolha == 4) {
        produto_matriz(matriz, matriz2, linhas, colunas, linhas2, colunas2);
    }

    if (escolha == 7) {
        transposta_matriz(matriz, linhas, colunas);
    }

    return 0;
}
