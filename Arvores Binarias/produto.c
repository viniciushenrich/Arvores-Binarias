#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "produto.h"

Produto* criarProduto(int id, char nome[], float preco) {
    Produto *p = (Produto*) malloc(sizeof(Produto));

    if (p == NULL) {
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    p->id = id;
    strcpy(p->nome, nome);
    p->preco = preco;

    return p;
}

NoID* inserirID(NoID *raiz, Produto *p) {
    if (raiz == NULL) {
        NoID *novo = (NoID*) malloc(sizeof(NoID));
        novo->produto = p;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (p->id == raiz->produto->id) {
        printf("ID duplicado!\n");
        return raiz;
    }

    if (p->id < raiz->produto->id) {
        raiz->esq = inserirID(raiz->esq, p);
    } else {
        raiz->dir = inserirID(raiz->dir, p);
    }

    return raiz;
}

NoPreco* inserirPreco(NoPreco *raiz, Produto *p) {
    if (raiz == NULL) {
        NoPreco *novo = (NoPreco*) malloc(sizeof(NoPreco));
        novo->produto = p;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (p->preco < raiz->produto->preco) {
        raiz->esq = inserirPreco(raiz->esq, p);
    } else {
        raiz->dir = inserirPreco(raiz->dir, p);
    }

    return raiz;
}

Produto* buscarID(NoID *raiz, int id) {
    if (raiz == NULL) return NULL;

    if (id == raiz->produto->id) {
        return raiz->produto;
    }

    if (id < raiz->produto->id) {
        return buscarID(raiz->esq, id);
    } else {
        return buscarID(raiz->dir, id);
    }
}

void inserirProduto(NoID **raizID, NoPreco **raizPreco, Produto *p) {
    *raizID = inserirID(*raizID, p);
    *raizPreco = inserirPreco(*raizPreco, p);
}

void buscarFaixa(NoPreco *raiz, float min, float max) {
    if (raiz == NULL) return;

    float preco = raiz->produto->preco;

    if (preco >= min && preco <= max) {
        printf("ID: %d | Nome: %s | Preco: %.2f\n",
               raiz->produto->id,
               raiz->produto->nome,
               raiz->produto->preco);
    }

    if (preco > min) {
        buscarFaixa(raiz->esq, min, max);
    }

    if (preco < max) {
        buscarFaixa(raiz->dir, min, max);
    }
}

Produto* buscarPrecoMaisProximo(NoPreco *raiz, float valor) {
    if (raiz == NULL) return NULL;

    Produto *maisProx = raiz->produto;
    float menorDif = fabs(raiz->produto->preco - valor);

    while (raiz != NULL) {
        float dif = fabs(raiz->produto->preco - valor);

        if (dif < menorDif) {
            menorDif = dif;
            maisProx = raiz->produto;
        }

        if (valor < raiz->produto->preco) {
            raiz = raiz->esq;
        } else if (valor > raiz->produto->preco) {
            raiz = raiz->dir;
        } else {
            // achou exatamente igual
            return raiz->produto;
        }
    }

    return maisProx;
}