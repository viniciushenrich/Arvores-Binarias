#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "produto.h"

int altura(NoID *n) {
    if (n == NULL) return 0;
    return n->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(NoID *n) {
    if (n == NULL) return 0;
    return altura(n->esq) - altura(n->dir);
}

NoID* rotacaoDireita(NoID *y) {
    NoID *x = y->esq;
    NoID *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

NoID* rotacaoEsquerda(NoID *x) {
    NoID *y = x->dir;
    NoID *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

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
        novo->altura = 1;
        return novo;
    }

    if (p->id < raiz->produto->id)
        raiz->esq = inserirID(raiz->esq, p);
    else if (p->id > raiz->produto->id)
        raiz->dir = inserirID(raiz->dir, p);
    else {
        printf("ID duplicado!\n");
        return raiz;
    }

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int fb = fatorBalanceamento(raiz);

    // Rotação simples direita
    if (fb > 1 && p->id < raiz->esq->produto->id)
        return rotacaoDireita(raiz);

    // Rotação simples esquerda
    if (fb < -1 && p->id > raiz->dir->produto->id)
        return rotacaoEsquerda(raiz);

    // Rotação dupla esquerda-direita
    if (fb > 1 && p->id > raiz->esq->produto->id) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // Rotação dupla direita-esquerda
    if (fb < -1 && p->id < raiz->dir->produto->id) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
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

            return raiz->produto;
        }
    }

    return maisProx;


}

NoID* menorNoID(NoID* atual) {
    NoID* temp = atual;
    while (temp != NULL && temp->esq != NULL) {
        temp = temp->esq;
    }
    return temp;
}

NoID* removerID(NoID *raiz, int id) {
    if (raiz == NULL) return raiz;

    // PASSO 1: Remoção normal BST
    if (id < raiz->produto->id) {
        raiz->esq = removerID(raiz->esq, id);
    } 
    else if (id > raiz->produto->id) {
        raiz->dir = removerID(raiz->dir, id);
    } 
    else {
        // Nó com 1 ou nenhum filho
        if (raiz->esq == NULL || raiz->dir == NULL) {
            NoID *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }

            free(temp);
        } 
        else {
            // Nó com 2 filhos
            NoID *temp = menorNoID(raiz->dir);

            raiz->produto = temp->produto;

            raiz->dir = removerID(raiz->dir, temp->produto->id);
        }
    }

    if (raiz == NULL) return raiz;

    // PASSO 2: Atualiza altura
    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    // PASSO 3: Verifica balanceamento
    int fb = fatorBalanceamento(raiz);

    // 🔁 Casos de rotação

    // Esquerda-Esquerda
    if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);

    // Esquerda-Direita
    if (fb > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // Direita-Direita
    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);

    // Direita-Esquerda
    if (fb < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

NoPreco* menorNoPreco(NoPreco* atual) {
    NoPreco* temp = atual;

    while (temp != NULL && temp->esq != NULL) {
        temp = temp->esq;
    }
    return temp;
}

NoPreco* removerPreco(NoPreco *raiz, float preco, int id) {
    if (raiz == NULL) return raiz;

    if (preco < raiz->produto->preco) {
        raiz->esq = removerPreco(raiz->esq, preco, id);
    }
    else if (preco > raiz->produto->preco) {
        raiz->dir = removerPreco(raiz->dir, preco, id);
    }

    else {
        if (raiz->produto->id != id) {
            raiz->dir = removerPreco(raiz->dir, preco, id);
            return raiz;
        }

        if (raiz->esq == NULL) {
            NoPreco *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            NoPreco *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        NoPreco *temp = menorNoPreco(raiz->dir);

        raiz->produto = temp->produto;

        raiz->dir = removerPreco(raiz->dir, temp->produto->preco, temp->produto->id);
    }

    return raiz;
}

//Sincroniza as duas remoções
void removerProduto(NoID **raizID, NoPreco **raizPreco, int id) {
    Produto *p = buscarID(*raizID, id);

    if (p == NULL) {
        printf("Erro: Produto com ID %d nao encontrado.\n", id);
        return;
    }

    float precoRemover = p->preco;

    *raizID = removerID(*raizID, id);

    *raizPreco = removerPreco(*raizPreco, precoRemover, id);

    printf("Produto ID %d removido com sucesso das duas arvores!\n", id);
}

void imprimirArvoreID(NoID *raiz) {
    if (raiz != NULL) {
        printf("(ID:%d | Nome:%s | Preco:%.2f | ",
               raiz->produto->id,
               raiz->produto->nome,
               raiz->produto->preco);

        if (raiz->esq != NULL)
            printf("esq:%d | ", raiz->esq->produto->id);
        else
            printf("esq:NULL | ");

        if (raiz->dir != NULL)
            printf("dir:%d)\n", raiz->dir->produto->id);
        else
            printf("dir:NULL)\n");

        imprimirArvoreID(raiz->esq);
        imprimirArvoreID(raiz->dir);
    }
}

void imprimirArvorePreco(NoPreco *raiz) {
    if (raiz != NULL) {
        printf("(Preco:%.2f | Nome:%s | ID:%d | ",
               raiz->produto->preco,
               raiz->produto->nome,
               raiz->produto->id);

        if (raiz->esq != NULL)
            printf("esq:%.2f | ", raiz->esq->produto->preco);
        else
            printf("esq:NULL | ");

        if (raiz->dir != NULL)
            printf("dir:%.2f)\n", raiz->dir->produto->preco);
        else
            printf("dir:NULL)\n");

        imprimirArvorePreco(raiz->esq);
        imprimirArvorePreco(raiz->dir);
    }
}