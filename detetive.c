#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10
#define MAX_SUSPEITOS 5

// Estruturas
struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
};

struct PistaNode {
    char texto[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
};

struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode* proximo;
};

struct HashTable {
    struct HashNode* table[TAM_HASH];
};

// Funções auxiliares
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

// Funções para hash table
int hashFunction(char* pista) {
    int soma = 0;
    for (int i = 0; pista[i] != '\0'; i++) {
        soma += pista[i];
    }
    return soma % TAM_HASH;
}

void inicializarHash(struct HashTable* hashTable) {
    for (int i = 0; i < TAM_HASH; i++) {
        hashTable->table[i] = NULL;
    }
}

void inserirNaHash(struct HashTable* hashTable, char* pista, char* suspeito) {
    int index = hashFunction(pista);
    struct HashNode* novoNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    strcpy(novoNode->pista, pista);
    strcpy(novoNode->suspeito, suspeito);
    novoNode->proximo = hashTable->table[index];
    hashTable->table[index] = novoNode;
}

char* encontrarSuspeito(struct HashTable* hashTable, char* pista) {
    int index = hashFunction(pista);
    struct HashNode* atual = hashTable->table[index];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void exibirPistas(struct PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->texto);
        exibirPistas(raiz->direita);
    }
}

void explorarSalasComPistas(struct Sala* salaAtual, struct PistaNode** pistas) {
    char escolha;
    while (salaAtual != NULL) {
        printf("\nVoce esta em: %s\n", salaAtual->nome);
        
        if (strlen(salaAtual->pista) > 0) {
            printf("Pista encontrada: %s\n", salaAtual->pista);
            *pistas = inserirPista(*pistas, salaAtual->pista);
        }
        
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

int contarPistasPorSuspeito(struct HashTable* hashTable, struct PistaNode* pistas, char* suspeito) {
    int count = 0;
    if (pistas != NULL) {
        char* suspeitoDaPista = encontrarSuspeito(hashTable, pistas->texto);
        if (suspeitoDaPista && strcmp(suspeitoDaPista, suspeito) == 0) {
            count++;
        }
        count += contarPistasPorSuspeito(hashTable, pistas->esquerda, suspeito);
        count += contarPistasPorSuspeito(hashTable, pistas->direita, suspeito);
    }
    return count;
}

void verificarSuspeitoFinal(struct HashTable* hashTable, struct PistaNode* pistas) {
    char suspeito[50];
    printf("\nCom base nas pistas coletadas, quem voce acusa? ");
    scanf(" %[^\n]s", suspeito);
    
    int numPistas = contarPistasPorSuspeito(hashTable, pistas, suspeito);
    
    printf("\nAnalisando acusacao contra %s...\n", suspeito);
    if (numPistas >= 2) {
        printf("ACUSACAO CORRETA! %d pistas apontam para %s!\n", numPistas, suspeito);
    } else {
        printf("ACUSACAO INCORRETA! Apenas %d pista(s) apontam para %s.\n", numPistas, suspeito);
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
    
    // Inicialização das estruturas
    struct PistaNode* pistas = NULL;
    struct HashTable hashTable;
    inicializarHash(&hashTable);
    
    // Associar pistas a suspeitos
    inserirNaHash(&hashTable, "Pegadas molhadas no chao", "Mordomo");
    inserirNaHash(&hashTable, "Janela quebrada", "Ladrao");
    inserirNaHash(&hashTable, "Talheres fora do lugar", "Mordomo");
    inserirNaHash(&hashTable, "Livro sobre venenos aberto", "Professor");
    inserirNaHash(&hashTable, "Cofre arrombado", "Ladrao");
    inserirNaHash(&hashTable, "Faca ensanguentada", "Cozinheiro");
    inserirNaHash(&hashTable, "Plantas pisoteadas", "Jardineiro");
    
    printf("=== Mansao Misteriosa ===\n");
    printf("Explore as salas e colete pistas!\n");
    
    // Iniciar exploração
    explorarSalasComPistas(hall, &pistas);
    
    // Exibir pistas coletadas
    printf("\nPistas coletadas (em ordem alfabetica):\n");
    exibirPistas(pistas);
    
    // Realizar acusação
    verificarSuspeitoFinal(&hashTable, pistas);
    
    // Liberar memória
    // ... código de limpeza aqui ...
    
    return 0;
}