# ListaD Duplamente Encadeada

## Exercícios básicos (o mínimo necessário para a prova)

1. Faça uma listad duplamente encadeada de strings (char *)
2. Crie uma função para criar um novo nó de ListaD Duplamente Encadeada `ListaD *listad__new(char *string, ListaD *prox)`
3. Crie uma função para inserir um novo nó em qualquer posição da ListaD `ListaD *listad__insert(ListaD **this, char *string)`
4. Crie uma função para remover um nó da ListaD em qualquer posição `char *listad__remove_at(ListaD **this, int posicao)`
5. Crie uma função para imprimir a ListaD `void listad__print(ListaD *this)`

## Exercícios extras (para quem sentir que precisa reforcar mais um pouco)

6. Crie uma função para inserir no começo de uma ListaD `ListaD *listad__shift(ListaD **this, char *string)`
7. Crie uma função para inserir no final de uma ListaD `ListaD *listad__push(ListaD *this, char *string)`
8. Crie uma função para remover no começo de uma ListaD `char *listad__unshift(ListaD **this)`
9. Crie uma função para remover no final de uma ListaD `char *listad__pop(ListaD **this)`
10. Crie uma função para remover uma determinada string da ListaD `char *listad__remove(ListaD **this, char *string)`
11. Crie uma função para limpar a ListaD/remover todos nós da ListaD `void listad__clear(ListaD **this)`
12. Crie uma função para imprimir a listad ao contrário `void listad__rprint(ListaD *this)`
13. Crie uma função para imprimir a listad, separando cada nó por uma string passada para a função `void listad__join(ListaD *this, char *separador)`
14. Crie uma função que retorna a quantidade de nós em uma listad encadeada `int listad__length(ListaD *this)`
15. Crie uma função que retorna uma string que está em uma posição da ListaD `char *listad__get(ListaD *this, int posicao)`
16. Crie uma função que ordena as strings de uma Lista Duplamente Encadeada em ordem alfabética `void listad__sort(ListaD *this)`