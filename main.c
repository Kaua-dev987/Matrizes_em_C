<<<<<<< HEAD
#include <stdio.h>
#include <math.h>

#define MAX 15

int main(void) {
    /* 1. Declaracao de todas as variaveis no inicio da funcao (regra C89/C90) */
    int escolha;
    int linhas, colunas;
    int i, j;
    int matriz[2][3];

   

    /* 2. Menu dentro da funcao main */
    printf("=============================================\n");
    printf("            Calculadora de Matrizes          \n");
    printf("=============================================\n");
    printf(" 1 - Adicao de matrizes;\n");
    printf(" 2 - Subtracao de matrizes;\n");
    printf(" 3 - Produto de um numero por uma matriz;\n");
    printf(" 4 - Produto de matrizes;\n");
    printf(" 5 - Calculo de Determinante;\n");
    printf(" 6 - Matriz inversa;\n");
    printf(" 7 - Matriz transposta;\n");
    printf("=============================================\n");
    printf("Escolha uma das operacoes (1 a 7): ");
    scanf("%d", &escolha); /* Sem o "\n" extra */
    printf("=============================================\n");
    printf("Opcao escolhida: %d\n\n", escolha);
    printf("Escolha a quantidade de linhas da sua matriz (1 a 15) : ")
    scanf("%d", &linhas , "\n");
    printf("Escolha a quantidade de colunas da sua matriz (1 a 15) : ")
    scanf("%d", &colunas , "\n");

    /* 3. Leitura da matriz dentro da main (ou de outra funcao) */
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("Digite o valor para posicao [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    return 0;
}
=======
#include <stdio.h>
#include <math.h>

#define MAX 15

int main(void) {
    /* 1. Declaracao de todas as variaveis no inicio da funcao (regra C89/C90) */
    int escolha;
    int linhas, colunas;
    int i, j;
    int matriz[2][3];

    linhas = 2;
    colunas = 3;

    /* 2. Menu dentro da funcao main */
    printf("=============================================\n");
    printf("            Calculadora de Matrizes          \n");
    printf("=============================================\n");
    printf(" 1 - Adicao de matrizes;\n");
    printf(" 2 - Subtracao de matrizes;\n");
    printf(" 3 - Produto de um numero por uma matriz;\n");
    printf(" 4 - Produto de matrizes;\n");
    printf(" 5 - Calculo de Determinante;\n");
    printf(" 6 - Matriz inversa;\n");
    printf(" 7 - Matriz transposta;\n");
    printf("=============================================\n");
    printf("Escolha uma das operacoes (1 a 7): ");
    scanf("%d", &escolha); /* Sem o "\n" extra */
    printf("=============================================\n");
    printf("Opcao escolhida: %d\n\n", escolha);

    /* 3. Leitura da matriz dentro da main (ou de outra funcao) */
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("Digite o valor para posicao [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    return 0;
}

>>>>>>> 32a8ae53ffea312aff30cfe70729e1fc37657d60
