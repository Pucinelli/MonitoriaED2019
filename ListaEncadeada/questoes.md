# Lista Encadeada

## Exercícios básicos (o mínimo necessário para a prova)

1. Faça uma lista encadeada de strings (char *)
2. Crie uma função para criar um novo nó de Lista Encadeada `Lista *lista__new(char *string, Lista *prox)`
3. Crie uma função para inserir um novo nó em qualquer posição da Lista `Lista *lista__insert(Lista **this, char *string)`
4. Crie uma função para remover um nó da Lista em qualquer posição `char *lista__remove_at(Lista **this, int posicao)`
5. Crie uma função para imprimir a Lista `void lista__print(Lista *this)`

## Exercícios extras (para quem sentir que precisa reforcar mais um pouco)

6. Crie uma função para inserir no começo de uma Lista `Lista *lista__shift(Lista **this, char *string)`
7. Crie uma função para inserir no final de uma Lista `Lista *lista__push(Lista *this, char *string)`
8. Crie uma função para remover no começo de uma Lista `char *lista__unshift(Lista **this)`
9. Crie uma função para remover no final de uma Lista `char *lista__pop(Lista **this)`
10. Crie uma função para remover uma determinada string da Lista `char *lista__remove(Lista **this, char *string)`
11. Crie uma função para limpar a Lista/remover todos mós da Lista `void lista__clear(Lista **this)`
12. Crie uma função para imprimir a lista, separando cada nó por uma string passada para a função `void lista__join(Lista *this, char *separador)`
13. Crie uma função que retorna a quantidade de nós em uma lista encadeada `int lista__length(Lista *this)`
14. Crie uma função que retorna uma string que está em uma posição da Lista `char *lista__get(Lista *this, int posicao)`
15. Crie uma função que ordena as strings dd uma Lista Encadeada em ordem alfabética `void lista__sort(Lista *this)`