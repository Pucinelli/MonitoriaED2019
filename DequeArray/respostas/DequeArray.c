#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

/**
 * Deque
 *
 * array { char*[MAX] } Array de strings
 * inicio { int } Posição onde o Deque começa
 * tamanho { int } Quantidade de strings no Deque
**/
typedef struct Deque
{
	char *array[MAX];
	int inicio;
	int tamanho;
} Deque;

/**
 * deque__new
 * Cria um novo Deque
 *
 * returns { Deque * } o novo Deque criado
**/
Deque *deque__new()
{
	// alocando espaço na memória para o Deque
	Deque *this = malloc(sizeof(Deque));
	// definindo que o Deque está vazio
	this->inicio = 0;
	this->tamanho = 0;
	return this;
}

/**
 * deque__push
 * Insere uma nova string no final do Deque
 *
 * this { Deque * } Deque a ter a string inserida
 * str { char * } String a ser inserida
**/
void deque__push(Deque *this, char *str)
{
	int posicao;
	// se o Deque nao estiver cheio, podemos inserir
	if(this->tamanho < MAX)
	{
		// a posição a ser ocupada
		// (início + tamanho) para saber qual a posição
		// % MAX para o caso da posição ser maior que o tamanho do array, e portanto o Deque está fazendo uma volta
		posicao = (this->inicio + this->tamanho) % MAX;
		// o final do Deque recebe a string
		this->array[posicao] = str;
		// incrementamos o tamanho
		this->tamanho++;
	} else
	{
		printf("Lista cheia.\n");
	}
}

/**
 * deque__shift
 * Insere uma nova string no começo do Deque
 *
 * this { Deque * } Deque a ter a string inserida
 * str { char * } String a ser inserida
**/
void deque__shift(Deque *this, char *str)
{
	// se o Deque não estiver cheio, podemos inserir
	if(this->tamanho < MAX)
	{
		// a posição a ser ocupada
		// (início - 1 + MAX) para saber qual a posição
		// % MAX para o caso da posição ser maior que o tamanho do array, e portanto o Deque está fazendo uma volta
		this->inicio = (this->inicio - 1 + MAX) % MAX;
		// o inicio do Deque recebe a string
		this->array[this->inicio] = str;
		// incrementamos o tamanho
		this->tamanho++;
	} else
	{
		printf("Lista cheia.\n");
	}
}

/**
 * deque__pop
 * Remove uma string no final do Deque
 *
 * this { Deque * } Deque a ter a string removida
 *
 * returns { char * } String removida do Deque
**/
char *deque__pop(Deque *this)
{
	int posicao;
	// se o Deque não estiver vazio podemos remover
	if (this->tamanho > 0)
	{
		// decrementamos o tamanho
		this->tamanho--;
		// a posição a ser removida é o final
		posicao = (this->inicio + this->tamanho) % MAX;
		// retornamos o que há no final
		return this->array[posicao];
	}
	return NULL;
}

/**
 * deque__unshift
 * Remove uma string no começo do Deque
 *
 * this { Deque * } Deque a ter a string removida
 *
 * returns { char * } String removida da Deque
**/
char *deque__unshift(Deque *this)
{
	int posicao;
	// se o Deque não estiver vazio podemos remover
	if (this->tamanho > 0)
	{
		// a posição a ser removida é o início
		posicao = this->inicio;
		// o início passa a ser a próxima posição do array (cuidando para não resultar um número maior que o próprio array)
		this->inicio = (this->inicio + 1) % MAX;
		this->tamanho--;
		// retornamos o que havia no início
		return this->array[posicao];
	}
	return NULL;
}

/**
 * deque__print
 * Imprime as strings de um Deque
 *
 * this { Deque * } Deque a ser mostrado
**/
void deque__print(Deque *this)
{
	// um for normal para mostrar o array
	for (int i = 0; i < this->tamanho; i++)
		printf("'%s', ", this->array[(this->inicio + i) % MAX]);
	printf("\n");
}

/**
 * deque__clear
 * Limpa um Deque
 *
 * this { Deque * } Deque a ter suas strings removidas
**/
void deque__clear(Deque *this)
{
	// sim, é so definir o tamanho como 0
	this->tamanho = 0;
	// gosto de definir o inicio também, mas nesse caso não faz diferença
	this->inicio = 0;
}

/**
 * deque__rprint
 * Imprime as strings de um Deque do fim até o início
 *
 * this { Deque * } Deque a ser impresso
**/
void deque__rprint(Deque *this)
{
	// for normal pra imprimir o array ao contrário
	// repare que o i começa em 1
	// caso começasse em 0, teríamos que diminuir 1 na conta da posição na hora do printf
	for (int i = 1; i <= this->tamanho; i++)
		printf("'%s', ", this->array[(this->tamanho + this->inicio - i + MAX) % MAX]);
	printf("\n");
}

/**
 * deque__join
 * Imprime as strings de um Deque, separadas por um separador
 *
 * this { Deque * } Deque a ser impresso
 * separador { char * } Separador entre as strings do Deque
**/
void deque__join(Deque *this, char *separador)
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
 * deque__length
 * Informa a quantidade de strings contidas no Deque
 *
 * this { Deque * } Deque a ter suas strings contadas
 *
 * returns { int } Quantidade de strings no Deque
**/
int deque__length(Deque *this)
{
	// o tamanho já informa a quantidade de strings do Deque
	return this->tamanho;
}

/**
 * deque__sort
 * Ordena as strings de um Deque em ordem alfabética
 *
 * this { Deque * } Deque a ter suas strings ordenadas
**/
void deque__sort(Deque *this)
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
	Deque *f = deque__new();
	
	deque__push(f, "World");
	deque__shift(f, "my dear");
	deque__shift(f, "Hello");
	deque__print(f);
	deque__rprint(f);
	
	printf("removendo '%s'\n", deque__pop(f));
	deque__print(f);
	printf("removendo '%s'\n", deque__unshift(f));
	deque__print(f);
	
	deque__clear(f);

	deque__push(f, "com");
	deque__push(f, "Deque");
	deque__shift(f, "array");
	deque__shift(f, "eh");
	deque__shift(f, "legal");

	deque__print(f);
	deque__rprint(f);
	deque__join(f, "_");
	
	printf("O Deque tem %d strings\n", deque__length(f));
	deque__clear(f);
	
	deque__push(f, "b");
	deque__push(f, "c");
	deque__push(f, "e");
	deque__push(f, "d");
	deque__push(f, "g");
	deque__push(f, "f");
	deque__push(f, "a");
	deque__push(f, "h");
	deque__push(f, "j");
	deque__push(f, "i");
	
	deque__sort(f);
	deque__print(f);
}

