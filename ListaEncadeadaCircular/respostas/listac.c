#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * ListaC Encadeada Circular
 *
 * str { char * } String armazenada por cada nó
 * prox { struct ListaC * } Próximo nó da ListaC
**/
typedef struct ListaC
{
	char *str;
	struct ListaC *prox;
} ListaC;

/**
 * listac__new
 * Cria um novo nó de uma Lista Encadeada Circular
 *
 * str { char * } String armazenada pelo nó
 * prox { ListaC * } Próximo nó da lista
 *
 * returns { ListaC * } novo nó criado
**/
ListaC *listac__new(char *str, ListaC *prox)
{
	// criamos uma ListaC e alocamos espaço na memória para ela
	ListaC *this = malloc(sizeof(ListaC));
	
	// definimos as propriedades da lista criada com as passadas para a função
	this->str = str;
	
	// se o próximo não for definido, então o nó criado é o início da lista
	if (prox == NULL)
		this->prox = this;
	else
		this->prox = prox;
	
	// retornamos a lista criada
	return this;
}

/**
 * listac__push
 * Insere um novo nó no final da Lista Encadeada Circular
 *
 * this { ListaC * } ListaC a ter un novo no inserido
 * str { char * } Nova string a ser inserida
 *
 * returns { ListaC * } início da lista
**/
ListaC *listac__push(ListaC *this, char *str)
{
	// criamos uma variável para iterar sobre a lista e chegar até a última posição
	ListaC *it = this;
	
	// caso a ListaC passada seja NULL, retorna uma nova ListaC
	if (this == NULL)
		return listac__new(str, NULL);
	
	// iterando ate a última posição
	do
		it = it->prox;
	while (it->prox != this);
	
	// inserimos o novo nó no final da ListaC
	// o novo último nó aponta para o início da lista
	it->prox = listac__new(str, this);
	
	// retornamos o início da ListaC
	return this;
}

/**
 * listac__shift
 * Insere um novo nó no início da ListaC
 *
 * this { ListaC ** } Endereço da ListaC, para alterar o primeiro nó da ListaC
 * str { char * } String a ser adicionada
 *
 * returns { ListaC * } novo primeiro nó da ListaC
**/
ListaC *listac__shift(ListaC **this, char *str)
{
	// iterador para percorrer a lista
	ListaC *it = *this;
	// defininos uma ListaC que recebe a string e o primeiro nó da ListaC
	ListaC *novo_inicio = listac__new(str, *this);
	
	// caso a lista esteja vazia
	if (*this == NULL)
	{
		novo_inicio->prox = novo_inicio;
		*this = novo_inicio;
		return novo_inicio;
	}

	// percorrendo lista
	do
		it = it->prox;
	while(it->prox != *this);
	
	// o último nó da lista aponta para o novo início
	it->prox = novo_inicio;
	// o primeiro nó da ListaC passa a ser o novo nó criado
	*this = novo_inicio;
	// retornamos o novo início
	return novo_inicio;
}

/**
 * listac__insert
 * Insere um novo nó na lista em uma posição definida
 *
 * this { ListaC ** } Endereço de uma lista, para o caso do novo nó ser inserido no começo
 * str { char * } String a ser inserida na ListaC
 * posicao { int } Posição a ter o novo nó inserido
 *
 * returns { ListaC * } primeiro nó da ListaC
**/
ListaC *listac__insert(ListaC **this, char *str, int posicao)
{
	// iterador para percorrer a ListaC
	ListaC *it = *this;
	// auxiliar para saber nó anterior ao iterador
	ListaC *anterior = NULL;
	// contador
	int i = 0;
	
	if (posicao <= 0) // caso o novo nó seja o novo começo da ListaC
		*this = listac__new(str, it);
	else
	{
		// caso a lista não estiver vazia, procurar posição
		if (*this != NULL)
		{
			// enquanto não estiver no último nó da lista e não ter alcançado a posição para inserir
			do
			{
				anterior = it;
				it = it->prox;
				i++;
			} while(it != *this && i < posicao);
			if (it == *this) // caso novo nó seja o novo final da ListaC
				anterior->prox = listac__new(str, *this);
			else // o novo nó deve apontar para o próximo no da ListaC
				anterior->prox = listac__new(str, it);
		} else // a lista está vazia
		{
			*this = listac__new(str, NULL);
		}
		
	}
	
	// retornamos o primeiro nó
	return *this;
}

/**
 * listac__pop
 * Remove o último nó da lista
 *
 * this { ListaC ** } Endereço da lista, para o caso da ListaC conter apenas um nó
 *
 * returns { char * } string do nó removido
**/
char *listac__pop(ListaC **this)
{
	// iterador para percorrer a ListaC
	ListaC *it = *this;
	// auxiliar para saber qual o nó antes do nó a ser removido
	ListaC *anterior = NULL;
	// string do nó a ser removido
	char *str_removida = NULL;
	
	// caso lista já esteja vazia
	if(*this == NULL)
		return NULL;
	
	// enquanto não for o último nó da ListaC
	while (it->prox != *this)
	{
		anterior = it;
		it = it->prox;
	} 
	
	// caso a ListaC tenha apenas um nó
	if (anterior == NULL)
	{
		// a string removida recebe a string do nó a ser removido
		str_removida = it->str;
		// liberamos o nó da memória
		free(it);
		// a ListaC passa a ser NULL
		*this = NULL;
	} else
	{
		// a string removida recebe a string do nó a ser removido
		str_removida = it->str;
		// o penúltimo nó passa a ser o último
		anterior->prox = it->prox;
		// liberamos o nó da memória
		free(it);
	}
	
	// retornamos a string do nó removido
	return str_removida;
}

/**
 * listac__unshift
 * Remove o primeiro nó da ListaC
 *
 * this { ListaC ** } Endereço do primeiro nó da ListaC
 *
 * returns { char * } string do primeiro nó
**/
char *listac__unshift(ListaC **this)
{
	// iterador para percorrer a lista
	ListaC *it = *this;
	// nó a ser removido é o primeiro da ListaC
	ListaC *remover = *this;
	// string a ser removida é a string do primeiro nó
	char *str_removida = NULL;
	
	// caso lista já esteja vazia
	if(*this == NULL)
		return NULL;
	
	// percorrendo até chegar no último nó
	do
		it = it->prox;
	while(it->prox != *this);

	str_removida = remover->str;
	// o último nó aponta para o novo primeiro nó
	it->prox = (*this)->prox;
	// liberando memória do primeiro nó
	free(*this);
	
	// caso a lista tenha apenas um nó, tornar NULL
	if (remover == remover->prox)
		*this = NULL;
	else
		*this = remover->prox; // o novo primeiro nó da ListaC passa a ser o segundo nó
	// retorna a string do nó removido
	return str_removida;
}

/**
 * lista_remove
 * Remove uma string da lista
 *
 * this { ListaC ** } Endereço da lista, para poder alterar a ListaC caso o nó removido seja o primeiro
 * str { char * } String a ser removida
 *
 * return { char * } string do nó removido
**/
char *listac__remove(ListaC **this, char *str)
{
	// variável para iterar sobre a lista e chegar até a última posição
	ListaC *it = *this;
	// variável para saber qual o nó que esta antes do nó a ser removido
	ListaC *anterior = NULL;
	// variável para guardar o nó a ser removido
	ListaC *remover = NULL;
	// variável para retornaro a string removida
	char *str_removida = NULL;
	
	// caso a lista já esteja vazia
	if (*this == NULL)
		return NULL;

	// iterar enquanto a lista não acabar
	while (it != *this)
	{
		// caso o iterador tenha a string a ser removida, parar o loop
		if (strcmp(it->str, str) == 0)
			break;
		// o anterior recebe o iterador antes do iterador receber o proximo nó da ListaC
		anterior = it;
		// caso o próximo seja o primeiro nó, a lista acaba
		if (it->prox == *this)
		{
			it = NULL;
			break;
		}
		it = it->prox;
	}
	
	// se o iterador for NULL, a string procurada não existe na lista
	if (it != NULL)
	{
		// definindo o nó a ser removido
		remover = it;
		// definindo a string a ser retornada
		str_removida = remover->str;
		// caso a palavra a ser removida seja do primeiro nó da ListaC
		if (anterior == NULL)
		{
			// caso a lista tenha apenas um nó, tornar NULL
			if(it == it->prox)
				*this = NULL;
			else
				*this = (*this)->prox; // para remover o primeiro item, apenas definimos o segundo item como o novo primeiro
		}
		else
			anterior->prox = it->prox; // o nó anterior ao removido aponta para o nó apos o removido
	}
	
	// liberamos o nó removido da memória
	free(remover);
	
	// retornamos a string encontrada
	return str_removida;
}

/**
 * lista_remove_at
 * Remove um nó em uma dada posição da lista
 *
 * this { ListaC ** } Endereço da lista, para poder alterar a ListaC caso o nó removido seja o primeiro
 * posicao { char * } Posição do nó a ser removido
 *
 * return { char * } string do nó removido
**/
char *listac__remove_at(ListaC **this, int posicao)
{
	// variável para iterar sobre a lista e chegar até a última posição
	ListaC *it = *this;
	// variável para saber qual o nó que esta antes do nó a ser removido
	ListaC *anterior = NULL;
	// variável para guardar o nó a ser removido
	ListaC *remover = NULL;
	// variável para retornaro a string removida
	char *str_removida = NULL;
	// contador
	int i = 0;
	
	// caso lista já esteja vazia
	if(*this == NULL)
		return NULL;
	
	// iterar enquanto a lista não acabar
	while (it->prox != *this && i < posicao)
	{
		// o anterior recebe o iterador antes do iterador receber o proximo nó da ListaC
		anterior = it;
		it = it->prox;
	}
	
	// definindo o nó a ser removido
	remover = it;
	// definindo a string a ser retornada
	str_removida = remover->str;
	// caso a palavra a ser removida seja do primeiro nó da ListaC
	if (anterior == NULL)
	{
		// caso a lista tenha apenas um nó, tornar NULL
		if(it == it->prox)
			*this = NULL;
		else
			*this = (*this)->prox; // para remover o primeiro item, apenas definimos o segundo item como o novo primeiro
	} else
		anterior->prox = it->prox; // o nó anterior ao removido aponta para o nó apos o removido
	
	// liberamos o nó removido da memória
	free(remover);
	
	// retornamos a string encontrada
	return str_removida;
}

/**
 * listac__clear
 * Esvazia uma ListaC Encadeada
 *
 * this { ListaC ** } Endereço da ListaC a ser esvaziada, no final se tornara NULL
**/
void listac__clear(ListaC **this)
{
	// enquanto a ListaC não estiver vazia, removemos o primeiro elemento
	while(*this != NULL)
		listac__unshift(this);
}

/**
 * listac__print
 * Mostra todos nós da ListaC
 *
 * this { ListaC * } ListaC a ser mostrada
**/
void listac__print(ListaC *this)
{
	// iterador para percorrer a ListaC
	ListaC *it = this;
	
	// enquanto a ListaC não acabar
	if (this != NULL)
		do
		{
			printf("'%s', ", it->str);
			it = it->prox;
		} while (it != this);
	
	printf("\n");
}

/**
 * listac__join
 * Imprime a ListaC, separando os nós com um separador
 *
 * this { ListaC * } ListaC a ser mostrada
 * separador { char * } Separador entre os nós da ListaC
**/
void listac__join(ListaC *this, char *separador)
{
	// iterador para percorrer a lista
	ListaC *it = this;
	
	// enquanto a ListaC não acabar
	if (this != NULL)
		do
		{
			printf("%s", it->str);
			// se o nó nao for o último, imprimir o separador
			if (it->prox != this)
				printf("%s", separador);
			it = it->prox;
		} while (it != this);
	
	printf("\n");
}

/**
 * listac__length
 * Informa a quantidade de nós na ListaC
 *
 * this { ListaC * } ListaC a ter os nós contados
 *
 * returns { int } Quantidade de nós da ListaC
**/
int listac__length(ListaC *this)
{
	// iterador para percorrer a ListaC
	ListaC *it = this;
	// contador de nós da ListaC
	int tamanho = 0;
	
	// caso a lista esteja vazia
	if (this == NULL)
		return 0;

	// percorrer a ListaC e incrementar o tamanho para cada nó
	do
	{
		tamanho++;
		it = it->prox;
	} while (it != this);
	
	// retornar a quantidade de nós
	return tamanho;
}

/**
 * listac__get
 * Retorna a string em determinada posição da ListaC
 *
 * this { ListaC * } ListaC a ter a string procurada
 * posicao { int } Posição a ser procurada na ListaC
**/
char *listac__get(ListaC *this, int posicao)
{
	// iterador para percorrer a ListaC
	ListaC *it = this;
	// contador para saber a posição
	int i = 0;
	// string a ser retornada
	char *str_encontrada = NULL;
	
	// caso a lista esteja vazia
	if (this == NULL)
		return NULL;

	// percorrer ListaC até acabar ou chegar na posição definida
	if (posicao > 0)
		do
		{
			i++;
			it = it->prox;
		} while (it != this && i < posicao);
	else
		str_encontrada = it->str;
	
	// se encontrar a posição, definir a string a ser retornada
	if (it != this)
		str_encontrada = it->str;
	return str_encontrada;
}

/**
 * listac__sort
 * 
 * Ordena os elementos de uma ListaC Encadeada
 *
 * this { ListaC * } ListaC a ser ordenada
**/
void listac__sort(ListaC *this)
{
	// iteradores e auxiliar
	ListaC *it_i = this;
	ListaC *it_j;
	char *aux;
	
	// percorrendo lista ate o final
	do
	{
		it_j = it_i;
		do
		{
			// comparando e trocando as strings
			if (strcmp(it_j->str, it_i->str) < 0)
			{
				aux = it_i->str;
				it_i->str = it_j->str;
				it_j->str = aux;
			}
			it_j = it_j->prox;
		} while (it_j != this);
		it_i = it_i->prox;
	} while (it_i != this);
}

int main(int argc, char **argv)
{
	ListaC *l = listac__new("Hello", NULL);
	listac__print(l);
	
	l = listac__push(l, "World");
	l = listac__insert(&l, "my dear", 1);
	
	listac__print(l);
	
	listac__pop(&l);
	listac__unshift(&l);
	listac__remove(&l, "my dear");
	
	listac__print(l);
	
	l = listac__shift(&l, "Wow");
	l = listac__push(l, "worked");
	l = listac__insert(&l, "this", 1);

	listac__join(l, " ");
	
	printf("A lista possui %d elementos.\n", listac__length(l));
	
	listac__clear(&l);
	
	printf("A lista possui %d elementos.\n", listac__length(l));
	
	l = listac__insert(&l, "teste0", 123);
	listac__print(l);
	listac__remove_at(&l, 54321);
	listac__print(l);
	
	l = listac__push(l, "teste1");
	listac__print(l);
	listac__pop(&l);
	listac__print(l);
	
	l = listac__shift(&l, "teste2");
	listac__print(l);
	listac__unshift(&l);
	listac__print(l);
	
	listac__clear(&l);
	l = listac__push(l, "b");
	l = listac__push(l, "c");
	l = listac__push(l, "e");
	l = listac__push(l, "d");
	l = listac__push(l, "f");
	l = listac__push(l, "a");
	l = listac__push(l, "g");
	
	listac__sort(l);
	listac__print(l);
	
	listac__clear(&l);
	
	l = listac__insert(&l, "agora", 0);
	l = listac__shift(&l, "ok,");
	l = listac__push(l, "acabou");
	
	for (int i = 0; i < listac__length(l); i++)
		printf("%s ", listac__get(l, i));

	return 0;
}