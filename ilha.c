#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

// Contadores globais para análise de desempenho
int comparacoes = 0;

// Estrutura do Componente
struct Componente {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
};

// Função auxiliar para limpar buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar componente
void cadastrarComponente(struct Componente componentes[], int* total) {
    if (*total >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido!\n");
        return;
    }

    printf("\n=== Cadastro de Componente ===\n");
    printf("Nome: ");
    fgets(componentes[*total].nome, TAM_NOME, stdin);
    componentes[*total].nome[strcspn(componentes[*total].nome, "\n")] = '\0';

    printf("Tipo (controle/suporte/propulsao): ");
    fgets(componentes[*total].tipo, TAM_TIPO, stdin);
    componentes[*total].tipo[strcspn(componentes[*total].tipo, "\n")] = '\0';

    do {
        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[*total].prioridade);
        limparBuffer();
    } while (componentes[*total].prioridade < 1 || componentes[*total].prioridade > 10);

    (*total)++;
    printf("Componente cadastrado com sucesso!\n");
}

// Bubble Sort por nome
void bubbleSortNome(struct Componente componentes[], int total) {
    comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                struct Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nBubble Sort (Nome) - Comparacoes: %d, Tempo: %.4f segundos\n", 
           comparacoes, tempo);
}

// Insertion Sort por tipo
void insertionSortTipo(struct Componente componentes[], int total) {
    comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < total; i++) {
        struct Componente key = componentes[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentes[j].tipo, key.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = key;
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nInsertion Sort (Tipo) - Comparacoes: %d, Tempo: %.4f segundos\n", 
           comparacoes, tempo);
}

// Selection Sort por prioridade
void selectionSortPrioridade(struct Componente componentes[], int total) {
    comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < total - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < total; j++) {
            comparacoes++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            struct Componente temp = componentes[i];
            componentes[i] = componentes[min_idx];
            componentes[min_idx] = temp;
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nSelection Sort (Prioridade) - Comparacoes: %d, Tempo: %.4f segundos\n", 
           comparacoes, tempo);
}

// Busca binária por nome
void buscaBinariaPorNome(struct Componente componentes[], int total) {
    char nome[TAM_NOME];
    printf("\nDigite o nome do componente-chave: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int inicio = 0, fim = total - 1;
    int comparacoesBusca = 0;
    clock_t inicioBusca = clock();

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBusca++;
        
        int comparacao = strcmp(componentes[meio].nome, nome);
        if (comparacao == 0) {
            clock_t fimBusca = clock();
            double tempo = (double)(fimBusca - inicioBusca) / CLOCKS_PER_SEC;
            printf("\nComponente-chave encontrado!\n");
            printf("Nome: %s\nTipo: %s\nPrioridade: %d\n",
                   componentes[meio].nome, componentes[meio].tipo, 
                   componentes[meio].prioridade);
            printf("Busca Binaria - Comparacoes: %d, Tempo: %.4f segundos\n",
                   comparacoesBusca, tempo);
            return;
        }
        if (comparacao > 0) fim = meio - 1;
        else inicio = meio + 1;
    }

    clock_t fimBusca = clock();
    double tempo = (double)(fimBusca - inicioBusca) / CLOCKS_PER_SEC;
    printf("\nComponente-chave nao encontrado!\n");
    printf("Busca Binaria - Comparacoes: %d, Tempo: %.4f segundos\n",
           comparacoesBusca, tempo);
}

// Exibir componentes
void mostrarComponentes(struct Componente componentes[], int total) {
    if (total == 0) {
        printf("\nNenhum componente cadastrado!\n");
        return;
    }

    printf("\n=== Componentes da Torre ===\n");
    for (int i = 0; i < total; i++) {
        printf("\nComponente %d:\n", i + 1);
        printf("Nome: %s\n", componentes[i].nome);
        printf("Tipo: %s\n", componentes[i].tipo);
        printf("Prioridade: %d\n", componentes[i].prioridade);
        printf("--------------------\n");
    }
}

int main() {
    struct Componente componentes[MAX_COMPONENTES];
    int totalComponentes = 0;
    int opcao;

    do {
        printf("\n=== MENU DA TORRE ===\n");
        printf("1. Cadastrar componente\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente-chave\n");
        printf("6. Mostrar todos componentes\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarComponente(componentes, &totalComponentes);
                break;
            case 2:
                bubbleSortNome(componentes, totalComponentes);
                mostrarComponentes(componentes, totalComponentes);
                break;
            case 3:
                insertionSortTipo(componentes, totalComponentes);
                mostrarComponentes(componentes, totalComponentes);
                break;
            case 4:
                selectionSortPrioridade(componentes, totalComponentes);
                mostrarComponentes(componentes, totalComponentes);
                break;
            case 5:
                buscaBinariaPorNome(componentes, totalComponentes);
                break;
            case 6:
                mostrarComponentes(componentes, totalComponentes);
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