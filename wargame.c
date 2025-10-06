#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definindo a struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar territórios com alocação dinâmica
struct Territorio* cadastrarTerritorios(int* num_territorios) {
    printf("Digite o numero de territorios a serem cadastrados: ");
    scanf("%d", num_territorios);
    limparBufferEntrada();

    struct Territorio* territorios = (struct Territorio*)calloc(*num_territorios, sizeof(struct Territorio));
    
    if (territorios == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return NULL;
    }

    for (int i = 0; i < *num_territorios; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        
        printf("Digite Nome do territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite cor da tropa: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();
    }

    return territorios;
}

// Função para exibir os territórios
void exibirTerritorios(struct Territorio* territorios, int num_territorios) {
    printf("\n--- Informacoes dos Territorios ---\n");
    for (int i = 0; i < num_territorios; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor da tropa: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }
}

// Função para simular ataque
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;
    
    printf("\nDado do atacante: %d\n", dado_atacante);
    printf("Dado do defensor: %d\n", dado_defensor);

    if (dado_atacante > dado_defensor) {
        printf("\nAtaque bem sucedido!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = defensor->tropas / 2;
    } else {
        printf("\nAtaque falhou!\n");
        atacante->tropas--;
    }
}

int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios
    int num_territorios;
    struct Territorio* territorios = cadastrarTerritorios(&num_territorios);

    if (territorios == NULL) {
        return 1;
    }

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                exibirTerritorios(territorios, num_territorios);
                break;
            case 2:
                int atacante_idx, defensor_idx;
                exibirTerritorios(territorios, num_territorios);
                
                printf("\nEscolha o territorio atacante (1-%d): ", num_territorios);
                scanf("%d", &atacante_idx);
                printf("Escolha o territorio defensor (1-%d): ", num_territorios);
                scanf("%d", &defensor_idx);
                limparBufferEntrada();

                atacante_idx--; defensor_idx--;

                if (atacante_idx >= 0 && atacante_idx < num_territorios &&
                    defensor_idx >= 0 && defensor_idx < num_territorios) {
                    if (strcmp(territorios[atacante_idx].cor, territorios[defensor_idx].cor) == 0) {
                        printf("Nao e possivel atacar um territorio da mesma cor!\n");
                    } else {
                        atacar(&territorios[atacante_idx], &territorios[defensor_idx]);
                    }
                } else {
                    printf("Indices invalidos!\n");
                }
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    free(territorios);
    return 0;
}