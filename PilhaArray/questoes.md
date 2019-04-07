# Pilha com Array

## Exercícios básicos (o mínimo necessário para a prova)

1. Faça uma pilha de strings (char *)
2. Crie uma função para criar uma nova pilha `Pilha *pilha__new()`
3. Crie uma função para inserir uma nova string na Pilha `void pilha__push(Pilha *this, char *string)`
4. Crie uma função para remover uma string da Pilha `char *pilha__pop(Pilha *this)`
5. Crie uma função para imprimir a Pilha `void pilha__print(Pilha *this)`

## Exercícios extras (para quem sentir que precisa reforcar mais um pouco)

6. Crie uma função para limpar a Pilha/remover todas strings da Pilha `void pilha__clear(Pilha *this)`
7. Crie uma função para imprimir a Pilha ao contrário `void pilha__rprint(Pilha *this)`
8. Crie uma função para imprimir a Pilha, separando cada string por uma string passada para a função `void pilha__join(Pilha *this, char *separador)`
9. Crie uma função que retorna a quantidade de strings em uma pilha `int pilha__length(Pilha *this)`
10. Crie uma função que ordena as strings de uma Pilha em ordem alfabética `void pilha__sort(Pilha *this)`