#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 50
#define MAX_EMPRESTIMO 100
#define TAM_STRING 100

struct Livro
{
   char nome [TAM_STRING];
   char autor [TAM_STRING];
   char editora [TAM_STRING];
   int edicao;
   int disponivel;
};


struct Emprestimo
{
    int indiceLivro;
    char nomeUsuario [TAM_STRING];  
};


void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}

int main (){
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;


    biblioteca = (struct Livro *) calloc (MAX_LIVROS, sizeof(struct Livro));

    emprestimos = (struct Emprestimo *) malloc (MAX_EMPRESTIMO * sizeof(struct Emprestimo));
    
    if (biblioteca == NULL || emprestimos == NULL)
    {
       printf("Erro de alocacao de memoria!\n");
       return 1;    
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;
    

    do
    {
        printf("=========================\n");
        printf(" BIBLIOTECA - PARTE 1\n");
        printf("========================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros \n");
        printf("3 - Cadastrar emprestimo de livro\n");
        printf("4 - Listar todos os emprestimos\n");
        printf("0 - Sair\n");
        printf ("---------------------------\n");
        printf ("Escolhe uma opcao: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
        case 1:
            printf ("--- Cadastro de Novo Livro --- \n\n");
            
            if(totalLivros < MAX_LIVROS){
                printf("Digite o nome do livro: ");
                fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                printf("Digite o autor: ");
                fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                printf("Digite a editora: ");
                fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] =
                biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor,"\n")] =
                biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora,"\n")] =

                printf("Digite a edicao: ");
                scanf("%d", &biblioteca[totalLivros].edicao);
                limparBufferEntrada();

                totalLivros++;

                printf("\nLivro cadastrado com sucesso\n");
            } else
            {
                printf("Biblioteca cheia! Nao e possivel cadastrar mais livros.\n");
            }
            
        
        case 2: 
                printf("---Lista de livros Cadastrados ----\n\n");

                if(totalLivros == 0){
                    printf("Nenhum livros cadastrado ainda.\n");
                }else{
                    for(int i = 0; i < totalLivros; i++){
                        printf("--------------------\n");
                        printf("Livro %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("edicao: %d\n", biblioteca[i].edicao);
                    }
                    printf("--------------------------\n");
                }
                        printf("\nPressione Enter para continuar...");
                        getchar();
                        break;
        case 3:
                printf("--- Cadastro de Emprestimo de Livro ---\n\n");  
                
                if (totalEmprestimos >= MAX_EMPRESTIMO){
                    printf("Limite de emprestimos atingido! Nao e possivel cadastrar mais emprestimos.\n");
                } else {
                    printf("Lista de livros disponiveis para emprestimo:\n");
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++){
                        if (biblioteca[i].disponivel){
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0){
                        printf("Nenhum livro disponivel para emprestimo.\n");
                        break;
                    } else {
                        printf("\nDigite o numero do livro que deseja empresetar:\n");
                        int numLivro;
                        scanf("%d", &numLivro);
                        limparBufferEntrada();  

                        int indice = numLivro - 1;

                        if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel){
                            printf("Digite o nome do usuario que esta pegando o livro: ");
                            fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0';
                           
                            emprestimos[totalEmprestimos].indiceLivro = indice;

                            biblioteca[indice].disponivel = 0; // marcar como indisponivel

                            totalEmprestimos++;


                            printf("\nEmprestimo cadastrado com sucesso!\n");
                        } else {
                            printf("Opcao invalida ou livro indisponivel para emprestimo.\n");
                        }
                    }


                    printf("\nPressione Enter para continuar...");
                    getchar();  
                    break;

        case 4:
                printf("--- Lista de Emprestimos Cadastrados ---\n\n");    

                if (totalEmprestimos == 0){
                    printf("Nenhum emprestimo cadastrado ainda.\n");
                } else {
                    for (int i = 0; i < totalEmprestimos; i++){
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("--------------------\n");
                        printf("Emprestimo %d\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                    }
                    printf("--------------------------\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();  
                break;


        case 0:
                printf("Saindo do programa...\n");  
                break;
        default:
                printf("Opcao invalida!\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }
    }
 } while (opcao != 0);

    free(biblioteca);   
    free(emprestimos);

    printf("Memoria liberada. Programa encerrado.\n");

    return 0;

}