#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Necessário para a função abs() (valor absoluto)

// --- Constantes Globais ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5 // Tamanho fixo para as matrizes de habilidade (ex: 5x5)

// --- Protótipos das Funções ---

// Funções do nível anterior (simplificadas para focar na nova lógica)
void inicializar_matriz(int tamanho, int matriz[tamanho][tamanho], int valor);
void configurar_cenario_padrao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibir_tabuleiro_final(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// Novas funções para habilidades
void criar_matriz_cone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_matriz_cruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_matriz_octaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                        int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                        int origem_linha, int origem_coluna);

// --- Função Principal ---
int main() {
    // 1. Definir o Tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    configurar_cenario_padrao(tabuleiro); // Posiciona alguns navios para o exemplo

    // 2. Criar Matrizes de Habilidade
    int habilidade_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Utiliza condicionais dentro de loops para gerar as formas dinamicamente
    criar_matriz_cone(habilidade_cone);
    criar_matriz_cruz(habilidade_cruz);
    criar_matriz_octaedro(habilidade_octaedro);
    
    // 3. Integrar Habilidades ao Tabuleiro
    // Define um ponto de origem para cada habilidade e aplica sobre o tabuleiro
    printf("Aplicando habilidades no tabuleiro...\n\n");
    aplicar_habilidade(tabuleiro, habilidade_cone, 0, 4);      // Cone no topo do tabuleiro
    aplicar_habilidade(tabuleiro, habilidade_cruz, 7, 7);      // Cruz no canto inferior direito
    aplicar_habilidade(tabuleiro, habilidade_octaedro, 4, 3);  // Octaedro no centro-esquerda

    // 4. Exibir o Tabuleiro com Habilidade
    exibir_tabuleiro_final(tabuleiro);

    return 0;
}

// --- Implementação das Funções de Habilidade ---

/**
 * @brief Cria a matriz de efeito para a habilidade CONE.
 * A forma se expande para baixo a partir do centro da primeira linha.
 * @param habilidade A matriz 5x5 que representará a habilidade.
 */
void criar_matriz_cone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    inicializar_matriz(TAMANHO_HABILIDADE, habilidade, 0);
    int centro = TAMANHO_HABILIDADE / 2;

    // Utiliza loops aninhados e condicionais para criar a forma
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) { // linha
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) { // coluna
            // A condição define a largura do cone em cada linha
            if (j >= centro - i && j <= centro + i) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * @brief Cria a matriz de efeito para a habilidade CRUZ.
 * A forma é uma linha horizontal e uma vertical que se cruzam no centro.
 * @param habilidade A matriz 5x5 que representará a habilidade.
 */
// CORREÇÃO APLICADA AQUI: TAMANHO_HABILidade -> TAMANHO_HABILIDADE
void criar_matriz_cruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    inicializar_matriz(TAMANHO_HABILIDADE, habilidade, 0);
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A condição verifica se a posição está na linha ou coluna central
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * @brief Cria a matriz de efeito para a habilidade OCTAEDRO (vista frontal/losango).
 * Utiliza a distância de Manhattan para criar a forma de diamante.
 * @param habilidade A matriz 5x5 que representará a habilidade.
 */
void criar_matriz_octaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    inicializar_matriz(TAMANHO_HABILIDADE, habilidade, 0);
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A soma das distâncias absolutas do centro define o losango
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

/**
 * @brief Sobrepõe uma matriz de habilidade ao tabuleiro principal.
 * @param tabuleiro O tabuleiro 10x10 do jogo.
 * @param habilidade A matriz 5x5 da habilidade.
 * @param origem_linha A linha do tabuleiro onde o centro da habilidade será aplicado.
 * @param origem_coluna A coluna do tabuleiro onde o centro da habilidade será aplicado.
 */
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                        int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                        int origem_linha, int origem_coluna) {
                            
    int centro_habilidade = TAMANHO_HABILIDADE / 2;

    // Itera sobre a matriz de habilidade 5x5
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Se a posição na matriz de habilidade for 1 (afetada)
            if (habilidade[i][j] == 1) {
                // Calcula a coordenada correspondente no tabuleiro principal
                // O cálculo (i - centro) mapeia a coordenada da matriz de habilidade
                // para um deslocamento relativo ao ponto de origem.
                int alvo_linha = origem_linha + (i - centro_habilidade);
                int alvo_coluna = origem_coluna + (j - centro_habilidade);

                // Condicional para garantir que a área de efeito não saia dos limites do tabuleiro
                if (alvo_linha >= 0 && alvo_linha < TAMANHO_TABULEIRO &&
                    alvo_coluna >= 0 && alvo_coluna < TAMANHO_TABULEIRO) {
                    
                    // Marca a posição no tabuleiro com 5, somente se for água (0)
                    if (tabuleiro[alvo_linha][alvo_coluna] == 0) {
                        tabuleiro[alvo_linha][alvo_coluna] = 5;
                    }
                }
            }
        }
    }
}


// --- Funções Auxiliares (reaproveitadas e adaptadas) ---

/**
 * @brief Preenche uma matriz quadrada com um valor específico.
 * @param tamanho O lado da matriz quadrada.
 * @param matriz A matriz a ser preenchida.
 * @param valor O valor a ser inserido em todas as posições.
 */
void inicializar_matriz(int tamanho, int matriz[tamanho][tamanho], int valor) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            matriz[i][j] = valor;
        }
    }
}

/**
 * @brief Configura o tabuleiro com 0s (água) e alguns navios (3).
 * @param tabuleiro O tabuleiro 10x10 do jogo.
 */
void configurar_cenario_padrao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    inicializar_matriz(TAMANHO_TABULEIRO, tabuleiro, 0);
    // Adiciona alguns navios para visualização
    tabuleiro[1][1] = 3; tabuleiro[1][2] = 3; tabuleiro[1][3] = 3; // Horizontal
    tabuleiro[4][8] = 3; tabuleiro[5][8] = 3; tabuleiro[6][8] = 3; // Vertical
    tabuleiro[8][1] = 3; tabuleiro[8][2] = 3; // Pedaço de navio
}

/**
 * @brief Exibe o tabuleiro final com uma legenda clara.
 * @param tabuleiro O tabuleiro 10x10 do jogo.
 */
void exibir_tabuleiro_final(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("--- Tabuleiro Final com Áreas de Efeito ---\n");
    printf("Legenda: 0 = Água | 3 = Navio | 5 = Área de Efeito\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}