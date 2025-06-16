#include <stdio.h>
#include <stdbool.h> // Para usar o tipo de dado bool (true/false) na validação

// --- Requisitos Não Funcionais: Legibilidade e Manutenção ---
// Constantes para definir os tamanhos fixos, facilitando futuras alterações.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Protótipos das funções para organizar o código
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool validar_posicionamento(int h_linha, int h_coluna, int v_linha, int v_coluna);

int main() {
    // --- 1. Represente o Tabuleiro ---
    // Matriz (array bidimensional) 10x10 para o tabuleiro do jogo.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com 0 (água) em todas as posições.
    inicializar_tabuleiro(tabuleiro);

    // --- 2. Posicione os Navios ---
    // Coordenadas iniciais definidas diretamente no código, como solicitado.
    // Lembre-se que em C, os índices de arrays começam em 0.
    // Linha 2, Coluna 2 (índices 1, 1) para o navio horizontal.
    int navio_horizontal_linha = 1;
    int navio_horizontal_coluna = 1;

    // Linha 4, Coluna 5 (índices 3, 4) para o navio vertical.
    int navio_vertical_linha = 3;
    int navio_vertical_coluna = 4;

    // --- Requisitos Funcionais: Validação de Posições e Sobreposição ---
    if (validar_posicionamento(navio_horizontal_linha, navio_horizontal_coluna, navio_vertical_linha, navio_vertical_coluna)) {
        // Se a validação for bem-sucedida, posiciona os navios na matriz.
        
        // Posiciona o navio HORIZONTAL (3 posições)
        // Percorre as colunas a partir da posição inicial.
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_horizontal_linha][navio_horizontal_coluna + i] = 3;
        }

        // Posiciona o navio VERTICAL (3 posições)
        // Percorre as linhas a partir da posição inicial.
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_vertical_linha + i][navio_vertical_coluna] = 3;
        }

        // --- 3. Exiba o Tabuleiro ---
        printf("--- Tabuleiro do Batalha Naval (Nível Novato) ---\n");
        printf("0 = Água | 3 = Navio\n\n");
        exibir_tabuleiro(tabuleiro);

    } else {
        // Caso a validação falhe, exibe uma mensagem de erro.
        printf("ERRO: Posição dos navios é inválida! Verifique os limites do tabuleiro e a sobreposição.\n");
        return 1; // Retorna 1 para indicar que o programa terminou com erro.
    }

    return 0; // Sucesso
}

/**
 * @brief Inicializa a matriz do tabuleiro com o valor 0.
 * @param tabuleiro A matriz 10x10 a ser inicializada.
 * * --- Documentação: Comentário claro explicando a função. ---
 */
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

/**
 * @brief Exibe o estado atual do tabuleiro no console.
 * @param tabuleiro A matriz 10x10 a ser exibida.
 * * --- Dica: Usa loops aninhados e printf para exibir de forma organizada. ---
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime cada elemento com um espaço para melhor visualização
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Pula uma linha ao final de cada linha da matriz
    }
}

/**
 * @brief Valida se os navios estão dentro dos limites e não se sobrepõem.
 * @param h_linha Linha inicial do navio horizontal.
 * @param h_coluna Coluna inicial do navio horizontal.
 * @param v_linha Linha inicial do navio vertical.
 * @param v_coluna Coluna inicial do navio vertical.
 * @return Retorna 'true' se o posicionamento for válido, e 'false' caso contrário.
 */
bool validar_posicionamento(int h_linha, int h_coluna, int v_linha, int v_coluna) {
    // 1. Validação de Limites
    // Verifica se o navio horizontal cabe no tabuleiro
    if (h_coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return false;
    }
    // Verifica se o navio vertical cabe no tabuleiro
    if (v_linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return false;
    }

    // 2. Validação de Sobreposição (simplificada)
    // Itera por cada parte de um navio e verifica se a coordenada bate com alguma parte do outro.
    for (int i = 0; i < TAMANHO_NAVIO; i++) { // Partes do navio horizontal
        int pos_h_col = h_coluna + i;

        for (int j = 0; j < TAMANHO_NAVIO; j++) { // Partes do navio vertical
            int pos_v_lin = v_linha + j;

            // Se a linha do navio horizontal for igual a uma das linhas do vertical
            // E a coluna do navio vertical for igual a uma das colunas do horizontal,
            // então há uma sobreposição.
            if (h_linha == pos_v_lin && pos_h_col == v_coluna) {
                return false; // Sobreposição detectada
            }
        }
    }

    // Se passou por todas as verificações, o posicionamento é válido.
    return true;
}