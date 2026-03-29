# Árvores Binárias de Produtos

Este repositório contém implementação em C de duas árvores binárias com `Produto`:

- `NoID`: árvore de busca binária ordenada por `id`
- `NoPreco`: árvore de busca binária ordenada por `preco`

## O que está implementado

- Estrutura `Produto` (`id`, `nome`, `preco`) em `produto.h`.
- Função `criarProduto` para alocar e inicializar `Produto` em `produto.c`.
- Inserção de produto em ambas as árvores:
  - `inserirID` (por `id`)
  - `inserirPreco` (por `preco`)
  - `inserirProduto` combina ambas as inserções.
- Busca por `id` em `NoID`:
  - `buscarID`
- Busca por faixa de preço em `NoPreco`:
  - `buscarFaixa` (imprime produtos entre `min` e `max`).
- Busca por produto com preço mais próximo de um valor dado em `NoPreco`:
  - `buscarMaisProximo`.
- Funções de liberação de memória:
  - `liberarArvoreID`
  - `liberarArvorePreco`

## Fonte principal

- `main.c`: exemplo de uso com três produtos (`Mouse`, `Teclado`, `Pneu`), inserção em ambas as árvores, busca por id, busca por faixa de preço e busca por preço mais próximo.
- `produto.h` / `produto.c`: implementação das estruturas e lógica de árvore.

## Como compilar

O projeto já possui `CMakeLists.txt`. Exemplo de compilação manual:

```powershell
mkdir -p cmake-build-debug; cd cmake-build-debug
cmake ..
cmake --build .
```

## Como executar

- Executar o binário gerado a partir do build do CMake.

## Observações

- A implementação atual funciona com `float` para preços.
- Não há remoção de nós implementada ainda (apenas inserção e buscas).
- Há mensagens de erro para ID duplicado na árvore de ID.
