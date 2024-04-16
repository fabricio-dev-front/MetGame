#include <stdio.h>
#include <stdlib.h>
#include "metgame.h"

int main(){
    struct Usuario usuarios[50]; 
    int totalUsuarios = 0; 
    struct Produto produtos[50]; 
    int totalProdutos = 6;
    
    produtos[0] = (struct Produto){1001, "The Witcher 3", 59.99};
    produtos[1] = (struct Produto){1002, "Red Dead Redemption 2", 79.99};
    produtos[2] = (struct Produto){1003, "Cyberpunk 2077", 69.99};
    produtos[3] = (struct Produto){1004, "GTA V", 89.99};
    produtos[4] = (struct Produto){1005, "Assassin's Creed Valhalla", 99.99};
    produtos[5] = (struct Produto){1006, "FIFA 22", 79.99};
    
    int opcao;
    bool logado = false;

    while(true){
        if(!logado){
            printf("\n=== MENU ===\n");
            printf("1. Cadastrar\n");
            printf("2. Logar\n");
            printf("0. Sair\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch(opcao){
                case 1:
                    cadastrarUsuario(usuarios, &totalUsuarios);
                    break;
                case 2:
                    fazerLogin(usuarios, totalUsuarios, &logado);
                    break;
                case 0:
                    printf("Saindo...\n");
                    salvarProdutos(produtos, totalProdutos);
                    exit(0);
                default:
                    printf("Opcao invalida. Tente novamente.\n");
            }
        } else{
            printf("\n=== MENU DE PRODUTOS ===\n");
            printf("1. Visualizar Lista de Produtos\n");
            printf("2. Adicionar Produto\n");
            printf("3. Remover Produto\n");
            printf("4. Buscar Produto por Codigo\n");
            printf("0. Sair\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch(opcao){
                case 1:
                    exibirTabelaDeProdutos(produtos, totalProdutos);
                    break;
                case 2:
                    adicionarProduto(produtos, &totalProdutos);
                    break;
                case 3:
                    removerProduto(produtos, &totalProdutos);
                    break;
                case 4:
                    buscarProdutoPorCodigo(produtos, totalProdutos);
                    break;
                case 0:
                    printf("Saindo...\n");
                    salvarProdutos(produtos, totalProdutos);
                    exit(0);
                default:
                    printf("Opcao invalida. Tente novamente.\n");
            }
        }
    }

    return 0;
}
