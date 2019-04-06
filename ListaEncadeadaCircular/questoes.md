# Lista Encadeada Circular

## Exercícios básicos (o mínimo necessário para a prova)

1. Faça uma lista encadeada circular de strings (char *)
2. Crie uma função para criar um novo nó de Lista Encadeada Circular `ListaC *listac__new(char *string, Lista *prox)`
3. Crie uma função para inserir um novo nó em qualquer posição da Lista `ListaC *listac__insert(ListaC **this, char *string)`
4. Crie uma função para remover um nó da Lista em qualquer posição `char *listac__remove_at(ListaC **this, int posicao)`
5. Crie uma função para imprimir a Lista `void lista__print(ListaC *this)`

## Exercícios extras (para quem sentir que precisa reforcar mais um pouco)

6. Crie uma função para inserir no começo de uma Lista `ListaC *listac__shift(ListaC **this, char *string)`
7. Crie uma função para inserir no final de uma Lista `ListaC *listac__push(ListaC *this, char *string)`
8. Crie uma função para remover no começo de uma Lista `char *listac__unshift(ListaC **this)`
9. Crie uma função para remover no final de uma Lista `char *listac__pop(ListaC **this)`
10. Crie uma função para remover uma determinada string da Lista `char *listac__remove(ListaC **this, char *string)`
11. Crie uma função para limpar a Lista/remover todos nós da Lista `void listac__clear(ListaC **this)`
12. Crie uma função para imprimir a lista, separando cada nó por uma string passada para a função `void listac__join(ListaC *this, char *separador)`
13. Crie uma função que retorna a quantidade de nós em uma lista encadeada circular `int listac__length(ListaC *this)`
14. Crie uma função que retorna uma string que está em uma posição da Lista `char *listac__get(ListaC *this, int posicao)`
15. Crie uma função que ordena as strings de uma Lista Encadeada Circular em ordem alfabética `void listac__sort(ListaC *this)`