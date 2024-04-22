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

void cadastrarUsuario(struct UsuarioNode **head, int *totalUsuarios){
    printf("=== CADASTRO ===\n");
    struct UsuarioNode *newNode = (struct UsuarioNode*)malloc(sizeof(struct UsuarioNode));
    if (newNode == NULL) {
        printf("Erro: Memoria insuficiente para cadastrar o usuario.\n");
        return;
    }
    
    printf("Nome: ");
    scanf("%s", newNode->data.nome);
    
    do{
        printf("Email: ");
        scanf("%s", newNode->data.email);
        if(!validarEmail(newNode->data.email)){
            printf("Email invalido. Por favor, insira um email valido.\n");
        }
    } while(!validarEmail(newNode->data.email));

    struct UsuarioNode *temp = *head;
    while(temp != NULL){
        if(strcmp(newNode->data.email, temp->data.email) == 0){
            printf("Este email ja esta cadastrado. Por favor, use outro email.\n");
            free(newNode);
            return;
        }
        temp = temp->next;
    }

    printf("Senha: ");
    scanf("%s", newNode->data.senha);

    newNode->next = *head;
    *head = newNode;

    printf("Usuario cadastrado com sucesso!\n");
    
    (*totalUsuarios)++;
}

void fazerLogin(struct UsuarioNode *head, bool *logado){
    char email[50];
    char senha[20];
    
    printf("=== LOGIN ===\n");
    printf("Email: ");
    scanf("%s", email);
    printf("Senha: ");
    scanf("%s", senha);
    
    struct UsuarioNode *temp = head;
    while(temp != NULL){
        if(strcmp(email, temp->data.email) == 0 && strcmp(senha, temp->data.senha) == 0){
            printf("Login bem-sucedido!\nBem-vindo a MetGame, %s!\n", temp->data.nome);
            *logado = true;
            return;
        }
        temp = temp->next;
    }
    
    printf("Email ou senha incorretos. Tente novamente.\n");
}

void exibirTabelaDeProdutos(struct ProdutoNode *head){
    printf("Codigo | Produto             | Preco\n");
    printf("------------------------------------\n");
    struct ProdutoNode *temp = head;
    while(temp != NULL){
        printf("%06d | %-20s | R$ %.2f\n", temp->data.codigo, temp->data.nome, temp->data.preco);
        temp = temp->next;
    }
}

// parei aqui. proxima funcao adicionarProduto.

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
