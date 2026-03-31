#include <stdio.h>
#include <stdlib.h>
#include "produto.h"

int main() {
    NoID *raizID = NULL;
    NoPreco *raizPreco = NULL;

    int opcao, id;
    char nome[50];
    float preco, min, max;
    Produto *p;

    do {
        printf("\n======= SISTEMA DE PRODUTOS (ESTRUTURA DE ARVORES) =======\n");
        printf("1. Inserir Produto\n");
        printf("2. Buscar Produto por ID\n");
        printf("3. Buscar Produtos por Faixa de Preco\n");
        printf("4. Buscar Preco Mais Proximo\n");
        printf("5. Remover Produto\n");
        printf("6. Imprimir Arvores\n");
        printf("0. Sair\n");
        printf("=============================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\n Cadastro de Produto \n");
                printf("Digite o ID, Nome (sem espacos) e Preco: ");
                // Usando a leitura em uma linha como voce queria
                if (scanf("%d %s %f", &id, nome, &preco) == 3) {
                    p = criarProduto(id, nome, preco);
                    inserirProduto(&raizID, &raizPreco, p);
                    printf("Sucesso: Produto cadastrado!\n");
                } else {
                    printf("Erro: Formato de entrada invalido.\n");
                }
                break;

            case 2:
                printf("\n Busca por ID \n");
                printf("Digite o ID desejado: ");
                scanf("%d", &id);
                p = buscarID(raizID, id);
                if (p != NULL) {
                    printf("Encontrado: [ID: %d] Nome: %s | Preco: R$%.2f\n", p->id, p->nome, p->preco);
                } else {
                    printf("Aviso: Produto com ID %d nao encontrado.\n", id);
                }
                break;

            case 3:
                printf("\n Busca por Faixa de Preco \n");
                printf("Digite o preço MINÍMO e o MÁXIMO: ");
                scanf("%f %f", &min, &max);
                printf("Produtos na faixa de R$%.2f ate R$%.2f:\n", min, max);
                buscarFaixa(raizPreco, min, max);
                break;

            case 4:
                printf("\n Buscar Preco Mais Proximo \n");
                printf("Digite um valor de referencia: ");
                scanf("%f", &preco);
                p = buscarPrecoMaisProximo(raizPreco, preco);
                if (p != NULL) {
                    printf("O produto com preço mais proximo de R$%.2f e:\n", preco);
                    printf("-> %s (R$%.2f)\n", p->nome, p->preco);
                } else {
                    printf("Aviso: Não há produtos cadastrados.\n");
                }
                break;

            case 5:
                printf("\n--- Remover Produto ---\n");
                printf("Digite o ID do produto a ser removido: ");
                scanf("%d", &id);
                // A funcao removerProduto ja faz a busca e a remocao sincronizada
                removerProduto(&raizID, &raizPreco, id);
                break;
            
            case 6:
                printf("\n--- IMPRESSAO DAS ARVORES ---\n");

                printf("\nArvore por ID:\n");
                if (raizID == NULL) {
                    printf("Arvore vazia!\n");
                } else{
                    imprimirArvoreID(raizID);
                    printf("\nArvore por Preco:\n");
                }
                if (raizPreco == NULL){
                    printf("Arvore vazia!\n");
                } else{
                    imprimirArvorePreco(raizPreco);
                }

                break;

            case 0:
                printf("Encerrando o sistema... Até logo!\n");
                break;

            default:
                printf("Opçao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
