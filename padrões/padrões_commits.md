# Padrões de Commit

Este documento define um padrão simples e organizado para escrita de mensagens de commit no repositório.

---

## Formato Geral

```
<tipo>: <descrição curta>

<descrição detalhada opcional>
```

A descrição curta deve ser direta e no imperativo.

---

## Tipos de Commit

### `feat:`

Indica adição de funcionalidade.

```
feat: implementar inserção na árvore AVL
```

### `fix:`

Correção de erro.

```
fix: corrigir cálculo de altura na AVL
```

### `refactor:`

Mudança no código que não altera comportamento.

```
refactor: reorganizar funções de impressão
```

### `docs:`

Alterações em documentação.

```
docs: atualizar README com estrutura do projeto
```

### `style:`

Mudanças que não afetam lógica (espaços, formatação, nomes).

```
style: ajustar indentação do arquivo binaria.c
```

### `test:`

Criação ou ajuste de testes.

```
test: adicionar casos de teste para inserção em AVL
```

### `chore:`

Tarefas gerais que não alteram código de produção.

```
chore: mover arquivos para diretório padroes
```

---

## Boas Práticas

* Mensagem curta com no máximo 70 caracteres.
* Descrição detalhada opcional em parágrafo abaixo.
* Commits pequenos e específicos.
* Usar apenas um tipo por commit.

---

## Exemplos

```
feat: adicionar remoção na árvore binária
```

```
fix: corrigir rotação esquerda na AVL

Erro ocorria quando o nó direito era nulo.
```

```
docs: criar documentação dos padrões de commit
```
