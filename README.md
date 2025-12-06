# Repositório – Árvores Binárias e AVL

Este repositório contém os códigos-fonte relacionados à implementação de duas estruturas clássicas de dados em C:

* **Árvore Binária de Busca (BST)**
* **Árvore AVL (árvore auto-balanceada)**

O objetivo deste repositório é fornecer uma base clara, modular e bem organizada para desenvolvimento, testes e evolução das estruturas.

---

## Estrutura do Repositório

```
src/
├── binaria.c   // Implementação da Árvore Binária de Busca
├── avl.c       // Implementação da Árvore AVL com rotações
└── padroes/    // Diretório contendo modelos, padrões e comentários úteis
```

---

## Conteúdo dos Arquivos

### `binaria.c`

Contém:

* Estrutura do nó da árvore binária (BST)
* Funções de inserção, busca e remoção
* Percursos: in-order, pre-order e post-order

### `avl.c`

Contém:

* Estrutura de nó AVL com altura
* Inserção e remoção com rebalanceamento
* Rotações simples e duplas

### `padroes/`

Contém:

* Modelos de comentários
* Padrões de organização
* Estrutura sugerida para arquivos e código
  Contém:
* Funções gerais de apoio (cálculo de altura, máximo, etc.)

---

## Objetivo do Projeto

Fornecer código limpo e modular para uso em estudos, testes e integrações futuras envolvendo estruturas de árvores.

---

## Como Compilar

Para compilar o projeto, execute cada linha abaixo separadamente:

````bash
gcc -c src/binaria.c -o binaria.o
gcc -c src/avl.c -o avl.o

gcc binaria.o avl.o -o arvores
```bash
gcc src/bst.c src/avl.c src/menu.c src/utils.c -o arvores
````

---

## Observação

A documentação teórica será adicionada separadamente em outro arquivo. Este README é focado **somente** na explicação dos arquivos presentes no repositório.
