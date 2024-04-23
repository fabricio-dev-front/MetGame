#include <string.h>
#include "met.h"
#include <stdio.h>
#include <stdlib.h>

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

void adicionarProduto(struct ProdutoNode **head, int *totalProdutos){
    printf("\n=== ADICIONAR NOVO PRODUTO ===\n");
    struct ProdutoNode *newNode = (struct ProdutoNode*)malloc(sizeof(struct ProdutoNode));
    if(newNode == NULL){
        printf("Erro: Memoria insuficiente para adicionar o produto.\n");
        return;
    }

    printf("Codigo: ");
    scanf("%d", &newNode->data.codigo);
    printf("Nome: ");
    scanf(" %[^\n]", newNode->data.nome);
    printf("Preco: ");
    scanf("%f", &newNode->data.preco);

    newNode->next = *head;
    *head = newNode;

    printf("Produto adicionado com sucesso!\n");
    
    (*totalProdutos)++;
}

void removerProduto(struct ProdutoNode **head, int *totalProdutos){
    int codigo;

    printf("\n=== REMOVER PRODUTO ===\n");
    printf("Informe o codigo do produto que deseja remover: ");
    scanf("%d", &codigo);
    
    struct ProdutoNode *temp = *head;
    struct ProdutoNode *prev = NULL;
    while(temp != NULL){
        if(temp->data.codigo == codigo){
            if(prev == NULL){
                *head = temp->next;
            } else{
                prev->next = temp->next;
            }

            free(temp);
            printf("Produto removido com sucesso!\n");
            (*totalProdutos)--;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    
    printf("Produto nao encontrado!\n");
}

void buscarProdutoPorCodigo(struct ProdutoNode *head){
    int codigo;
    printf("\n=== BUSCAR PRODUTO POR CODIGO ===\n");
    printf("Informe o codigo do produto que deseja buscar: ");
    scanf("%d", &codigo);
    
    struct ProdutoNode *temp = head;
    while(temp != NULL){
        if(temp->data.codigo == codigo){
            printf("Codigo: %d\n", temp->data.codigo);
            printf("Nome: %s\n", temp->data.nome);
            printf("Preco: R$ %.2f\n", temp->data.preco);
            return;
        }
        temp = temp->next;
    }
    
    printf("Produto nao encontrado!\n");
}

void salvarProdutos(struct ProdutoNode *head){
    FILE *file = fopen("produtos.txt", "w");
    if(file == NULL){
        printf("Nao foi possível abrir o arquivo produtos.txt\n");
        return;
    }

    struct ProdutoNode *current = head;
    while(current != NULL){
        fprintf(file, "%d %s %f\n", current->data.codigo, current->data.nome, current->data.preco);
        current = current->next;
    }

    fclose(file);
}

struct ProdutoNode* carregarProdutos(){
    FILE *file = fopen("produtos.txt", "r");
    if(file == NULL){
        printf("Nao foi possível abrir o arquivo produtos.txt\n");
        return NULL;
    }

    struct ProdutoNode *head = NULL;
    struct ProdutoNode *current = NULL;

    while(true){
        struct ProdutoNode *node = malloc(sizeof(struct ProdutoNode));
        int result = fscanf(file, "%d %s %f\n", &node->data.codigo, node->data.nome, &node->data.preco);
        node->next = NULL;

        if(result < 3){
            free(node);
            break;
        }

        if(head == NULL){
            head = node;
            current = node;
        } else{
            current->next = node;
            current = node;
        }
    }

    fclose(file);
    return head;
}

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

typedef struct {
    int codigo;
    char nome[50];
    float preco;
} Produto;

int compararProdutos(const void *a, const void *b){
    return ((Produto *)a)->codigo - ((Produto *)b)->codigo;
}

void ordenarProdutos(){
    FILE *file = fopen("produtos.txt", "r");
    if(file == NULL){
        printf("Não foi possível abrir o arquivo produtos.txt\n");
        return;
    }

    Produto produtos[1000];
    int totalProdutos = 0;

    while(fscanf(file, "%d %s %f\n", &produtos[totalProdutos].codigo, produtos[totalProdutos].nome, &produtos[totalProdutos].preco) != EOF){
        totalProdutos++;
    }

    fclose(file);

    qsort(produtos, totalProdutos, sizeof(Produto), compararProdutos);

    file = fopen("produtos.txt", "w");
    if(file == NULL){
        printf("Não foi possível abrir o arquivo produtos.txt\n");
        return;
    }

    for(int i = 0; i < totalProdutos; i++){
        fprintf(file, "%d %s %f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }

    fclose(file);
}