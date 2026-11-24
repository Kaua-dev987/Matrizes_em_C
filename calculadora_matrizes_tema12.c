/*
- Trabalho Final - Programacao Computacional (2026.2)
- Tema 12: Calculadora de Matrizes em C ANSI (C89/C90)
- Equipe:
-   - Kaua Felipe Gomes Medeiros (604425)
-   - Levy Martins de Oliveira (608045)
-   - Nacelio Gomes Matias Filho (606443)
 */

#include <stdio.h>

#define MAX 15

/* Limpa o buffer do teclado ate a quebra de linha para evitar loops com entradas invalidas */
void limpar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

/* Le um numero inteiro dentro de um intervalo [min, max], barrando letras e valores fora do limite na hora */
int ler_inteiro_intervalo(const char *mensagem, int min, int max)
{
    int valor;
    char proximo_caractere;

    printf("%s", mensagem);
    while (1)
    {
        /* Verifica se leu um inteiro e se logo apos ele veio Enter, espaco, retorno ou tabulacao */
        if (scanf("%d%c", &valor, &proximo_caractere) == 2 &&
            (proximo_caractere == '\n' || proximo_caractere == ' ' ||
             proximo_caractere == '\r' || proximo_caractere == '\t'))
        {
            if (proximo_caractere != '\n')
            {
                limpar_buffer();
            }

            if (valor >= min && valor <= max)
            {
                return valor;
            }
        }
        else
        {
            limpar_buffer();
        }

        printf("Numero invalido! Digite um valor entre %d e %d: ", min, max);
    }
}

/* Le um numero real (double) validando a entrada contra letras e simbolos */
double ler_real(const char *mensagem)
{
    double valor;
    char proximo_caractere;

    printf("%s", mensagem);
    while (1)
    {
        if (scanf("%lf%c", &valor, &proximo_caractere) == 2 &&
            (proximo_caractere == '\n' || proximo_caractere == ' ' ||
             proximo_caractere == '\r' || proximo_caractere == '\t'))
        {
            if (proximo_caractere != '\n')
            {
                limpar_buffer();
            }
            return valor;
        }
        else
        {
            limpar_buffer();
        }

        printf("Numero invalido! Digite um numero valido: ");
    }
}

/* Evita a exibicao de zero negativo (-0.00) devido a precisao de ponto flutuante */
double corrigir_zero(double valor)
{
    if (valor > -1e-9 && valor < 1e-9)
    {
        return 0.0;
    }
    return valor;
}

/* Multiplica todos os elementos de uma matriz por um numero escalar */
void produto_escalar_matriz(double matriz[MAX][MAX], double multiplicador, int linhas, int colunas)
{
    int i, j;

    printf("\n==============================================================\n");
    printf("       RESULTADO DO PRODUTO ESCALAR (%.2f * A)               \n", multiplicador);
    printf("==============================================================\n");

    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            matriz[i][j] = corrigir_zero(matriz[i][j] * multiplicador);
            printf("%10.2f ", matriz[i][j]);
        }
        printf("\n");
    }
}

/* Calcula e exibe a matriz transposta (troca linhas por colunas) */
void transposta_matriz(double matriz[MAX][MAX], int linhas, int colunas)
{
    int i, j;
    double mt[MAX][MAX];

    for (j = 0; j < colunas; j++)
    {
        for (i = 0; i < linhas; i++)
        {
            mt[j][i] = corrigir_zero(matriz[i][j]);
        }
    }

    printf("\n==============================================================\n");
    printf("                       MATRIZ TRANSPOSTA                      \n");
    printf("==============================================================\n");

    for (j = 0; j < colunas; j++)
    {
        for (i = 0; i < linhas; i++)
        {
            printf("%10.2f ", mt[j][i]);
        }
        printf("\n");
    }
}

/* Realiza a multiplicacao entre duas matrizes (A * B) */
void produto_matriz(double matriz[MAX][MAX], double matriz2[MAX][MAX], int linhas, int colunas, int linhas_2, int colunas_2)
{
    int i, j, k;
    double m3[MAX][MAX];

    if (colunas != linhas_2)
    {
        printf("\nERRO: O NUMERO DE COLUNAS DA PRIMEIRA MATRIZ\n");
        printf("DEVE SER IGUAL AO NUMERO DE LINHAS DA SEGUNDA!!!\n");
        return;
    }

    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas_2; j++)
        {
            m3[i][j] = 0.0;

            for (k = 0; k < colunas; k++)
            {
                m3[i][j] = m3[i][j] + (matriz[i][k] * matriz2[k][j]);
            }
            m3[i][j] = corrigir_zero(m3[i][j]);
        }
    }

    printf("\n==============================================================\n");
    printf("                     RESULTADO DO PRODUTO                     \n");
    printf("==============================================================\n");

    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas_2; j++)
        {
            printf("%10.2f ", m3[i][j]);
        }
        printf("\n");
    }
}

/* Realiza a subtracao entre duas matrizes de mesma ordem (A - B) */
void subtracao_matriz(double matriz[MAX][MAX], double matriz2[MAX][MAX], int linhas, int colunas, int linhas_2, int colunas_2)
{
    int i, j;
    double m3[MAX][MAX];

    if (linhas != linhas_2 || colunas != colunas_2)
    {
        printf("\nERRO: AS MATRIZES DEVEM TER O MESMO TAMANHO!!!\n");
        return;
    }

    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            m3[i][j] = corrigir_zero(matriz[i][j] - matriz2[i][j]);
        }
    }

    printf("\n==============================================================\n");
    printf("                    RESULTADO DA SUBTRACAO                    \n");
    printf("==============================================================\n");

    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            printf("%10.2f ", m3[i][j]);
        }
        printf("\n");
    }
}

/* Calcula o determinante de matrizes quadradas de ordem 1x1 ate 15x15 via eliminacao de Gauss */
void determinante_matriz(int linhas, int colunas, double matriz[MAX][MAX])
{
    int i, j, passo, linha_pivo, ordem;
    int trocas = 0;
    double copia[MAX][MAX];
    double maior_valor, valor_absoluto, temporario, fator;
    double determinante = 1.0;

    if (linhas != colunas)
    {
        printf("\nMatrizes retangulares nao possuem determinantes.\n");
        return;
    }

    ordem = linhas;

    /* Cria uma copia da matriz original para nao alterar os dados recebidos */
    for (i = 0; i < ordem; i++)
    {
        for (j = 0; j < ordem; j++)
        {
            copia[i][j] = matriz[i][j];
        }
    }

    /* Escalonamento para matriz triangular superior */
    for (passo = 0; passo < ordem; passo++)
    {
        linha_pivo = passo;
        maior_valor = copia[passo][passo];
        if (maior_valor < 0.0)
        {
            maior_valor = -maior_valor;
        }

        /* Busca o maior pivo na coluna atual (pivoteamento parcial) */
        for (i = passo + 1; i < ordem; i++)
        {
            valor_absoluto = copia[i][passo];
            if (valor_absoluto < 0.0)
            {
                valor_absoluto = -valor_absoluto;
            }

            if (valor_absoluto > maior_valor)
            {
                maior_valor = valor_absoluto;
                linha_pivo = i;
            }
        }

        /* Se o maior pivo for zero, a matriz e singular e o determinante vale 0 */
        if (maior_valor < 1e-12)
        {
            determinante = 0.0;
            printf("\n==============================================================\n");
            printf("                        Determinante :                        \n");
            printf("%.2f\n", determinante);
            printf("==============================================================\n");
            return;
        }

        /* Troca as linhas e contabiliza a inversao de sinal do determinante */
        if (linha_pivo != passo)
        {
            for (j = 0; j < ordem; j++)
            {
                temporario = copia[passo][j];
                copia[passo][j] = copia[linha_pivo][j];
                copia[linha_pivo][j] = temporario;
            }
            trocas++;
        }

        /* Zera os elementos abaixo do pivo */
        for (i = passo + 1; i < ordem; i++)
        {
            fator = copia[i][passo] / copia[passo][passo];
            for (j = passo; j < ordem; j++)
            {
                copia[i][j] -= fator * copia[passo][j];
            }
        }
    }

    /* Multiplica os elementos da diagonal principal */
    for (i = 0; i < ordem; i++)
    {
        determinante *= copia[i][i];
    }

    /* Cada troca de linha inverte o sinal do determinante */
    if (trocas % 2 != 0)
    {
        determinante = -determinante;
    }

    determinante = corrigir_zero(determinante);

    printf("\n==============================================================\n");
    printf("                        Determinante :                        \n");
    printf("%.2f\n", determinante);
    printf("==============================================================\n");
}

/* Calcula a matriz inversa utilizando o metodo de eliminacao de Gauss-Jordan com pivoteamento parcial */
void calcular_matriz_inversa(double matriz[MAX][MAX], double resultado[MAX][MAX], int linhas, int colunas)
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

    if (linhas != colunas)
    {
        printf("\nErro: Para calcular a inversa, linhas e colunas devem ser iguais!\n");
        return;
    }

    ordem = linhas;

    /* Monta a matriz aumentada [A | I] */
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

    /* Escalonamento para transformar o lado esquerdo na matriz identidade */
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
            printf("\nEsta matriz NAO possui inversa!\n");
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

    printf("\n==============================================================\n");
    printf("                   MATRIZ INVERSA (%dx%d)                      \n", ordem, ordem);
    printf("==============================================================\n");

    for (indice_linha = 0; indice_linha < ordem; indice_linha++)
    {
        for (indice_coluna = 0; indice_coluna < ordem; indice_coluna++)
        {
            resultado[indice_linha][indice_coluna] = corrigir_zero(matriz_estendida[indice_linha][indice_coluna + ordem]);
            printf("%10.2f ", resultado[indice_linha][indice_coluna]);
        }
        printf("\n");
    }
}

/* Realiza a adicao entre duas matrizes de mesma ordem (A + B) */
void somar_matrizes(double matriz[MAX][MAX], double matrizB[MAX][MAX], double resultado[MAX][MAX], int linhas, int colunas, int linhas_2, int colunas_2)
{
    int indice_linha;
    int indice_coluna;

    if (linhas != linhas_2 || colunas != colunas_2)
    {
        printf("\nERRO: AS MATRIZES DEVEM TER O MESMO TAMANHO!!!\n");
        return;
    }

    printf("\n==============================================================\n");
    printf("                    RESULTADO DA ADICAO (A + B)               \n");
    printf("==============================================================\n");

    for (indice_linha = 0; indice_linha < linhas; indice_linha++)
    {
        for (indice_coluna = 0; indice_coluna < colunas; indice_coluna++)
        {
            resultado[indice_linha][indice_coluna] = corrigir_zero(matriz[indice_linha][indice_coluna] + matrizB[indice_linha][indice_coluna]);
            printf("%10.2f ", resultado[indice_linha][indice_coluna]);
        }
        printf("\n");
    }
}

/* Exibe o menu, valida a operacao escolhida e faz a leitura das dimensoes e elementos */
int menu(int primeira_execucao, int *escolha, int *linhas, int *colunas, int *linhas_2, int *colunas_2, double *multiplicador, double matriz[MAX][MAX], double matrizB[MAX][MAX])
{
    int i, j;

    printf("==============================================================\n");
    if (primeira_execucao)
    {
        printf("    [ o_o ] Ola seja bem vindo ! esta e a \n");
        printf("    ||___|/   Calculadora de Matrizes    \n");
        printf("      | |  \n");
    }
    else
    {
        printf("        Escolha novamente a sua opcao       \n");
    }
    printf("==============================================================\n");
    printf(" 1 - Adicao de matrizes;\n");
    printf(" 2 - Subtracao de matrizes;\n");
    printf(" 3 - Produto de um numero por uma matriz;\n");
    printf(" 4 - Produto de matrizes;\n");
    printf(" 5 - Calculo de Determinante;\n");
    printf(" 6 - Matriz inversa;\n");
    printf(" 7 - Matriz transposta;\n");
    printf("==============================================================\n");

    *escolha = ler_inteiro_intervalo("Escolha uma das operacoes (1 a 7): ", 1, 7);

    printf("==============================================================\n");

    /* Operacoes que utilizam apenas uma matriz (3, 5, 6 e 7) */
    if (*escolha == 3 || *escolha == 5 || *escolha == 6 || *escolha == 7)
    {
        switch (*escolha)
        {
        case 3:
            printf("Opcao escolhida: Produto de um numero por uma matriz\n");
            printf("==============================================================\n\n");
            *multiplicador = ler_real("Por qual numero que vc deseja multiplicar a sua matriz? : ");
            break;

        case 5:
            printf("Opcao escolhida: Calculo de Determinante\n");
            printf("==============================================================\n");
            break;

        case 6:
            printf("Opcao escolhida: Matriz inversa\n");
            printf("==============================================================\n");
            break;

        case 7:
            printf("Opcao escolhida: Matriz transposta\n");
            printf("==============================================================\n");
            break;
        }

        printf("\n--- Dimensoes da Matriz ---\n");
        *linhas = ler_inteiro_intervalo("Quantidade de linhas  (1 a 15) : ", 1, MAX);
        *colunas = ler_inteiro_intervalo("Quantidade de colunas (1 a 15) : ", 1, MAX);

        printf("\n==============================================================\n");
        printf("         Preenchimento da matriz            \n");
        printf("==============================================================\n");

        for (i = 0; i < *linhas; i++)
        {
            for (j = 0; j < *colunas; j++)
            {
                printf("Digite o valor para posicao (Matriz)[%d][%d]: ", i + 1, j + 1);
                matriz[i][j] = ler_real("");
            }
        }
    }
    /* Operacoes que utilizam duas matrizes (1, 2 e 4) */
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
        }
        printf("==============================================================\n");

        /* 1. Leitura das dimensoes e preenchimento da PRIMEIRA matriz */
        printf("\n--- Dimensoes da Primeira Matriz ---\n");
        *linhas = ler_inteiro_intervalo("Quantidade de linhas  (1 a 15) : ", 1, MAX);
        *colunas = ler_inteiro_intervalo("Quantidade de colunas (1 a 15) : ", 1, MAX);

        printf("\n==============================================================\n");
        printf("         Preenchimento da matriz 1          \n");
        printf("==============================================================\n");

        for (i = 0; i < *linhas; i++)
        {
            for (j = 0; j < *colunas; j++)
            {
                printf("Digite o valor para posicao (Primeira Matriz)[%d][%d]: ", i + 1, j + 1);
                matriz[i][j] = ler_real("");
            }
        }

        /* 2. Leitura das dimensoes e preenchimento da SEGUNDA matriz */
        printf("\n==============================================================\n");
        printf("\n--- Dimensoes da Segunda Matriz ---\n");
        *linhas_2 = ler_inteiro_intervalo("Quantidade de linhas  (1 a 15) : ", 1, MAX);
        *colunas_2 = ler_inteiro_intervalo("Quantidade de colunas (1 a 15) : ", 1, MAX);

        printf("\n==============================================================\n");
        printf("         Preenchimento da matriz 2         \n");
        printf("==============================================================\n");

        for (i = 0; i < *linhas_2; i++)
        {
            for (j = 0; j < *colunas_2; j++)
            {
                printf("Digite o valor para posicao (Segunda Matriz)[%d][%d]: ", i + 1, j + 1);
                matrizB[i][j] = ler_real("");
            }
        }
    }

    return 0;
}

int main(void)
{
    int escolha = 0;
    int linhas = 0, colunas = 0, linhas_2 = 0, colunas_2 = 0;
    double multiplicador = 0.0;
    double matriz[MAX][MAX], matrizB[MAX][MAX], resultado[MAX][MAX];
    int verificacao = 1;
    int primeira_execucao = 1;

    while (verificacao == 1)
    {
        menu(primeira_execucao, &escolha, &linhas, &colunas, &linhas_2, &colunas_2, &multiplicador, matriz, matrizB);
        primeira_execucao = 0;

        /* Executa a operacao escolhida pelo usuario */
        switch (escolha)
        {
        case 1:
            somar_matrizes(matriz, matrizB, resultado, linhas, colunas, linhas_2, colunas_2);
            break;

        case 2:
            subtracao_matriz(matriz, matrizB, linhas, colunas, linhas_2, colunas_2);
            break;

        case 3:
            produto_escalar_matriz(matriz, multiplicador, linhas, colunas);
            break;

        case 4:
            produto_matriz(matriz, matrizB, linhas, colunas, linhas_2, colunas_2);
            break;

        case 5:
            determinante_matriz(linhas, colunas, matriz);
            break;

        case 6:
            calcular_matriz_inversa(matriz, resultado, linhas, colunas);
            break;

        case 7:
            transposta_matriz(matriz, linhas, colunas);
            break;
        }

        printf("\n==============================================================\n");
        verificacao = ler_inteiro_intervalo("Deseja continuar com o programa? (0 - Nao / 1 - Sim) : ", 0, 1);
    }

    /* Exibe os creditos finais da equipe ao encerrar o programa */
    printf("\n==============================================================\n");
    printf("============ Finalizando programa ... \n");
    printf("Desenvolvido por : \n");
    printf("Kaua Felipe Gomes Medeiros (604425) \n");
    printf("Levy Martins de Oliveira (608045) \n");
    printf("Nacelio Gomes Matias Filho (606443) \n");
    printf("==============================================================\n");

    return 0;
}
