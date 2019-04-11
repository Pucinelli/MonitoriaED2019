#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

/**
 * Fila
 *
 * array { char*[MAX] } Array de strings
 * inicio { int } Posição onde a fila começa
 * tamanho { int } Quantidade de strings na fila
**/
typedef struct Fila
{
	char *array[MAX];
	int inicio;
	int tamanho;
} Fila;

/**
 * fila__new
 * Cria uma nova fila
 *
 * returns { Fila * } a nova fila criada
**/
Fila *fila__new()
{
	// alocando espaço na memória para a fila
	Fila *this = malloc(sizeof(Fila));
	// definindo que fila esta vazia
	this->inicio = 0;
	this->tamanho = 0;
	return this;
}

/**
 * fila__push
 * Insere uma nova string na fila
 * Quando trabalhamos com filas, sempre inserimos no final
 *
 * this { Fila * } Fila a ter a string inserida
 * str { char * } String a ser inserida
**/
void fila__push(Fila *this, char *str)
{
	int posicao;
	// se a fila nao estiver cheia, podemos inserir
	if(this->tamanho < MAX)
	{
		// a posição a ser ocupada
		// (início + tamanho) para saber qual a posição
		// % MAX para o caso da posição ser maior que o tamanho do array, e portanto a fila está fazendo uma volta
		posicao = (this->inicio + this->tamanho) % MAX;
		// o topo da fila recebe a string
		this->array[posicao] = str;
		// incrementamos o topo
		this->tamanho++;
	} else
	{
		printf("Lista cheia.\n");
	}
}

/**
 * fila__unshift
 * Remove uma string da Fila
 * Quando trabalhamos com Filas, sempre removemos do começo
 *
 * this { Fila * } Fila a ter a string removida
 *
 * returns { char * } String removida da fila
**/
char *fila__unshift(Fila *this)
{
	int posicao;
	// se fila nao estiver vazia podemos remover
	if (this->tamanho > 0)
	{
		// a posição a ser removida é o início
		posicao = this->inicio;
		// o início passa a ser a próxima posição do array (cuidando para não resultar um número maior que o próprio array)
		this->inicio = (this->inicio + 1) % MAX;
		this->tamanho--;
		// retornamos o que há no topo
		return this->array[posicao];
	}
	return NULL;
}

/**
 * fila__print
 * Imprime as strings de uma fila
 *
 * this { Fila * } Fila a ser mostrada
**/
void fila__print(Fila *this)
{
	// um for normal para mostrar o array
	for (int i = 0; i < this->tamanho; i++)
		printf("'%s', ", this->array[(this->inicio + i) % MAX]);
	printf("\n");
}

/**
 * fila__clear
 * Limpa uma fila
 *
 * this { Fila * } Fila a ter suas strings removida
**/
void fila__clear(Fila *this)
{
	// sim, é so definir o tamanho como 0
	this->tamanho = 0;
	// gosto de definir o inicio também, mas nesse caso não faz diferença
	this->inicio = 0;
}

/**
 * fila__rprint
 * Imprime as strings de uma fila do fim até o início
 *
 * this { Fila * } Fila a ser impressa
**/
void fila__rprint(Fila *this)
{
	// for normal pra imprimir o array ao contrário
	// repare que o i começa em 1
	// caso começasse em 0, teríamos que diminuir 1 na conta da posição na hora do printf
	for (int i = 1; i <= this->tamanho; i++)
		printf("'%s', ", this->array[(this->tamanho - i + MAX) % MAX]);
	printf("\n");
}

/**
 * fila__join
 * Imprime as strings de uma fila, separadas por um separador
 *
 * this { Fila * } Fila a ser impressa
 * separador { char * } Separador entre as strings da fila
**/
void fila__join(Fila *this, char *separador)
{
	// for normal para imprimir o array
	for (int i = 0; i < this->tamanho; i++)
	{
		printf("%s", this->array[(this->inicio + i) % MAX]);
		// se não estiver na última string, imprimir o separador
		if (i < this->tamanho - 1)
			printf("%s", separador);
	}
	printf("\n");
}

/**
 * fila__length
 * Informa a quantidade de strings contidas na fila
 *
 * this { Fila * } Fila a ter suas strings contadas
 *
 * returns { int } Quantidade de strings na fila
**/
int fila__length(Fila *this)
{
	// o tamanho já informa a quantidade de strings da fila
	return this->tamanho;
}

/**
 * fila__sort
 * Ordena as strings de uma fila dm ordem alfabética
 *
 * this { Fila * } Fila a ter suas strings ordenadas
**/
void fila__sort(Fila *this)
{
	// um algoritmo básico de ordenação, pode ser substituído com o de sua preferência
	// para entender o cálculo pra acessar, é o mesmo feito na função de imprimir
	char *aux;
	for (int i = 0; i < this->tamanho; i++)
	{
		for (int j = i; j < this->tamanho; j++)
		{
			if (strcmp(this->array[(this->inicio + j) % MAX], this->array[(this->inicio + i) % MAX]) < 0)
			{
				aux = this->array[(this->inicio + i) % MAX];
				this->array[(this->inicio + i) % MAX] = this->array[(this->inicio + j) % MAX];
				this->array[(this->inicio + j) % MAX] = aux;
			}
		}
	}
}


int main(int argc, char **argv)
{
	Fila *f = fila__new();
	
	fila__push(f, "Hello");
	fila__push(f, "World");
	fila__print(f);
	
	printf("removendo '%s'\n", fila__unshift(f));
	fila__print(f);
	
	fila__clear(f);

	fila__push(f, "legal");
	fila__push(f, "eh");
	fila__push(f, "array");
	fila__push(f, "com");
	fila__push(f, "fila");

	fila__print(f);
	fila__rprint(f);
	fila__join(f, "_");
	
	printf("A fila tem %d strings\n", fila__length(f));
	fila__clear(f);
	
	fila__push(f, "b");
	fila__push(f, "c");
	fila__push(f, "e");
	fila__push(f, "d");
	fila__push(f, "g");
	fila__push(f, "f");
	fila__push(f, "a");
	fila__push(f, "h");
	fila__push(f, "j");
	fila__push(f, "i");
	
	fila__sort(f);
	fila__print(f);
}

