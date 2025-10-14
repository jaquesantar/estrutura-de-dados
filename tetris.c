#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Estrutura para representar uma peça
struct Peca {
    char nome;     // Tipo da peça (I, O, T, L)
    int id;        // Identificador único
};

// Estrutura para representar a fila circular
struct Fila {
    struct Peca pecas[TAM_FILA];
    int inicio;    // Índice do início da fila
    int fim;       // Índice do fim da fila
    int total;     // Quantidade atual de peças
    int nextId;    // Próximo ID disponível
};

// Função para inicializar a fila
void inicializarFila(struct Fila* fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->total = 0;
    fila->nextId = 0;
}

// Função para verificar se a fila está cheia
int filaCheia(struct Fila* fila) {
    return fila->total >= TAM_FILA;
}

// Função para verificar se a fila está vazia
int filaVazia(struct Fila* fila) {
    return fila->total == 0;
}

// Função para gerar uma peça aleatória
struct Peca gerarPeca(struct Fila* fila) {
    struct Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    novaPeca.nome = tipos[rand() % 4];
    novaPeca.id = fila->nextId++;
    return novaPeca;
}

// Função para inserir uma peça na fila (enqueue)
void inserirPeca(struct Fila* fila) {
    if (filaCheia(fila)) {
        printf("Fila cheia! Nao e possivel inserir mais pecas.\n");
        return;
    }

    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->pecas[fila->fim] = gerarPeca(fila);
    fila->total++;
    printf("Nova peca inserida: [%c %d]\n", 
           fila->pecas[fila->fim].nome, 
           fila->pecas[fila->fim].id);
}

// Função para remover uma peça da fila (dequeue)
void jogarPeca(struct Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Nao ha pecas para jogar.\n");
        return;
    }

    printf("Peca jogada: [%c %d]\n", 
           fila->pecas[fila->inicio].nome, 
           fila->pecas[fila->inicio].id);

    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->total--;
}

// Função para exibir o estado atual da fila
void exibirFila(struct Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }

    printf("\nFila de pecas:\n");
    int pos = fila->inicio;
    for (int i = 0; i < fila->total; i++) {
        printf("[%c %d] ", fila->pecas[pos].nome, fila->pecas[pos].id);
        pos = (pos + 1) % TAM_FILA;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));  // Inicializa gerador de números aleatórios
    
    struct Fila fila;
    inicializarFila(&fila);

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        inserirPeca(&fila);
    }

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Jogar peca (dequeue)\n");
        printf("2. Inserir nova peca (enqueue)\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila);
                break;
            case 0:
                printf("Programa encerrado!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        if (opcao != 0) {
            exibirFila(&fila);
        }

    } while (opcao != 0);

    return 0;
}