#ifndef ARVORESBINARIAS_PRODUTO_H
#define ARVORESBINARIAS_PRODUTO_H

typedef struct {
    int id;
    char nome[50];
    float preco;
}Produto;

typedef struct NoID {
    Produto *produto;
    struct NoID *esq;
    struct NoID *dir;
}NoID;

typedef struct NoPreco {
    Produto *produto;
    struct NoPreco *esq;
    struct NoPreco *dir;
}NoPreco;


// Funções
Produto* criarProduto (int id, char nome[], float preco);
Produto* buscarID(NoID *raiz, int id);
Produto* buscarMaisProximo(NoPreco *raiz, float valor);

NoID* inserirID (NoID *raiz, Produto *p);
NoPreco* inserirPreco (NoPreco *raiz, Produto *p);

void inserirProduto (NoID **raizID, NoPreco **raizPreco, Produto *p);
void buscarFaixa(NoPreco *raiz, float min, float max);
void liberarArvoreID(NoID *raiz);
void liberarArvorePreco(NoPreco *raiz);

#endif