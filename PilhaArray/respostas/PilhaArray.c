#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

/**
 * Pilha
 *
 * array { char*[MAX] } Array de strings
 * topo { int } Posição que vai ter a nova string inserida
**/
typedef struct Pilha
{
	char *array[MAX];
	int topo;
} Pilha;

/**
 * pilha__new
 * Cria uma nova pilha
 *
 * returns { Pilha * } a nova pilha criada
**/
Pilha *pilha__new()
{
	// alocando espaço na memória para a pilha
	Pilha *this = malloc(sizeof(Pilha));
	// definindo que pilha esta vazia
	this->topo = 0;
	return this;
}

/**
 * pilha__push
 * Insere uma nova string na pilha
 *
 * this { Pilha * } Pilha a ter a string inserida
 * str { char * } String a ser inserida
**/
void pilha__push(Pilha *this, char *str)
{
	// se a pilha nao estiver cheia, podemos inserir
	if(this->topo < MAX)
	{
		// o topo da pilha recebe a string
		this->array[this->topo] = str;
		// incrementamos o topo
		this->topo++;
	} else
	{
		printf("Lista cheia.\n");
	}
}

/**
 * pilha__pop
 * Remove uma string da Pilha
 *
 * this { Pilha * } Pilha a ter a string removida
 *
 * returns { char * } String removida da pilha
**/
char *pilha__pop(Pilha *this)
{
	// se polha nao estiver vazia podemos remover
	if (this->topo > 0)
	{
		// decrementamos o topo (porque o topo é onde a nova string deve ser inserida, e portanto é sempre NULL)
		this->topo--;
		// retornamos o que há no topo
		return this->array[this->topo];
	}
	return NULL;
}

/**
 * pilha__print
 * Imprime as strings de uma pilha
 *
 * this { Pilha * } Pilha a ser mostrada
**/
void pilha__print(Pilha *this)
{
	// um for normal para mostrar o array
	for (int i = 0; i < this->topo; i++)
		printf("'%s', ", this->array[i]);
	printf("\n");
}

/**
 * pilha__clear
 * Limpa uma pilha
 *
 * this { Pilha * } Pilha a ter suas strings removida
**/
void pilha__clear(Pilha *this)
{
	// sim, é so definir o topo como 0
	this->topo = 0;
}

/**
 * pilha__rprint
 * Imprime as strings de uma pilha do topo ate o começo
 *
 * this { Pilha * } Pilha a ser impressa
**/
void pilha__rprint(Pilha *this)
{
	// for normal pra imprimir o array ao contrário
	for (int i = this->topo - 1; i >= 0; i--)
		printf("'%s', ", this->array[i]);
	printf("\n");
}

/**
 * pilha__join
 * Imprime as strings dd uma pilha, separadas por um separador
 *
 * this { Pilha * } Pilha a ser impressa
 * separador { char * } Separador entre as strings da pilha
**/
void pilha__join(Pilha *this, char *separador)
{
	// for normal para imprimir o array
	for (int i = 0; i < this->topo; i++)
	{
		printf("%s", this->array[i]);
		// se não estiver na última string, imprimir o separador
		if (i < this->topo - 1)
			printf("%s", separador);
	}
	printf("\n");
}

/**
 * pilha__length
 * Informa a quantidade de strings contidas na pilha
 *
 * this { Pilha * } Pilha a ter suas strings contadas
 *
 * returns { int } Quantidade de strings na pilha
**/
int pilha__length(Pilha *this)
{
	// o topo já informa a quantidade de strings da pilha
	return this->topo;
}

/**
 * pilha__sort
 * Ordena as strings de uma pilha dm ordem alfabética
 *
 * this { Pilha * } Pilha a ter suas strings ordenadas
**/
void pilha__sort(Pilha *this)
{
	// um algoritmo básico de ordenação, pode ser substituído com o de sua preferência
	char *aux;
	for (int i = 0; i < this->topo; i++)
	{
		for (int j = i; j < this->topo; j++)
		{
			if (strcmp(this->array[j], this->array[i]) < 0)
			{
				aux = this->array[i];
				this->array[i] = this->array[j];
				this->array[j] = aux;
			}
		}
	}
}


int main(int argc, char **argv)
{
	Pilha *p = pilha__new();
	
	pilha__push(p, "Hello");
	pilha__push(p, "World");
	pilha__print(p);
	
	printf("removendo '%s'\n", pilha__pop(p));
	pilha__print(p);
	
	pilha__clear(p);
	
	pilha__push(p, "legal");
	pilha__push(p, "eh");
	pilha__push(p, "array");
	pilha__push(p, "com");
	pilha__push(p, "pilha");
	
	pilha__rprint(p);
	pilha__join(p, "_");
	
	printf("A pilha tem %d strings\n", pilha__length(p));
	pilha__clear(p);
	
	pilha__push(p, "b");
	pilha__push(p, "c");
	pilha__push(p, "e");
	pilha__push(p, "d");
	pilha__push(p, "g");
	pilha__push(p, "f");
	pilha__push(p, "a");
	
	pilha__sort(p);
	pilha__print(p);
}

