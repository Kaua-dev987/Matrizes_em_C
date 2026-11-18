
#include <stdio.h>
#include <math.h>

int escolha;

int main()
{
    printf("=============================================\n");
    printf("            Calculadora de Matrizes              \n");
    printf("=============================================\n");
    printf(" 1 - Adição de matrizes; \n");
    printf(" 2 - Subtração de matrizes; \n");
    printf(" 3 - Produto de um número por uma matriz;\n");
    printf(" 4 - Produto de matrizes;\n");
    printf(" 5 - Cálculo de Determinante; \n");
    printf(" 6 - Matriz inversa;\n");
    printf(" 7 - Matriz transposta;\n ");
    printf("=============================================\n");
    printf("Escolha uma das operações (1 a 7) : ");
    scanf("%d", &escolha , "\n");
    printf("=============================================\n");
    printf("%d" , escolha);
}