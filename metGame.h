#ifndef METGAME_H
#define METGAME_H

#include <stdbool.h>

struct Usuario{
    char nome[50];
    char email[50];
    char senha[20];
};

struct Produto{
    int codigo;
    char nome[50];
    float preco;
};

bool validarEmail(const char *email);
void cadastrarUsuario(struct Usuario *usuarios, int *totalUsuarios);
void fazerLogin(struct Usuario *usuarios, int totalUsuarios, bool *logado);
void exibirTabelaDeProdutos(struct Produto *produtos, int totalProdutos);
void adicionarProduto(struct Produto *produtos, int *totalProdutos);
void removerProduto(struct Produto *produtos, int *totalProdutos);
void buscarProdutoPorCodigo(struct Produto *produtos, int totalProdutos);
void salvarProdutos(struct Produto *produtos, int totalProdutos);

#endif
