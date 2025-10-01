#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// definindo a struct //
struct Territorio
{
    char nome [30];
    char cor [10];
    int tropas;
};

void limparBufferEntrada(){
    int C;
    while ((C = getchar()) != '\n' && C != EOF);
}

// definindo um array de structs para armazenar 5 territorios//
int main(){
    struct Territorio territorios[5];
    int i;

    printf("----Cadastro de territorios---\n");
    for ( i = 0; i < 5; i++){
        printf("\nTerritorio %d:\n", i+1);

        
        printf("Digite Nome da tropa: ");
                fgets(territorios[i].nome,sizeof(territorios[i].nome),stdin);

        territorios[i].nome[strcspn(territorios[i].nome,"\n")] ='\0';

                printf("Digite cor da tropa: ");
                fgets(territorios[i].cor,sizeof(territorios[i].cor),stdin);

        territorios[i].cor[strcspn(territorios[i].cor,"\n")] ='\0';

                printf ("Quantidade de tropas: ");
                scanf("%d", &territorios[i].tropas);

                limparBufferEntrada();     
    
    }

    printf("\n --- Informacoes dos Territorios Cadastrados---\n");
    for (i = 0; i < 5; i++){
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor da tropa: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    printf("\nPressione Enter para sair...");
    getchar();


    return 0;
    
}