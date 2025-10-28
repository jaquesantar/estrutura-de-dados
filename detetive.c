#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma sala da mansão
struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
};

// Estrutura para a árvore BST de pistas
struct PistaNode {
    char texto[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
};

// Função para criar uma nova sala com pista
struct Sala* criarSala(const char* nome, const char* pista) {
    struct Sala* novaSala = (struct Sala*)malloc(sizeof(struct Sala));
    if (novaSala == NULL) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// Função para inserir pista na BST
struct PistaNode* inserirPista(struct PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        struct PistaNode* novo = (struct PistaNode*)malloc(sizeof(struct PistaNode));
        strcpy(novo->texto, pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    
    int comparacao = strcmp(pista, raiz->texto);
    if (comparacao < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (comparacao > 0)
        raiz->direita = inserirPista(raiz->direita, pista);
    
    return raiz;
}

// Função para exibir pistas em ordem alfabética
void exibirPistas(struct PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->texto);
        exibirPistas(raiz->direita);
    }
}

// Função para explorar as salas e coletar pistas
void explorarSalasComPistas(struct Sala* salaAtual, struct PistaNode** pistas) {
    char escolha;
    
    while (salaAtual != NULL) {
        printf("\nVoce esta em: %s\n", salaAtual->nome);
        
        // Se há pista na sala, mostra e adiciona à BST
        if (strlen(salaAtual->pista) > 0) {
            printf("Pista encontrada: %s\n", salaAtual->pista);
            *pistas = inserirPista(*pistas, salaAtual->pista);
        }
        
        // Verifica se é uma sala final
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Esta sala nao tem saidas.\n");
            return;
        }
        
        printf("\nEscolha uma direcao:\n");
        if (salaAtual->esquerda != NULL)
            printf("e - Ir para a esquerda\n");
        if (salaAtual->direita != NULL)
            printf("d - Ir para a direita\n");
        printf("s - Sair da exploracao\n");
        
        printf("Opcao: ");
        scanf(" %c", &escolha);
        
        switch (escolha) {
            case 'e':
                if (salaAtual->esquerda != NULL)
                    salaAtual = salaAtual->esquerda;
                else
                    printf("Nao ha caminho para a esquerda!\n");
                break;
                
            case 'd':
                if (salaAtual->direita != NULL)
                    salaAtual = salaAtual->direita;
                else
                    printf("Nao ha caminho para a direita!\n");
                break;
                
            case 's':
                return;
                
            default:
                printf("Opcao invalida!\n");
        }
    }
}

// Função para liberar a árvore de salas
void liberarArvore(struct Sala* sala) {
    if (sala != NULL) {
        liberarArvore(sala->esquerda);
        liberarArvore(sala->direita);
        free(sala);
    }
}

// Função para liberar a árvore de pistas
void liberarPistas(struct PistaNode* pista) {
    if (pista != NULL) {
        liberarPistas(pista->esquerda);
        liberarPistas(pista->direita);
        free(pista);
    }
}

int main() {
    // Criação da mansão com pistas
    struct Sala* hall = criarSala("Hall de Entrada", "Pegadas molhadas no chao");
    hall->esquerda = criarSala("Sala de Estar", "Janela quebrada");
    hall->direita = criarSala("Sala de Jantar", "Talheres fora do lugar");
    
    hall->esquerda->esquerda = criarSala("Biblioteca", "Livro sobre venenos aberto");
    hall->esquerda->direita = criarSala("Escritorio", "Cofre arrombado");
    
    hall->direita->esquerda = criarSala("Cozinha", "Faca ensanguentada");
    hall->direita->direita = criarSala("Jardim", "Plantas pisoteadas");
    
    // Inicialização da árvore de pistas
    struct PistaNode* pistas = NULL;
    
    printf("=== Mansao Misteriosa ===\n");
    printf("Explore as salas e colete pistas!\n");
    printf("Use 'e' para esquerda, 'd' para direita e 's' para sair.\n");
    
    // Inicia exploração
    explorarSalasComPistas(hall, &pistas);
    
    // Exibe pistas coletadas
    printf("\nPistas coletadas (em ordem alfabetica):\n");
    exibirPistas(pistas);
    
    // Libera memória
    liberarArvore(hall);
    liberarPistas(pistas);
    
    return 0;
}