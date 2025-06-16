#include <stdio.h>
#include <stdbool.h> // Para usar o tipo de dado bool (true/false)

// --- Requisitos Não Funcionais: Legibilidade e Manutenção ---
// Constantes para tamanhos fixos.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NUMERO_DE_NAVIOS 4

/**
 * @brief Enum para definir as orientações possíveis de um navio.
 * Isso torna o código mais legível do que usar números mágicos (0, 1, 2, 3).
 */
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_PRINCIPAL,  // Diagonal onde linha e coluna aumentam
    DIAGONAL_SECUNDARIA  // Diagonal onde linha aumenta e coluna diminui
} Orientacao;

/**
 * @brief Struct para representar um navio.
 * Agrupa todas as informações relevantes de um navio em um único tipo de dado.
 */
typedef struct {
    int linha_inicial;
    int coluna_inicial;
    Orientacao orientacao;
} Navio;

// --- Protótipos das Funções ---
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio navio);

// --- Função Principal ---
int main() {
    // 1. Criar um Tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializar_tabuleiro(tabuleiro);

    // 2. Posicionar Quatro Navios (coordenadas e orientações definidas no código)
    Navio navios[NUMERO_DE_NAVIOS] = {
        {1, 1, HORIZONTAL},         // Navio 1: Horizontal na linha 1, coluna 1
        {2, 8, VERTICAL},           // Navio 2: Vertical na linha 2, coluna 8
        {3, 2, DIAGONAL_PRINCIPAL}, // Navio 3: Diagonal principal na linha 3, coluna 2
        {7, 4, DIAGONAL_SECUNDARIA} // Navio 4: Diagonal secundária na linha 7, coluna 4
    };

    bool todos_posicionados = true;
    // Laço para posicionar cada navio sequencialmente
    for (int i = 0; i < NUMERO_DE_NAVIOS; i++) {
        if (!posicionar_navio(tabuleiro, navios[i])) {
            printf("ERRO: Falha ao posicionar o navio %d. Verifique limites ou sobreposição.\n", i + 1);
            todos_posicionados = false;
            break; // Interrompe se um navio não puder ser posicionado
        }
    }

    // 3. Exibir o Tabuleiro
    if (todos_posicionados) {
        printf("--- Tabuleiro do Batalha Naval (Nível Intermediário) ---\n");
        printf("0 = Água | 3 = Navio\n\n");
        exibir_tabuleiro(tabuleiro);
    }

    return 0;
}

/**
 * @brief Valida e posiciona um único navio no tabuleiro.
 * Esta função verifica limites e sobreposição ANTES de modificar o tabuleiro.
 * @param tabuleiro A matriz do jogo.
 * @param navio A struct contendo os dados do navio a ser posicionado.
 * @return 'true' se o navio foi posicionado com sucesso, 'false' caso contrário.
 */
bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio navio) {
    // Array temporário para armazenar as coordenadas que o navio ocupará.
    int posicoes[TAMANHO_NAVIO][2]; // [i][0] para linha, [i][1] para coluna

    // Calcula as coordenadas para cada parte do navio de acordo com sua orientação
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        switch (navio.orientacao) {
            case HORIZONTAL:
                posicoes[i][0] = navio.linha_inicial;
                posicoes[i][1] = navio.coluna_inicial + i;
                break;
            case VERTICAL:
                posicoes[i][0] = navio.linha_inicial + i;
                posicoes[i][1] = navio.coluna_inicial;
                break;
            case DIAGONAL_PRINCIPAL:
                posicoes[i][0] = navio.linha_inicial + i;
                posicoes[i][1] = navio.coluna_inicial + i;
                break;
            case DIAGONAL_SECUNDARIA:
                posicoes[i][0] = navio.linha_inicial + i;
                posicoes[i][1] = navio.coluna_inicial - i;
                break;
        }
    }

    // --- Validação ---
    // 1. Verifica se todas as posições calculadas estão dentro dos limites E não estão ocupadas.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];

        // Validação de limites
        if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
            return false; // Fora do tabuleiro
        }
        // Validação de sobreposição
        if (tabuleiro[linha][coluna] != 0) {
            return false; // Posição já ocupada por outro navio
        }
    }

    // --- Posicionamento ---
    // Se todas as validações passaram, modifica o tabuleiro.
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];
        tabuleiro[linha][coluna] = 3;
    }

    return true; // Navio posicionado com sucesso
}


/**
 * @brief Inicializa a matriz do tabuleiro com o valor 0 (água).
 * @param tabuleiro A matriz 10x10 a ser inicializada.
 */
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

/**
 * @brief Exibe o estado atual do tabuleiro no console.
 * @param tabuleiro A matriz 10x10 a ser exibida.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}