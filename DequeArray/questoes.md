# Deque com Array

## Exercícios básicos (o mínimo necessário para a prova)

1. Faça um Deque de strings (char *)
2. Crie uma função para criar um novo Deque `Deque *deque__new()`
3. Crie uma função para inserir uma nova string no começo do Deque `void deque__shift(Deque *this, char *string)`
4. Crie uma função para inserir uma nova string no fim do Deque `void deque__push(Deque *this, char *string)`
5. Crie uma função para remover uma string do começo do Deque `char *deque__unshift(Deque *this)`
6. Crie uma função para remover uma string do fim do Deque `char *deque__pop(Deque *this)`
7. Crie uma função para imprimir o Deque do começo ao fim `void deque__print(Deque *this)`
8. Crie uma função para imprimir o Deque do fim ao começo `void deque__rprint(Deque *this)`

## Exercícios extras (para quem sentir que precisa reforcar mais um pouco)

9. Crie uma função para limpar o Deque/remover todas strings do Deque `void deque__clear(Deque *this)`
10. Crie uma função para imprimir o Dque, separando cada string por uma string passada para a função `void deque__join(Deque *this, char *separador)`
11. Crie uma função que retorna a quantidade de strings em um Deque `int deque__length(Deque *this)`
12. Crie uma função que ordena as strings de um Deque em ordem alfabética `void deque__sort(Deque *this)`