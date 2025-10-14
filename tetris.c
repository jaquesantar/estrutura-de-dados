#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

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
};

// Estrutura para representar a pilha de reserva
struct Pilha {
    struct Peca pecas[TAM_PILHA];
    int topo;      // Índice do topo da pilha
};

// Variável global para gerar IDs únicos
int nextId = 0;

// Funções para a Fila
void inicializarFila(struct Fila* fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->total = 0;
}

int filaCheia(struct Fila* fila) {
    return fila->total >= TAM_FILA;
}

int filaVazia(struct Fila* fila) {
    return fila->total == 0;
}

// Funções para a Pilha
void inicializarPilha(struct Pilha* pilha) {
    pilha->topo = -1;
}

int pilhaCheia(struct Pilha* pilha) {
    return pilha->topo >= TAM_PILHA - 1;
}

int pilhaVazia(struct Pilha* pilha) {
    return pilha->topo == -1;
}

// Função para gerar uma peça aleatória
struct Peca gerarPeca() {
    struct Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    novaPeca.nome = tipos[rand() % 4];
    novaPeca.id = nextId++;
    return novaPeca;
}

// Função para inserir uma peça na fila
void inserirPeca(struct Fila* fila) {
    if (filaCheia(fila)) {
        printf("Fila cheia!\n");
        return;
    }
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->pecas[fila->fim] = gerarPeca();
    fila->total++;
}

// Função para jogar a peça da frente da fila
void jogarPeca(struct Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }
    
    printf("Peca jogada: [%c %d]\n", 
           fila->pecas[fila->inicio].nome, 
           fila->pecas[fila->inicio].id);
    
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->total--;
    
    // Gera nova peça automaticamente
    inserirPeca(fila);
}

// Função para reservar uma peça (move da fila para a pilha)
void reservarPeca(struct Fila* fila, struct Pilha* pilha) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }
    if (pilhaCheia(pilha)) {
        printf("Pilha de reserva cheia!\n");
        return;
    }
    
    pilha->topo++;
    pilha->pecas[pilha->topo] = fila->pecas[fila->inicio];
    printf("Peca reservada: [%c %d]\n", 
           pilha->pecas[pilha->topo].nome, 
           pilha->pecas[pilha->topo].id);
    
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->total--;
    
    // Gera nova peça automaticamente
    inserirPeca(fila);
}

// Função para usar uma peça reservada
void usarPecaReservada(struct Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha de reserva vazia!\n");
        return;
    }
    
    printf("Peca usada da reserva: [%c %d]\n", 
           pilha->pecas[pilha->topo].nome, 
           pilha->pecas[pilha->topo].id);
    
    pilha->topo--;
}

// Função para exibir o estado atual do jogo
void exibirEstado(struct Fila* fila, struct Pilha* pilha) {
    printf("\n=== Estado Atual ===\n");
    
    // Exibe a fila
    printf("Fila de pecas:  ");
    if (!filaVazia(fila)) {
        int pos = fila->inicio;
        for (int i = 0; i < fila->total; i++) {
            printf("[%c %d] ", fila->pecas[pos].nome, fila->pecas[pos].id);
            pos = (pos + 1) % TAM_FILA;
        }
    } else {
        printf("(vazia)");
    }
    printf("\n");
    
    // Exibe a pilha
    printf("Pilha reserva: ");
    if (!pilhaVazia(pilha)) {
        printf("(Topo -> Base): ");
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->pecas[i].nome, pilha->pecas[i].id);
        }
    } else {
        printf("(vazia)");
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    
    struct Fila fila;
    struct Pilha pilha;
    int opcao;
    
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        inserirPeca(&fila);
    }
    
    do {
        exibirEstado(&fila, &pilha);
        
        printf("\n=== MENU ===\n");
        printf("1. Jogar peca\n");
        printf("2. Reservar peca\n");
        printf("3. Usar peca reservada\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                reservarPeca(&fila, &pilha);
                break;
            case 3:
                usarPecaReservada(&pilha);
                break;
            case 0:
                printf("Programa encerrado!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
    } while (opcao != 0);
    
    return 0;
}