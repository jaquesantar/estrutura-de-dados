#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MISSOES 5
#define TAM_MISSAO 100

// Estrutura para território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Estrutura para jogador
struct Jogador {
    char cor[10];
    char* missao;
};

// Vetor global de missões
const char* MISSOES[MAX_MISSOES] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas vermelhas",
    "Conquistar 5 territorios quaisquer",
    "Ter o maior exercito do jogo",
    "Dominar todos os territorios de uma cor"
};

// Função para limpar buffer
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar territórios
struct Territorio* cadastrarTerritorios(int* num_territorios) {
    printf("Digite o numero de territorios: ");
    scanf("%d", num_territorios);
    limparBufferEntrada();

    struct Territorio* territorios = (struct Territorio*)calloc(*num_territorios, sizeof(struct Territorio));
    if (territorios == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return NULL;
    }

    for (int i = 0; i < *num_territorios; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor inicial: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();
    }

    return territorios;
}

// Função para exibir territórios
void exibirTerritorios(struct Territorio* territorios, int num_territorios) {
    printf("\n=== TERRITORIOS ATUAIS ===\n");
    for (int i = 0; i < num_territorios; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }
}

// Função para atribuir missão
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Função para simular ataque
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;
    
    printf("\nDado do atacante: %d\n", dado_atacante);
    printf("Dado do defensor: %d\n", dado_defensor);

    if (dado_atacante > dado_defensor) {
        printf("Ataque bem sucedido!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = defensor->tropas / 2;
    } else {
        printf("Ataque falhou!\n");
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }
}

// Função para verificar cumprimento da missão
int verificarMissao(const char* missao, struct Territorio* mapa, int tamanho, const char* corJogador) {
    if (strstr(missao, "3 territorios seguidos") != NULL) {
        int territorios_seguidos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                territorios_seguidos++;
                if (territorios_seguidos >= 3) return 1;
            } else {
                territorios_seguidos = 0;
            }
        }
    } else if (strstr(missao, "5 territorios quaisquer") != NULL) {
        int territorios_conquistados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                territorios_conquistados++;
                if (territorios_conquistados >= 5) return 1;
            }
        }
    }
    return 0;
}

// Função para liberar memória
void liberarMemoria(struct Territorio* territorios, struct Jogador* jogadores, int num_jogadores) {
    if (territorios != NULL) {
        free(territorios);
    }
    if (jogadores != NULL) {
        for (int i = 0; i < num_jogadores; i++) {
            if (jogadores[i].missao != NULL) {
                free(jogadores[i].missao);
            }
        }
        free(jogadores);
    }
}

int main() {
    srand(time(NULL));
    int num_territorios;
    int num_jogadores;

    // Inicialização dos territórios
    struct Territorio* territorios = cadastrarTerritorios(&num_territorios);
    if (territorios == NULL) return 1;

    // Inicialização dos jogadores
    printf("Digite o numero de jogadores: ");
    scanf("%d", &num_jogadores);
    limparBufferEntrada();

    struct Jogador* jogadores = (struct Jogador*)malloc(num_jogadores * sizeof(struct Jogador));
    if (jogadores == NULL) {
        liberarMemoria(territorios, NULL, 0);
        return 1;
    }

    // Cadastro dos jogadores e atribuição de missões
    for (int i = 0; i < num_jogadores; i++) {
        printf("\nJogador %d, digite sua cor: ", i + 1);
        fgets(jogadores[i].cor, sizeof(jogadores[i].cor), stdin);
        jogadores[i].cor[strcspn(jogadores[i].cor, "\n")] = '\0';

        jogadores[i].missao = (char*)malloc(TAM_MISSAO * sizeof(char));
        if (jogadores[i].missao == NULL) {
            liberarMemoria(territorios, jogadores, i);
            return 1;
        }
        atribuirMissao(jogadores[i].missao, MISSOES, MAX_MISSOES);
        printf("Sua missao secreta: %s\n", jogadores[i].missao);
    }

    int jogador_atual = 0;
    int opcao;
    do {
        printf("\n=== MENU (Jogador %s) ===\n", jogadores[jogador_atual].cor);
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

            case 2: {
                exibirTerritorios(territorios, num_territorios);
                
                int terr_atacante, terr_defensor;
                printf("\nEscolha o territorio atacante (1-%d): ", num_territorios);
                scanf("%d", &terr_atacante);
                printf("Escolha o territorio defensor (1-%d): ", num_territorios);
                scanf("%d", &terr_defensor);
                limparBufferEntrada();

                terr_atacante--; // Ajusta índice para base 0
                terr_defensor--;

                if (terr_atacante >= 0 && terr_atacante < num_territorios &&
                    terr_defensor >= 0 && terr_defensor < num_territorios) {
                    if (strcmp(territorios[terr_atacante].cor, jogadores[jogador_atual].cor) != 0) {
                        printf("Voce so pode atacar com seus territorios!\n");
                    } else if (strcmp(territorios[terr_atacante].cor, territorios[terr_defensor].cor) == 0) {
                        printf("Nao pode atacar territorio da mesma cor!\n");
                    } else {
                        atacar(&territorios[terr_atacante], &territorios[terr_defensor]);
                        
                        if (verificarMissao(jogadores[jogador_atual].missao, 
                                         territorios, 
                                         num_territorios,
                                         jogadores[jogador_atual].cor)) {
                            printf("\nPARABENS! Jogador %s venceu!\n", jogadores[jogador_atual].cor);
                            printf("Missao cumprida: %s\n", jogadores[jogador_atual].missao);
                            opcao = 0;
                            break;
                        }
                        jogador_atual = (jogador_atual + 1) % num_jogadores;
                    }
                } else {
                    printf("Territorios invalidos!\n");
                }
                break;
            }

            case 0:
                printf("Encerrando o programa...\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    liberarMemoria(territorios, jogadores, num_jogadores);
    printf("Memoria liberada. Programa encerrado.\n");
    return 0;
}