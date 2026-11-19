#include <stdio.h>
#include <math.h>

#define MAX 15

void determinate_matriz(int *linhas, int *colunas, double matriz[MAX][MAX])
{
    double determinante;

    if (*linhas != *colunas)
    {
        printf("Matrizes retangulares não possuem determinantes.\n");
        return;
    }
    else if (*linhas == 2)
    {
        determinante =
            (matriz[0][0] * matriz[1][1]) -
            (matriz[0][1] * matriz[1][0]);
    }
    else if (*linhas == 3)
    {
        determinante =
            (matriz[0][0] * matriz[1][1] * matriz[2][2]) +
            (matriz[0][1] * matriz[1][2] * matriz[2][0]) +
            (matriz[0][2] * matriz[1][0] * matriz[2][1]) -
            (matriz[0][2] * matriz[1][1] * matriz[2][0]) -
            (matriz[0][0] * matriz[1][2] * matriz[2][1]) -
            (matriz[0][1] * matriz[1][0] * matriz[2][2]);
    }
    else if (*linhas == 4)
    {
        determinante =
            (matriz[0][0] * ((matriz[1][1] * matriz[2][2] * matriz[3][3]) +
                             (matriz[1][2] * matriz[2][3] * matriz[3][1]) +
                             (matriz[1][3] * matriz[2][1] * matriz[3][2]) -
                             (matriz[1][3] * matriz[2][2] * matriz[3][1]) -
                             (matriz[1][1] * matriz[2][3] * matriz[3][2]) -
                             (matriz[1][2] * matriz[2][1] * matriz[3][3]))) -
            (matriz[0][1] * ((matriz[1][0] * matriz[2][2] * matriz[3][3]) +
                             (matriz[1][2] * matriz[2][3] * matriz[3][0]) +
                             (matriz[1][3] * matriz[2][0] * matriz[3][2]) -
                             (matriz[1][3] * matriz[2][2] * matriz[3][0]) -
                             (matriz[1][0] * matriz[2][3] * matriz[3][2]) -
                             (matriz[1][2] * matriz[2][0] * matriz[3][3]))) +
            (matriz[0][2] * ((matriz[1][0] * matriz[2][1] * matriz[3][3]) +
                             (matriz[1][1] * matriz[2][3] * matriz[3][0]) +
                             (matriz[1][3] * matriz[2][0] * matriz[3][1]) -
                             (matriz[1][3] * matriz[2][1] * matriz[3][0]) -
                             (matriz[1][0] * matriz[2][3] * matriz[3][1]) -
                             (matriz[1][1] * matriz[2][0] * matriz[3][3]))) -
            (matriz[0][3] * ((matriz[1][0] * matriz[2][1] * matriz[3][2]) +
                             (matriz[1][1] * matriz[2][2] * matriz[3][0]) +
                             (matriz[1][2] * matriz[2][0] * matriz[3][1]) -
                             (matriz[1][2] * matriz[2][1] * matriz[3][0]) -
                             (matriz[1][0] * matriz[2][2] * matriz[3][1]) -
                             (matriz[1][1] * matriz[2][0] * matriz[3][2])));
    }
    else
    {
        printf("Determinante implementado apenas para matrizes 2x2, 3x3 e 4x4.\n");
        return;
    }

    printf("=============================================\n");
    printf("               Determinante :                \n");
    printf("%.2lf\n", determinante);
    printf("=============================================\n");
}

void calcular_matriz_inversa(double matriz[MAX][MAX], double resultado[MAX][MAX], int *linhas, int *colunas)
{
    int indice_linha;
    int indice_coluna;
    int passo;
    int linha_pivo;
    int ordem;
    double matriz_estendida[MAX][2 * MAX];
    double maior_valor;
    double valor_absoluto;
    double pivo;
    double fator;
    double temporario;

    if (*linhas != *colunas)
    {
        printf("\nErro: Para calcular a inversa, linhas e colunas devem ser iguais!\n");
        return;
    }

    ordem = *linhas;

    for (indice_linha = 0; indice_linha < ordem; indice_linha++)
    {
        for (indice_coluna = 0; indice_coluna < ordem; indice_coluna++)
        {
            matriz_estendida[indice_linha][indice_coluna] = matriz[indice_linha][indice_coluna];

            if (indice_linha == indice_coluna)
            {
                matriz_estendida[indice_linha][indice_coluna + ordem] = 1.0;
            }
            else
            {
                matriz_estendida[indice_linha][indice_coluna + ordem] = 0.0;
            }
        }
    }

    for (passo = 0; passo < ordem; passo++)
    {
        linha_pivo = passo;
        maior_valor = matriz_estendida[passo][passo];
        if (maior_valor < 0.0)
        {
            maior_valor = -maior_valor;
        }

        for (indice_linha = passo + 1; indice_linha < ordem; indice_linha++)
        {
            valor_absoluto = matriz_estendida[indice_linha][passo];
            if (valor_absoluto < 0.0)
            {
                valor_absoluto = -valor_absoluto;
            }
            if (valor_absoluto > maior_valor)
            {
                maior_valor = valor_absoluto;
                linha_pivo = indice_linha;
            }
        }

        if (maior_valor < 1e-12)
        {
            printf("Esta matriz NAO possui inversa!\n");
            return;
        }

        if (linha_pivo != passo)
        {
            for (indice_coluna = 0; indice_coluna < 2 * ordem; indice_coluna++)
            {
                temporario = matriz_estendida[passo][indice_coluna];
                matriz_estendida[passo][indice_coluna] = matriz_estendida[linha_pivo][indice_coluna];
                matriz_estendida[linha_pivo][indice_coluna] = temporario;
            }
        }

        pivo = matriz_estendida[passo][passo];
        for (indice_coluna = 0; indice_coluna < 2 * ordem; indice_coluna++)
        {
            matriz_estendida[passo][indice_coluna] = matriz_estendida[passo][indice_coluna] / pivo;
        }

        for (indice_linha = 0; indice_linha < ordem; indice_linha++)
        {
            if (indice_linha != passo)
            {
                fator = matriz_estendida[indice_linha][passo];
                for (indice_coluna = 0; indice_coluna < 2 * ordem; indice_coluna++)
                {
                    matriz_estendida[indice_linha][indice_coluna] -= fator * matriz_estendida[passo][indice_coluna];
                }
            }
        }
    }

    printf("\nMatriz Inversa (%dx%d):\n", ordem, ordem);
    for (indice_linha = 0; indice_linha < ordem; indice_linha++)
    {
        for (indice_coluna = 0; indice_coluna < ordem; indice_coluna++)
        {
            resultado[indice_linha][indice_coluna] = matriz_estendida[indice_linha][indice_coluna + ordem];

            if (resultado[indice_linha][indice_coluna] > -1e-9 &&
                resultado[indice_linha][indice_coluna] < 1e-9)
            {
                resultado[indice_linha][indice_coluna] = 0.0;
            }

            printf("%10.2f ", resultado[indice_linha][indice_coluna]);
        }
        printf("\n");
    }
}

void somar_matrizes(double matriz[MAX][MAX], double matrizB[MAX][MAX], double resultado[MAX][MAX], int *linhas, int *colunas)
{
    int indice_linha;
    int indice_coluna;

    printf("\nResultado da Adicao (A + B):\n");
    for (indice_linha = 0; indice_linha < *linhas; indice_linha++)
    {
        for (indice_coluna = 0; indice_coluna < *colunas; indice_coluna++)
        {
            resultado[indice_linha][indice_coluna] = matriz[indice_linha][indice_coluna] + matrizB[indice_linha][indice_coluna];

            if (resultado[indice_linha][indice_coluna] > -1e-9 &&
                resultado[indice_linha][indice_coluna] < 1e-9)
            {
                resultado[indice_linha][indice_coluna] = 0.0;
            }

            printf("%10.2f ", resultado[indice_linha][indice_coluna]);
        }
        printf("\n");
    }
}

int menu(int *escolha, int *linhas, int *colunas, int *linhas_2, int *colunas_2, double *multiplicador, double matriz[MAX][MAX], double matrizB[MAX][MAX])
{
    int i, j;

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

    if (scanf("%d", escolha) != 1)
    {
        printf("Entrada invalida!\n");
        return 1;
    }

    printf("=============================================\n");

    if (*escolha == 3 || *escolha == 5 || *escolha == 6 || *escolha == 7)
    {
        switch (*escolha)
        {
        case 3:
            printf("Opcao escolhida: Produto de um numero por uma matriz\n");
            printf("Por qual numero que vc deseja multiplicar a sua matriz? : ");
            if (scanf("%lf", multiplicador) != 1)
            {
                printf("Entrada invalida!\n");
                return 1;
            }
            break;
        case 5:
            printf("Opcao escolhida: Calculo de Determinante\n");
            break;
        case 6:
            printf("Opcao escolhida: Matriz inversa\n");
            break;
        case 7:
            printf("Opcao escolhida: Matriz transposta\n");
            break;
        }

        printf("Escolha a quantidade de linhas da sua matriz (1 a 15) : ");
        if (scanf("%d", linhas) != 1)
        {
            printf("Entrada invalida!\n");
            return 1;
        }
        printf("Escolha a quantidade de colunas da sua matriz (1 a 15) : ");
        if (scanf("%d", colunas) != 1)
        {
            printf("Entrada invalida!\n");
            return 1;
        }

        while (*linhas > MAX || *colunas > MAX || *linhas <= 0 || *colunas <= 0)
        {
            printf("=============================================\n");
            printf("! Os valores devem estar dentro do limite ! \n");
            printf("=============================================\n");

            printf("Escolha a quantidade de linhas da sua matriz (1 a 15) : ");
            if (scanf("%d", linhas) != 1)
                return 1;

            printf("Escolha a quantidade de colunas da sua matriz (1 a 15) : ");
            if (scanf("%d", colunas) != 1)
                return 1;
        }

        for (i = 0; i < *linhas; i++)
        {
            for (j = 0; j < *colunas; j++)
            {
                printf("Digite o valor para posicao (1 matriz)[%d][%d]: ", i + 1, j + 1);
                if (scanf("%lf", &matriz[i][j]) != 1)
                {
                    printf("Entrada invalida!\n");
                    return 1;
                }
            }
        }
    }
    else
    {
        switch (*escolha)
        {
        case 1:
            printf("Opcao escolhida: Adicao de matrizes\n");
            break;
        case 2:
            printf("Opcao escolhida: Subtracao de matrizes\n");
            break;
        case 4:
            printf("Opcao escolhida: Produto de matrizes\n");
            break;
        default:
            printf("Opcao invalida!\n");
            return 1;
        }

        printf("Escolha a quantidade de linhas da sua matriz 1 (1 a 15) : ");
        if (scanf("%d", linhas) != 1)
            return 1;

        printf("Escolha a quantidade de linhas da sua matriz 2 (1 a 15) : ");
        if (scanf("%d", linhas_2) != 1)
            return 1;

        printf("Escolha a quantidade de colunas da sua matriz 1 (1 a 15) : ");
        if (scanf("%d", colunas) != 1)
            return 1;

        printf("Escolha a quantidade de colunas da sua matriz 2 (1 a 15) : ");
        if (scanf("%d", colunas_2) != 1)
            return 1;

        while (*linhas > MAX || *colunas > MAX || *linhas_2 > MAX || *colunas_2 > MAX ||
               *linhas <= 0 || *colunas <= 0 || *linhas_2 <= 0 || *colunas_2 <= 0)
        {
            printf("=============================================\n");
            printf("! Os valores devem estar dentro do limite ! \n");
            printf("=============================================\n");

            printf("Escolha a quantidade de linhas da sua matriz 1 (1 a 15) : ");
            if (scanf("%d", linhas) != 1)
                return 1;

            printf("Escolha a quantidade de linhas da sua matriz 2 (1 a 15) : ");
            if (scanf("%d", linhas_2) != 1)
                return 1;

            printf("Escolha a quantidade de colunas da sua matriz 1 (1 a 15) : ");
            if (scanf("%d", colunas) != 1)
                return 1;

            printf("Escolha a quantidade de colunas da sua matriz 2 (1 a 15) : ");
            if (scanf("%d", colunas_2) != 1)
                return 1;
        }

        printf("=============================================\n");
        printf("         Preenchimento da 1 matriz          \n");
        printf("=============================================\n");

        for (i = 0; i < *linhas; i++)
        {
            for (j = 0; j < *colunas; j++)
            {
                printf("Digite o valor para posicao (1 matriz)[%d][%d]: ", i + 1, j + 1);
                if (scanf("%lf", &matriz[i][j]) != 1)
                    return 1;
            }
        }

        printf("=============================================\n");
        printf("         Preenchimento da 2 matriz          \n");
        printf("=============================================\n");

        for (i = 0; i < *linhas_2; i++)
        {
            for (j = 0; j < *colunas_2; j++)
            {
                printf("Digite o valor para posicao (2 matriz)[%d][%d]: ", i + 1, j + 1);
                if (scanf("%lf", &matrizB[i][j]) != 1)
                    return 1;
            }
        }
    }

    return 0;
}
int menu_reload(int *escolha, int *linhas, int *colunas, int *linhas_2, int *colunas_2, double *multiplicador, double matriz[MAX][MAX], double matrizB[MAX][MAX])
{
    int i, j;

    printf("=============================================\n");
    printf("        Escolha novamente a sua opção        \n");
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

    if (scanf("%d", escolha) != 1)
    {
        printf("Entrada invalida!\n");
        return 1;
    }

    printf("=============================================\n");

    if (*escolha == 3 || *escolha == 5 || *escolha == 6 || *escolha == 7)
    {
        switch (*escolha)
        {
        case 3:
            printf("Opcao escolhida: Produto de um numero por uma matriz\n");
            printf("Por qual numero que vc deseja multiplicar a sua matriz? : ");
            if (scanf("%lf", multiplicador) != 1)
            {
                printf("Entrada invalida!\n");
                return 1;
            }
            break;
        case 5:
            printf("Opcao escolhida: Calculo de Determinante\n");
            break;
        case 6:
            printf("Opcao escolhida: Matriz inversa\n");
            break;
        case 7:
            printf("Opcao escolhida: Matriz transposta\n");
            break;
        }

        printf("Escolha a quantidade de linhas da sua matriz (1 a 15) : ");
        if (scanf("%d", linhas) != 1)
        {
            printf("Entrada invalida!\n");
            return 1;
        }
        printf("Escolha a quantidade de colunas da sua matriz (1 a 15) : ");
        if (scanf("%d", colunas) != 1)
        {
            printf("Entrada invalida!\n");
            return 1;
        }

        while (*linhas > MAX || *colunas > MAX || *linhas <= 0 || *colunas <= 0)
        {
            printf("=============================================\n");
            printf("! Os valores devem estar dentro do limite ! \n");
            printf("=============================================\n");

            printf("Escolha a quantidade de linhas da sua matriz (1 a 15) : ");
            if (scanf("%d", linhas) != 1)
                return 1;

            printf("Escolha a quantidade de colunas da sua matriz (1 a 15) : ");
            if (scanf("%d", colunas) != 1)
                return 1;
        }

        for (i = 0; i < *linhas; i++)
        {
            for (j = 0; j < *colunas; j++)
            {
                printf("Digite o valor para posicao (1 matriz)[%d][%d]: ", i + 1, j + 1);
                if (scanf("%lf", &matriz[i][j]) != 1)
                {
                    printf("Entrada invalida!\n");
                    return 1;
                }
            }
        }
    }
    else
    {
        switch (*escolha)
        {
        case 1:
            printf("Opcao escolhida: Adicao de matrizes\n");
            break;
        case 2:
            printf("Opcao escolhida: Subtracao de matrizes\n");
            break;
        case 4:
            printf("Opcao escolhida: Produto de matrizes\n");
            break;
        default:
            printf("Opcao invalida!\n");
            return 1;
        }

        printf("Escolha a quantidade de linhas da sua matriz 1 (1 a 15) : ");
        if (scanf("%d", linhas) != 1)
            return 1;

        printf("Escolha a quantidade de linhas da sua matriz 2 (1 a 15) : ");
        if (scanf("%d", linhas_2) != 1)
            return 1;

        printf("Escolha a quantidade de colunas da sua matriz 1 (1 a 15) : ");
        if (scanf("%d", colunas) != 1)
            return 1;

        printf("Escolha a quantidade de colunas da sua matriz 2 (1 a 15) : ");
        if (scanf("%d", colunas_2) != 1)
            return 1;

        while (*linhas > MAX || *colunas > MAX || *linhas_2 > MAX || *colunas_2 > MAX ||
               *linhas <= 0 || *colunas <= 0 || *linhas_2 <= 0 || *colunas_2 <= 0)
        {
            printf("=============================================\n");
            printf("! Os valores devem estar dentro do limite ! \n");
            printf("=============================================\n");

            printf("Escolha a quantidade de linhas da sua matriz 1 (1 a 15) : ");
            if (scanf("%d", linhas) != 1)
                return 1;

            printf("Escolha a quantidade de linhas da sua matriz 2 (1 a 15) : ");
            if (scanf("%d", linhas_2) != 1)
                return 1;

            printf("Escolha a quantidade de colunas da sua matriz 1 (1 a 15) : ");
            if (scanf("%d", colunas) != 1)
                return 1;

            printf("Escolha a quantidade de colunas da sua matriz 2 (1 a 15) : ");
            if (scanf("%d", colunas_2) != 1)
                return 1;
        }

        printf("=============================================\n");
        printf("         Preenchimento da 1 matriz          \n");
        printf("=============================================\n");

        for (i = 0; i < *linhas; i++)
        {
            for (j = 0; j < *colunas; j++)
            {
                printf("Digite o valor para posicao (1 matriz)[%d][%d]: ", i + 1, j + 1);
                if (scanf("%lf", &matriz[i][j]) != 1)
                    return 1;
            }
        }

        printf("=============================================\n");
        printf("         Preenchimento da 2 matriz          \n");
        printf("=============================================\n");

        for (i = 0; i < *linhas_2; i++)
        {
            for (j = 0; j < *colunas_2; j++)
            {
                printf("Digite o valor para posicao (2 matriz)[%d][%d]: ", i + 1, j + 1);
                if (scanf("%lf", &matrizB[i][j]) != 1)
                    return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    int escolha = 0;
    int linhas = 0, colunas = 0, linhas_2 = 0, colunas_2 = 0;
    double multiplicador = 0;
    double matriz[MAX][MAX], matrizB[MAX][MAX], resultado[MAX][MAX];
    int verificacao = 0;

    if (menu(&escolha, &linhas, &colunas, &linhas_2, &colunas_2, &multiplicador, matriz, matrizB) != 0)
    {
        return 1;
    }

    while (verificacao == 0)
    {
        /* Nesse switch, implementaremos as operacoes com as matrizes , ele funciona chamando cada função correta */
        switch (escolha)
        {
        case 1:
            if (linhas != linhas_2 || colunas != colunas_2)
            {
                printf("Erro: Para somar, as matrizes precisam ter a mesma quantidade de linhas e colunas!\n");
                break;
            }
            somar_matrizes(matriz, matrizB, resultado, &linhas, &colunas);
            printf("============= Deseja continuar com o programa? (1 - Nao / 0 - Sim) : ");
            scanf("%d", &verificacao);
            if (verificacao == 1)
            {
                printf("============ Finalizando programa ... \n");
                return 0;
            }
            break;
        case 2:
            printf("Subtracao de matrizes ainda nao implementada.\n");
            printf("============= Deseja continuar com o programa? (1 - Nao / 0 - Sim) : ");
            scanf("%d", &verificacao);
            if (verificacao == 1)
            {
                printf("============ Finalizando programa ... \n");
                return 0;
            }
            break;
        case 3:
            printf("Produto por escalar ainda nao implementado.\n");
            printf("============= Deseja continuar com o programa? (1 - Nao / 0 - Sim) : ");
            scanf("%d", &verificacao);
            if (verificacao == 1)
            {
                printf("============ Finalizando programa ... \n");
                return 0;
            }
            break;
        case 4:
            printf("Produto de matrizes ainda nao implementado.\n");
            printf("============= Deseja continuar com o programa? (1 - Nao / 0 - Sim) : ");
            scanf("%d", &verificacao);
            if (verificacao == 1)
            {
                printf("============ Finalizando programa ... \n");
                return 0;
            }
            break;
        case 5:
            determinate_matriz(&linhas, &colunas, matriz);
            printf("============= Deseja continuar com o programa? (1 - Nao / 0 - Sim) : ");
            scanf("%d", &verificacao);
            if (verificacao == 1)
            {
                printf("============ Finalizando programa ... \n");
                return 0;
            }
            break;
        case 6:
            calcular_matriz_inversa(matriz, resultado, &linhas, &colunas);
            printf("============= Deseja continuar com o programa? (1 - Nao / 0 - Sim) : ");
            scanf("%d", &verificacao);
            if (verificacao == 1)
            {
                printf("============ Finalizando programa ... \n");
                return 0;
            }
            break;
        case 7:
            printf("Matriz transposta ainda nao implementada.\n");
            printf("============= Deseja continuar com o programa? (1 - Nao / 0 - Sim) : ");
            scanf("%d", &verificacao);
            if (verificacao == 1)
            {
                printf("============ Finalizando programa ... \n");
                return 0;
            }
            break;
        }
        if (verificacao == 0)
        {
            if (menu_reload(&escolha, &linhas, &colunas, &linhas_2, &colunas_2, &multiplicador, matriz, matrizB) != 0)
            {
                return 1;
            }
        }
        else
        {
            printf("Programa encerrado.\n");
            return 0;
        }
    }
    return 0;
}
