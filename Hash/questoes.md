# Hash Table

## Exercícios básicos (o mínimo necessário para a prova)

Considere a seguinte struct:
```c
typedef struct Contato
{
    char nome[64];
    unsigned long numero;
} Contato;
```
Crie o algoritmo de uma lista telefônica utilizando tabela hash.

1. Faça uma tabela hash de Contatos que suporte no mínimo 1024 Contatos
2. Crie uma função para calcular o hash de um Contato utilizando o número do Contato
3. Crie uma função para inserir um Contato na tabela, em caso de colisão, esta função deve inserir na primeira posição livre
4. Crie uma função para inserir um Contato na tabela, em caso de colisão, esta função deve utilizar uma segunda função de dispersão
5. Crie uma função para remover um Contato da tabela
6. Crie uma função que recebe um número de telefone e retorna o Contato associado à ele
6. Crie uma função que imprime a tabela hash e informa quantos Contatos foram inseridos

7. Refaça a tabela hash, desta vez utilizando uma Lista Encadeada de Contatos.

## Exercícios extras (para quem sentir que precisa reforcar mais um pouco)

***Coming soon***
