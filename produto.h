#ifndef ARVORESBINARIAS_PRODUTO_H
#define ARVORESBINARIAS_PRODUTO_H

typedef struct {
    int id;
    char nome[50];
    float preco;
} Produto;

typedef struct NoID {
    Produto *produto;
    struct NoID *esq;
    struct NoID *dir;
    int altura;
} NoID;

typedef struct NoPreco {
    Produto *produto;
    struct NoPreco *esq;
    struct NoPreco *dir;
    int altura;
} NoPreco;

// --- Funções Auxiliares Gerais ---
int max(int a, int b);
Produto* criarProduto(int id, char nome[], float preco);

// --- Funções Auxiliares de Balanceamento: Árvore ID ---
int altura(NoID *n);
int fatorBalanceamento(NoID *n);
NoID* rotacaoDireita(NoID *y);
NoID* rotacaoEsquerda(NoID *x);

// --- Funções Auxiliares de Balanceamento: Árvore Preço ---
int alturaPreco(NoPreco *n);
int fatorBalanceamentoPreco(NoPreco *n);
NoPreco* rotacaoDireitaPreco(NoPreco *y);
NoPreco* rotacaoEsquerdaPreco(NoPreco *x);

// --- Operações: Árvore ID ---
NoID* inserirID(NoID *raiz, Produto *p);
NoID* removerID(NoID *raiz, int id);
NoID* menorNoID(NoID* atual);
Produto* buscarID(NoID *raiz, int id);
void imprimirArvoreID(NoID *raiz);

// --- Operações: Árvore Preço ---
NoPreco* inserirPreco(NoPreco *raiz, Produto *p);
NoPreco* removerPreco(NoPreco *raiz, float preco, int id);
NoPreco* menorNoPreco(NoPreco* atual);
Produto* buscarPrecoMaisProximo(NoPreco *raiz, float valor);
void buscarFaixa(NoPreco *raiz, float min, float max);
void imprimirArvorePreco(NoPreco *raiz);

// --- Operações Sincronizadas (Ambas as Árvores) ---
void inserirProduto(NoID **raizID, NoPreco **raizPreco, Produto *p);
void removerProduto(NoID **raizID, NoPreco **raizPreco, int id);

#endif