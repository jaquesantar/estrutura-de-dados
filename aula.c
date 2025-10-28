#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAX_STR_LEN 50


#define TAM_MAX 10


typedef struct {
    char dados[TAM_MAX][MAX_STR_LEN];
    int quantidade;
} ListaEstatica;

void inicializarListaestatica(ListaEstatica *lista);

void inserirListaEstatica(ListaEstatica *lista, const char *texto);
void removerListaEstatica(ListaEstatica *lista, const char *texto);
void listarListaEstatica(const ListaEstatica *lista);


typedef struct No {
    char* dado;
    struct No* proximo;
} No;


typedef No* ListaEncadeada;


void inicializarListaEncadeada(ListaEncadeada *lista);

void inserirListaEncadeada(ListaEncadeada *lista, const char *texto);
void removerListaEncadeada(ListaEncadeada *lista, const char *texto);
void listarListaEncadeada(const ListaEncadeada lista); 
void liberarListaEncadeada(ListaEncadeada *lista);


void menuListaEstatica();
void menuListaEncadeada();


int main() {
    int escolha;
    do {
        printf("Escolha o tipo de lista:\n");
        printf("1. Lista Estatica\n");
        printf("2. Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &escolha);
        getchar(); 

        switch (escolha) {
            case 1:
                menuListaEstatica();
                break;
            case 2:
                menuListaEncadeada();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}


void inicializarListaestatica(ListaEstatica *lista) {
    lista->quantidade = 0;
}


void inserirListaEstatica(ListaEstatica *lista, const char *texto) {
    if (lista->quantidade < TAM_MAX) {
        strncpy(lista->dados[lista->quantidade], texto, MAX_STR_LEN - 1);
        lista->dados[lista->quantidade][MAX_STR_LEN - 1] = '\0'; 
        lista->quantidade++;
        printf("Elemento inserido com sucesso!\n");
    } else {
        printf("Lista cheia! Nao e possivel inserir mais elementos.\n");
    }
}

void removerListaEstatica(ListaEstatica *lista, const char *texto) {
    int encontrado = 0;
    for (int i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i], texto) == 0) {
            encontrado = 1;
            for (int j = i; j < lista->quantidade - 1; j++) {
                strcpy(lista->dados[j], lista->dados[j + 1]);
            }
            lista->quantidade--;
            printf("Elemento removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Elemento nao encontrado na lista.\n");
    }
}

void listarListaEstatica(const ListaEstatica *lista) {
    if (lista->quantidade == 0) {
        printf("A lista esta vazia.\n");
    } else {
        printf("Elementos na lista:\n");
        for (int i = 0; i < lista->quantidade; i++) {
            printf("%d. %s\n", i + 1, lista->dados[i]);
        }
    }
}


void inicializarListaEncadeada(ListaEncadeada *lista) {
    *lista = NULL;
}

void inserirListaEncadeada(ListaEncadeada *lista, const char *texto) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    novoNo->dado = (char*)malloc(strlen(texto) + 1);
    if (!novoNo->dado) {
        printf("Erro ao alocar memoria!\n");
        free(novoNo);
        return;
    }
    strcpy(novoNo->dado, texto);
    novoNo->proximo = *lista;
    *lista = novoNo;
    printf("Elemento inserido com sucesso!\n");
}

void removerListaEncadeada(ListaEncadeada *lista, const char *texto) {
    No *atual = *lista;
    No *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dado, texto) == 0) {
            if (anterior == NULL) {
                *lista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual->dado);
            free(atual);
            printf("Elemento removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Elemento nao encontrado na lista.\n");
}


void listarListaEncadeada(const ListaEncadeada lista) {
    if (lista == NULL) {
        printf("A lista esta vazia.\n");
    } else {
        printf("Elementos na lista:\n");
        No* atual = lista;
        int indice = 1;
        while (atual != NULL) {
            printf("%d. %s\n", indice, atual->dado);
            atual = atual->proximo;
            indice++;
        }
    }
}


void liberarListaEncadeada(ListaEncadeada *lista) {
    No* atual = *lista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp->dado);
        free(temp);
    }
    *lista = NULL;
}
