#include <stdio.h>
#define MAX 15

/* PROTOTIPOS DAS FUNCOES GLOBAIS */
int ler_inteiro_intervalo(int minimo, int maximo);
double ler_double_seguro(void);
void ler_matriz(double matriz[MAX][MAX], 
                int quantidade_linhas, 
                int quantidade_colunas, 
                const char *nome_matriz);
void somar_matrizes(double matriz_a[MAX][MAX], 
                    double matriz_b[MAX][MAX], 
                    double matriz_resultado[MAX][MAX], 
                    int quantidade_linhas, 
                    int quantidade_colunas);
void calcular_matriz_inversa(double matriz_a[MAX][MAX], 
                             double matriz_resultado[MAX][MAX], 
                             int quantidade_linhas, 
                             int quantidade_colunas);


/* FUNCAO PRINCIPAL (main) */
int main(void) {
    /* Declaracao de todas as variaveis no inicio da funcao (regra C89/C90) */
    int opcao_escolhida;
    int continuar_programa;
    int quantidade_linhas;
    int quantidade_colunas;

    /* Usa 'double' para aceitar numeros decimais na matriz inversa */
    double matriz_a[MAX][MAX];
    double matriz_b[MAX][MAX];
    double matriz_resultado[MAX][MAX];

    continuar_programa = 1;

    /* Laco principal: repete o programa ate o usuario digitar 0 para sair */
    while (continuar_programa == 1) {
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
        opcao_escolhida = ler_inteiro_intervalo(1, 7);

        printf("=============================================\n");
        printf("Opcao escolhida: %d\n\n", opcao_escolhida);

        /* Direciona para a operacao escolhida */
        if (opcao_escolhida == 1) {
            printf("================= ADICAO DE MATRIZES =================\n");
            printf("Escolha a quantidade de linhas das matrizes (1 a %d): ", MAX);
            quantidade_linhas = ler_inteiro_intervalo(1, MAX);

            printf("Escolha a quantidade de colunas das matrizes (1 a %d): ", MAX);
            quantidade_colunas = ler_inteiro_intervalo(1, MAX);

            ler_matriz(matriz_a, quantidade_linhas, quantidade_colunas, "A");
            ler_matriz(matriz_b, quantidade_linhas, quantidade_colunas, "B");

            somar_matrizes(matriz_a, matriz_b, matriz_resultado, quantidade_linhas, quantidade_colunas);
        }

        else if (opcao_escolhida == 6) {
            printf("================= MATRIZ INVERSA =================\n");
            printf("Informe a quantidade de linhas da matriz (1 a %d): ", MAX);
            quantidade_linhas = ler_inteiro_intervalo(1, MAX);

            printf("Informe a quantidade de colunas da matriz (1 a %d): ", MAX);
            quantidade_colunas = ler_inteiro_intervalo(1, MAX);

            /* Verifica se as quantidades digitadas formam uma matriz quadrada */
            if (quantidade_linhas != quantidade_colunas) {
                printf("\nErro: Para calcular a inversa, a matriz deve ser quadrada!\n");
            } else {
                ler_matriz(matriz_a, quantidade_linhas, quantidade_colunas, "A");
                calcular_matriz_inversa(matriz_a, matriz_resultado, quantidade_linhas, quantidade_colunas);
            }
        }

        else {
            printf("\nOpcao ainda nao implementada!\n");
        }

        /* Repete a pergunta de continuar enquanto nao digitar 0 ou 1 */
        printf("\nDeseja realizar outro calculo? (1 - Sim / 0 - Sair): ");
        continuar_programa = ler_inteiro_intervalo(0, 1);
        printf("\n");
    }

    return 0;
}

/* ============================================================================
- IMPLEMENTACAO DAS FUNCOES GLOBAIS
- ============================================================================ */

/* Funcao auxiliar: le inteiro no intervalo [minimo, maximo] aceitando espacos e rejeitando letras */
int ler_inteiro_intervalo(int minimo, int maximo) {
    int valor;
    char proximo_char;
    int leitura_valida;
    int tem_lixo;

    leitura_valida = 0;

    while (leitura_valida == 0) {
        if (scanf("%d", &valor) == 1) {
            tem_lixo = 0;

            /* Verifica caractere por caractere ate o Enter ('\n') */
            proximo_char = getchar();
            while (proximo_char != '\n') {
                /* Aceita espacos ou tabs extras antes do Enter; rejeita qualquer letra ou simbolo */
                if (proximo_char != ' ' && proximo_char != '\t') {
                    tem_lixo = 1;
                }
                proximo_char = getchar();
            }

            if (tem_lixo == 0 && valor >= minimo && valor <= maximo) {
                leitura_valida = 1;
            } else {
                printf("Valor invalido! Digite um numero entre %d e %d: ", minimo, maximo);
            }
        } else {
            /* Limpa todo o lixo restante no buffer ate o Enter */
            while (getchar() != '\n');
            printf("Valor invalido! Digite apenas um numero entre %d e %d: ", minimo, maximo);
        }
    }

    return valor;
}

/* Funcao auxiliar: le numero real (double) aceitando espacos, rejeitando letras e valores extremos */
double ler_double_seguro(void) {
    double valor;
    char proximo_char;
    int leitura_valida;
    int tem_lixo;

    leitura_valida = 0;

    while (leitura_valida == 0) {
        if (scanf("%lf", &valor) == 1) {
            tem_lixo = 0;

            proximo_char = getchar();
            while (proximo_char != '\n') {
                if (proximo_char != ' ' && proximo_char != '\t') {
                    tem_lixo = 1;
                }
                proximo_char = getchar();
            }

            /* Garante que nao houve letras e evita valores extremos que causam overflow/underflow */
            if (tem_lixo == 0 && valor > -1e50 && valor < 1e50) {
                leitura_valida = 1;
            } else {
                printf("Valor invalido! Digite um numero valido: ");
            }
        } else {
            while (getchar() != '\n');
            printf("Valor invalido! Digite apenas um numero valido: ");
        }
    }

    return valor;
}

/* Funcao global para ler os elementos da matriz; exibe indices a partir de [1][1] */
void ler_matriz(double matriz[MAX][MAX], int quantidade_linhas, int quantidade_colunas, const char *nome_matriz) {
    int indice_linha;
    int indice_coluna;

    printf("\n--- Preenchendo a Matriz %s ---\n", nome_matriz);
    for (indice_linha = 0; indice_linha < quantidade_linhas; indice_linha++) {
        for (indice_coluna = 0; indice_coluna < quantidade_colunas; indice_coluna++) {
            printf("Digite o valor para posicao [%d][%d]: ", indice_linha + 1, indice_coluna + 1);
            matriz[indice_linha][indice_coluna] = ler_double_seguro();
        }
    }
}

/* Funcao global 1: Soma Matriz A + Matriz B e exibe o resultado */
void somar_matrizes(double matriz_a[MAX][MAX], double matriz_b[MAX][MAX], double matriz_resultado[MAX][MAX], int quantidade_linhas, int quantidade_colunas) {
    int indice_linha;
    int indice_coluna;

    printf("\nResultado da Adicao (A + B):\n");
    for (indice_linha = 0; indice_linha < quantidade_linhas; indice_linha++) {
        for (indice_coluna = 0; indice_coluna < quantidade_colunas; indice_coluna++) {
            matriz_resultado[indice_linha][indice_coluna] = matriz_a[indice_linha][indice_coluna] + matriz_b[indice_linha][indice_coluna];
            
            /* Evita imprimir -0.00 */
            if (matriz_resultado[indice_linha][indice_coluna] > -1e-9 &&
                matriz_resultado[indice_linha][indice_coluna] < 1e-9) {
                matriz_resultado[indice_linha][indice_coluna] = 0.0;
            }

            printf("%10.2f ", matriz_resultado[indice_linha][indice_coluna]);
        }
        printf("\n");
    }
}

/* Funcao global 6: Calcula e exibe a Matriz Inversa de qualquer ordem (1x1 ate MAXxMAX) */
void calcular_matriz_inversa(double matriz_a[MAX][MAX], double matriz_resultado[MAX][MAX], int quantidade_linhas, int quantidade_colunas) {
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

    /* Verifica se a matriz e quadrada (linhas == colunas) */
    if (quantidade_linhas != quantidade_colunas) {
        printf("\nErro: Para calcular a inversa, linhas e colunas devem ser iguais!\n");
        return;
    }

    ordem = quantidade_linhas;

    /* 1. Monta a matriz estendida [A | I] */
    for (indice_linha = 0; indice_linha < ordem; indice_linha++) {
        for (indice_coluna = 0; indice_coluna < ordem; indice_coluna++) {
            matriz_estendida[indice_linha][indice_coluna] = matriz_a[indice_linha][indice_coluna];

            /* Preenche o lado direito com a Matriz Identidade */
            if (indice_linha == indice_coluna) {
                matriz_estendida[indice_linha][indice_coluna + ordem] = 1.0;
            } else {
                matriz_estendida[indice_linha][indice_coluna + ordem] = 0.0;
            }
        }
    }

    /* 2. Aplica a Eliminacao de Gauss-Jordan */
    for (passo = 0; passo < ordem; passo++) {
        /* Pivoteamento parcial: busca o maior elemento na coluna atual para evitar divisao por zero */
        linha_pivo = passo;
        maior_valor = matriz_estendida[passo][passo];
        if (maior_valor < 0.0) {
            maior_valor = -maior_valor;
        }

        for (indice_linha = passo + 1; indice_linha < ordem; indice_linha++) {
            valor_absoluto = matriz_estendida[indice_linha][passo];
            if (valor_absoluto < 0.0) {
                valor_absoluto = -valor_absoluto;
            }
            if (valor_absoluto > maior_valor) {
                maior_valor = valor_absoluto;
                linha_pivo = indice_linha;
            }
        }

        /* Se o maior pivo da coluna for zero, o determinante e zero (nao tem inversa) */
        if (maior_valor < 1e-12) {
            printf("\nDeterminante = 0. Esta matriz NAO possui inversa!\n");
            return;
        }

        /* Troca a linha atual pela linha com o maior pivo, se necessario */
        if (linha_pivo != passo) {
            for (indice_coluna = 0; indice_coluna < 2 * ordem; indice_coluna++) {
                temporario = matriz_estendida[passo][indice_coluna];
                matriz_estendida[passo][indice_coluna] = matriz_estendida[linha_pivo][indice_coluna];
                matriz_estendida[linha_pivo][indice_coluna] = temporario;
            }
        }

        /* Divide a linha do pivo pelo proprio pivo para que ele vire 1 */
        pivo = matriz_estendida[passo][passo];
        for (indice_coluna = 0; indice_coluna < 2 * ordem; indice_coluna++) {
            matriz_estendida[passo][indice_coluna] = matriz_estendida[passo][indice_coluna] / pivo;
        }

        /* Zera todos os outros elementos acima e abaixo do pivo na coluna atual */
        for (indice_linha = 0; indice_linha < ordem; indice_linha++) {
            if (indice_linha != passo) {
                fator = matriz_estendida[indice_linha][passo];
                for (indice_coluna = 0; indice_coluna < 2 * ordem; indice_coluna++) {
                    matriz_estendida[indice_linha][indice_coluna] -= fator * matriz_estendida[passo][indice_coluna];
                }
            }
        }
    }

    /* 3. Copia o lado direito (agora a inversa) para matriz_resultado e exibe */
    printf("\nMatriz Inversa (%dx%d):\n", ordem, ordem);
    for (indice_linha = 0; indice_linha < ordem; indice_linha++) {
        for (indice_coluna = 0; indice_coluna < ordem; indice_coluna++) {
            matriz_resultado[indice_linha][indice_coluna] = matriz_estendida[indice_linha][indice_coluna + ordem];

            /* Evita imprimir -0.00 */
            if (matriz_resultado[indice_linha][indice_coluna] > -1e-9 &&
                matriz_resultado[indice_linha][indice_coluna] < 1e-9) {
                matriz_resultado[indice_linha][indice_coluna] = 0.0;
            }

            printf("%10.2f ", matriz_resultado[indice_linha][indice_coluna]);
        }
        printf("\n");
    }
}
