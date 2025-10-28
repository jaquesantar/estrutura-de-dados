#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma sala da mansão
struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
};

// Função para criar uma nova sala
struct Sala* criarSala(const char* nome) {
    struct Sala* novaSala = (struct Sala*)malloc(sizeof(struct Sala));
    if (novaSala == NULL) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// Função para explorar as salas da mansão
void explorarSalas(struct Sala* salaAtual) {
    char escolha;
    
    while (salaAtual != NULL) {
        printf("\nVoce esta na %s\n", salaAtual->nome);
        
        // Verifica se é uma sala final (nó folha)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Esta sala nao tem saidas. Exploracao concluida!\n");
            return;
        }
        
        // Mostra as opções disponíveis
        printf("\nEscolha uma direcao:\n");
        if (salaAtual->esquerda != NULL) {
            printf("e - Ir para a esquerda\n");
        }
        if (salaAtual->direita != NULL) {
            printf("d - Ir para a direita\n");
        }
        printf("s - Sair da exploracao\n");
        
        printf("Opcao: ");
        scanf(" %c", &escolha);
        
        switch (escolha) {
            case 'e':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("Nao ha caminho para a esquerda!\n");
                }
                break;
                
            case 'd':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("Nao ha caminho para a direita!\n");
                }
                break;
                
            case 's':
                printf("Exploracao encerrada.\n");
                return;
                
            default:
                printf("Opcao invalida!\n");
        }
    }
}

// Função para liberar a memória da árvore
void liberarArvore(struct Sala* sala) {
    if (sala != NULL) {
        liberarArvore(sala->esquerda);
        liberarArvore(sala->direita);
        free(sala);
    }
}

int main() {
    // Criação da estrutura da mansão
    struct Sala* hall = criarSala("Hall de Entrada");
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Sala de Jantar");
    
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Escritorio");
    
    hall->direita->esquerda = criarSala("Cozinha");
    hall->direita->direita = criarSala("Jardim");
    
    printf("Bem-vindo a Mansao Misteriosa!\n");
    printf("Explore as salas usando as teclas 'e' (esquerda) e 'd' (direita).\n");
    printf("Use 's' para sair da exploracao.\n");
    
    // Inicia a exploração a partir do hall
    explorarSalas(hall);
    
    // Libera a memória alocada
    liberarArvore(hall);
    
    return 0;
}