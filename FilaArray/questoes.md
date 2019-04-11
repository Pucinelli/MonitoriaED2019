# Fila com Array

## Exercícios básicos (o mínimo necessário para a prova)

1. Faça uma fila de strings (char *)
2. Crie uma função para criar uma nova Fila `Fila *fila__new()`
3. Crie uma função para inserir uma nova string na Fila `void fila__push(Fila *this, char *string)`
4. Crie uma função para remover uma string da Fila `char *fila__unshift(Fila *this)`
5. Crie uma função para imprimir a Fila `void fila__print(Fila *this)`

## Exercícios extras (para quem sentir que precisa reforcar mais um pouco)

6. Crie uma função para limpar a Fila/remover todas strings da Fila `void fila__clear(Fila *this)`
7. Crie uma função para imprimir a Fila ao contrário `void fila__rprint(Fila *this)`
8. Crie uma função para imprimir a Fila, separando cada string por uma string passada para a função `void fila__join(Fila *this, char *separador)`
9. Crie uma função que retorna a quantidade de strings em uma Fila `int fila__length(Fila *this)`
10. Crie uma função que ordena as strings de uma Fila em ordem alfabética `void fila__sort(Fila *this)`