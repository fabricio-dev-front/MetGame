#include "metgame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validarEmail(const char *email){
    int i;
    bool temArroba = false;
    int tamanho = strlen(email);
    
    for(i = 0; i < tamanho; i++){
        if(email[i] == '@'){
            temArroba = true;
            break;
        }
    }
    
    return temArroba;
}

void cadastrarUsuario(struct Usuario *usuarios, int *totalUsuarios){
    printf("=== CADASTRO ===\n");
    printf("Nome: ");
    scanf("%s", usuarios[*totalUsuarios].nome);
    
    do{
        printf("Email: ");
        scanf("%s", usuarios[*totalUsuarios].email);
        
        if(!validarEmail(usuarios[*totalUsuarios].email)){
            printf("Email invalido. Por favor, insira um email valido.\n");
        }
    } while(!validarEmail(usuarios[*totalUsuarios].email));
    
    int i;
    for(i = 0; i < *totalUsuarios; i++){
        if(strcmp(usuarios[*totalUsuarios].email, usuarios[i].email) == 0){
            printf("Este email ja esta cadastrado. Por favor, use outro email.\n");
            return; 
        }
    }
    
    printf("Senha: ");
    scanf("%s", usuarios[*totalUsuarios].senha);

    printf("Usuario cadastrado com sucesso!\n");
    
    (*totalUsuarios)++;
}

void fazerLogin(struct Usuario *usuarios, int totalUsuarios, bool *logado){
    char email[50];
    char senha[20];
    
    printf("=== LOGIN ===\n");
    printf("Email: ");
    scanf("%s", email);
    printf("Senha: ");
    scanf("%s", senha);
    
    int i;
    for(i = 0; i < totalUsuarios; i++){
        if(strcmp(email, usuarios[i].email) == 0 && strcmp(senha, usuarios[i].senha) == 0){
            printf("Login bem-sucedido!\nBem-vindo a MetGame, %s!\n", usuarios[i].nome);
            *logado = true;
            return;
        }
    }
    
    printf("Email ou senha incorretos. Tente novamente.\n");
}

void exibirTabelaDeProdutos(struct Produto *produtos, int totalProdutos){
    printf("Codigo | Produto             | Preco\n");
    printf("------------------------------------\n");
    for(int i = 0; i < totalProdutos; i++){
        printf("%06d | %-20s | R$ %.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }
}

void adicionarProduto(struct Produto *produtos, int *totalProdutos){
    printf("\n=== ADICIONAR NOVO PRODUTO ===\n");
    printf("Codigo: ");
    scanf("%d", &produtos[*totalProdutos].codigo);
    printf("Nome: ");
    scanf(" %[^\n]", produtos[*totalProdutos].nome);
    printf("Preco: ");
    scanf("%f", &produtos[*totalProdutos].preco);

    printf("Produto adicionado com sucesso!\n");
    
    (*totalProdutos)++;
}

void removerProduto(struct Produto *produtos, int *totalProdutos){
    int codigo;
    printf("\n=== REMOVER PRODUTO ===\n");
    printf("Informe o codigo do produto que deseja remover: ");
    scanf("%d", &codigo);
    
    int i, j;
    bool encontrado = false;
    for (i = 0; i < *totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            encontrado = true;

            for (j = i; j < *totalProdutos - 1; j++){
                produtos[j] = produtos[j + 1];
            }
            (*totalProdutos)--;
            printf("Produto removido com sucesso!\n");
            break;
        }
    }
    if(!encontrado){
        printf("Produto não encontrado!\n");
    }
}

void buscarProdutoPorCodigo(struct Produto *produtos, int totalProdutos){
    int codigo;
    printf("\n=== BUSCAR PRODUTO POR CÓDIGO ===\n");
    printf("Informe o codigo do produto que deseja buscar: ");
    scanf("%d", &codigo);
    
    int i;
    bool encontrado = false;
    for(i = 0; i < totalProdutos; i++){
        if(produtos[i].codigo == codigo){
            encontrado = true;
            printf("Codigo: %d\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preco: R$ %.2f\n", produtos[i].preco);
            break;
        }
    }
    if(!encontrado){
        printf("Produto nao encontrado!\n");
    }
}

void salvarProdutos(struct Produto *produtos, int totalProdutos){
    FILE *arquivo;
    arquivo = fopen("produtos.txt", "w"); 
    
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    int i;
    for(i = 0; i < totalProdutos; i++){
        fprintf(arquivo, "%d %s %.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }
    
    fclose(arquivo); 
    printf("Produtos salvos com sucesso!\n");
}
