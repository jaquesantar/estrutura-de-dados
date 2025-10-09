#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct Item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para inserir um novo item
void inserirItem(struct Item mochila[], int* totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n=== Cadastro de Item ===\n");
    printf("Nome do item: ");
    fgets(mochila[*totalItens].nome, sizeof(mochila[*totalItens].nome), stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';

    printf("Tipo (arma/municao/cura): ");
    fgets(mochila[*totalItens].tipo, sizeof(mochila[*totalItens].tipo), stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    limparBuffer();

    (*totalItens)++;
    printf("\nItem cadastrado com sucesso!\n");
}

// Função para remover um item
void removerItem(struct Item mochila[], int* totalItens) {
    if (*totalItens == 0) {
        printf("\nMochila vazia! Nada para remover.\n");
        return;
    }

    char nomeItem[30];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nomeItem, sizeof(nomeItem), stdin);
    nomeItem[strcspn(nomeItem, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeItem) == 0) {
            // Move todos os itens uma posição para trás
            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*totalItens)--;
            encontrado = 1;
            printf("\nItem removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado na mochila!\n");
    }
}

// Função para listar todos os itens
void listarItens(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    for (int i = 0; i < totalItens; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
        printf("--------------------\n");
    }
}

// Função para buscar um item pelo nome
void buscarItem(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeItem[30];
    printf("\nDigite o nome do item a ser buscado: ");
    fgets(nomeItem, sizeof(nomeItem), stdin);
    nomeItem[strcspn(nomeItem, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeItem) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado na mochila!\n");
    }
}

int main() {
    struct Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n=== MENU DA MOCHILA ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}