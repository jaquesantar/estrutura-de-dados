#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// Contadores globais para comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Estruturas
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

struct No {
    struct Item dados;
    struct No* proximo;
};

// Funções auxiliares
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// IMPLEMENTAÇÃO COM VETOR
void inserirItemVetor(struct Item mochila[], int* totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\n=== Cadastro de Item ===\n");
    printf("Nome: ");
    fgets(mochila[*totalItens].nome, 30, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[*totalItens].tipo, 20, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    limparBuffer();

    (*totalItens)++;
}

void removerItemVetor(struct Item mochila[], int* totalItens) {
    if (*totalItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*totalItens)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

void ordenarVetor(struct Item mochila[], int totalItens) {
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                struct Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome!\n");
}

void buscarSequencialVetor(struct Item mochila[], int totalItens) {
    comparacoesSequencial = 0;
    char nome[30];
    printf("Nome do item: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\nNome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
            return;
        }
    }
    printf("Item nao encontrado! Comparacoes realizadas: %d\n", comparacoesSequencial);
}

void buscarBinariaVetor(struct Item mochila[], int totalItens) {
    comparacoesBinaria = 0;
    char nome[30];
    printf("Nome do item: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int inicio = 0, fim = totalItens - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int comparacao = strcmp(mochila[meio].nome, nome);
        
        if (comparacao == 0) {
            printf("\nItem encontrado!\nNome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
            return;
        }
        if (comparacao > 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    printf("Item nao encontrado! Comparacoes realizadas: %d\n", comparacoesBinaria);
}

void listarVetor(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    printf("\n=== Items na Mochila ===\n");
    for (int i = 0; i < totalItens; i++) {
        printf("\nItem %d:\nNome: %s\nTipo: %s\nQuantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// IMPLEMENTAÇÃO COM LISTA ENCADEADA
struct No* inserirItemLista(struct No* inicio) {
    struct No* novo = (struct No*)malloc(sizeof(struct No));
    if (!novo) {
        printf("Erro de alocacao!\n");
        return inicio;
    }

    printf("\n=== Cadastro de Item ===\n");
    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    limparBuffer();

    novo->proximo = inicio;
    return novo;
}

struct No* removerItemLista(struct No* inicio) {
    if (!inicio) {
        printf("\nMochila vazia!\n");
        return NULL;
    }

    char nome[30];
    printf("Nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    struct No *atual = inicio, *anterior = NULL;

    while (atual && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("Item nao encontrado!\n");
        return inicio;
    }

    if (!anterior) inicio = atual->proximo;
    else anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido!\n");
    return inicio;
}

void buscarItemLista(struct No* inicio) {
    if (!inicio) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    struct No* atual = inicio;
    int comparacoes = 0;

    while (atual) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\nItem encontrado!\nNome: %s\nTipo: %s\nQuantidade: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item nao encontrado! Comparacoes realizadas: %d\n", comparacoes);
}

void listarLista(struct No* inicio) {
    if (!inicio) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n=== Items na Mochila ===\n");
    struct No* atual = inicio;
    int i = 1;
    while (atual) {
        printf("\nItem %d:\nNome: %s\nTipo: %s\nQuantidade: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void liberarLista(struct No* inicio) {
    while (inicio) {
        struct No* temp = inicio;
        inicio = inicio->proximo;
        free(temp);
    }
}

int main() {
    int opcaoEstrutura;
    printf("Escolha a estrutura:\n1 - Vetor\n2 - Lista Encadeada\nOpcao: ");
    scanf("%d", &opcaoEstrutura);
    limparBuffer();

    struct Item mochilaVetor[MAX_ITENS];
    struct No* mochilaLista = NULL;
    int totalItensVetor = 0;
    int opcao;

    do {
        printf("\n=== MENU DA MOCHILA ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        if (opcaoEstrutura == 1) {
            printf("5 - Ordenar itens\n");
            printf("6 - Busca binaria\n");
        }
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                if (opcaoEstrutura == 1) inserirItemVetor(mochilaVetor, &totalItensVetor);
                else mochilaLista = inserirItemLista(mochilaLista);
                break;
            case 2:
                if (opcaoEstrutura == 1) removerItemVetor(mochilaVetor, &totalItensVetor);
                else mochilaLista = removerItemLista(mochilaLista);
                break;
            case 3:
                if (opcaoEstrutura == 1) listarVetor(mochilaVetor, totalItensVetor);
                else listarLista(mochilaLista);
                break;
            case 4:
                if (opcaoEstrutura == 1) buscarSequencialVetor(mochilaVetor, totalItensVetor);
                else buscarItemLista(mochilaLista);
                break;
            case 5:
                if (opcaoEstrutura == 1) ordenarVetor(mochilaVetor, totalItensVetor);
                break;
            case 6:
                if (opcaoEstrutura == 1) buscarBinariaVetor(mochilaVetor, totalItensVetor);
                break;
            case 0:
                if (opcaoEstrutura == 2) liberarLista(mochilaLista);
                printf("Programa encerrado!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}