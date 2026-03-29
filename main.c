#include <stdio.h>
#include "produto.h"

int main() {
    NoID *raizID = NULL;
    NoPreco *raizPreco = NULL;

    Produto *p1 = criarProduto (50, "Mouse", 100);
    Produto *p2 = criarProduto (30, "Teclado", 300);
    Produto *p3 = criarProduto (10, "Pneu", 800);

    inserirProduto (&raizID, &raizPreco, p1);
    inserirProduto (&raizID, &raizPreco, p2);
    inserirProduto (&raizID, &raizPreco, p3);

    printf("Funcionando!\n");

    Produto *res = buscarID(raizID, 50);

    if (res != NULL) {
        printf("Encontrado: %s - %.2f\n", res->nome, res->preco);
    } else {
        printf("Produto nao encontrado\n");
    }

    printf("\nProdutos entre 100 e 500:\n");
    buscarFaixa(raizPreco, 100, 500);

    printf("\nMais proximo de 250:\n");

    Produto *prox = buscarMaisProximo(raizPreco, 250);

    if (prox != NULL) {
        printf("ID: %d | Nome: %s | Preco: %.2f\n",
               prox->id, prox->nome, prox->preco);
    }

    // Liberar memória alocada
    liberarArvoreID(raizID);
    liberarArvorePreco(raizPreco);

    free(p1);
    free(p2);
    free(p3);

    return 0;
}