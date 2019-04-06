#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Lista Encadeada
 *
 * str { char * } String armazenada por cada nó
 * prox { struct Lista * } Próximo nó da Lista
**/
typedef struct Lista
{
	char *str;
	struct Lista *prox;
} Lista;

/**
 * lista__new
 * Cria um novo nó de uma Lista Encadeada
 *
 * str { char * } String armazenada pelo nó
 * prox { Lista * } Próximo nó da lista
 *
 * returns { Lista * } novo nó criado
**/
Lista *lista__new(char *str, Lista *prox)
{
	// criamos uma Lista e alocamos espaço na memória para ela
	Lista *this = malloc(sizeof(Lista));
	
	// definimos as propriedades da lista criada com as passadas para a função
	this->str = str;
	this->prox = prox;
	
	// retornamos a lista criada
	return this;
}

/**
 * lista__push
 * Insere um novo nó no final da Lista Encadeada
 *
 * this { Lista * } Lista a ter un novo no inserido
 * str { char * } Nova string a ser inserida
 *
 * returns { Lista * } início da lista
**/
Lista *lista__push(Lista *this, char *str)
{
	// criamos uma variável para iterar sobre a lista e chegar até a última posição
	Lista *it = this;
	
	// caso a Lista passada seja NULL, retorna uma nova Lista
	if (this == NULL)
		return lista__new(str, NULL);
	
	// iterando ate a última posição
	while (it->prox != NULL)
		it = it->prox;
	
	// inserimos o novo nó no final da Lista
	it->prox = lista__new(str, NULL);
	
	// retornamos o início da Lista
	return this;
}

/**
 * lista__shift
 * Insere um novo nó no início da Lista
 *
 * this { Lista ** } Endereço da Lista, para alterar o primeiro nó da Lista
 * str { char * } String a ser adicionada
 *
 * returns { Lista * } novo primeiro nó da Lista
**/
Lista *lista__shift(Lista **this, char *str)
{
	// defininos uma Lista que recebe a string e o primeiro nó da Lista
	Lista *novo_inicio = lista__new(str, *this);
	// o primeiro nó da Lista passa a ser o novo nó criado
	*this = novo_inicio;
	// retornamos o novo início
	return novo_inicio;
}

/**
 * lista__insert
 * Insere um novo nó na lista em uma posição definida
 *
 * this { Lista ** } Endereço de uma lista, para o caso do novo nó ser inserido no começo
 * str { char * } String a ser inserida na Lista
 * posicao { int } Posição a ter o novo nó inserido
 *
 * returns { Lista * } primeiro nó da Lista
**/
Lista *lista__insert(Lista **this, char *str, int posicao)
{
	// iterador para percorrer a Lista
	Lista *it = *this;
	// auxiliar para saber nó anterior ao iterador
	Lista *anterior = NULL;
	// contador
	int i = 0;
	
	// enquanto não estiver no último nó da lista e não ter alcançado a posição para inserir
	while(it != NULL && i < posicao)
	{
		anterior = it;
		it = it->prox;
		i++;
	}
	
	if (i == 0) // caso o novo nó seja o novo começo da Lista
		*this = lista__new(str, it);
	else if (it == NULL) // caso novo nó seja o novo final da Lista
		anterior->prox = lista__new(str, NULL);
	else // o novo nó deve apontar para o próximo no da Lista
		anterior->prox = lista__new(str, it);
	
	// retornamos o primeiro nó
	return *this;
}

/**
 * lista__pop
 * Remove o último nó da lista
 *
 * this { Lista ** } Endereço da lista, para o caso da Lista conter apenas um nó
 *
 * returns { char * } string do nó removido
**/
char *lista__pop(Lista **this)
{
	// iterador para percorrer a Lista
	Lista *it = *this;
	// auxiliar para saber qual o nó antes do nó a ser removido
	Lista *anterior = NULL;
	// string do nó a ser removido
	char *str_removida = NULL;
	
	// caso lista já esteja vazia
	if(*this == NULL)
		return NULL;
	
	// enquanto não for o último nó da Lista
	while(it->prox != NULL)
	{
		anterior = it;
		it = it->prox;
	}
	
	// caso a Lista tenha apenas um nó
	if (anterior == NULL)
	{
		// a string removida recebe a string do nó a ser removido
		str_removida = it->str;
		// liberamos o nó da memória
		free(it);
		// a Lista passa a ser NULL
		*this = NULL;
	} else
	{
		// a string removida recebe a string do nó a ser removido
		str_removida = it->str;
		// o penúltimo nó passa a ser o último
		anterior->prox = NULL;
		// liberamos o nó da memória
		free(it);
	}
	
	// retornamos a string do nó removido
	return str_removida;
}

/**
 * lista__unshift
 * Remove o primeiro nó da Lista
 *
 * this { Lista ** } Endereço do primeiro nó da Lista
 *
 * returns { char * } string do primeiro nó
**/
char *lista__unshift(Lista **this)
{
	// nó a ser removido é o primeiro da Lista
	Lista *remover = *this;
	// string a ser removida é a string do primeiro nó
	char *str_removida = NULL;
	
	// caso lista já esteja vazia
	if(*this == NULL)
		return NULL;
	
	str_removida = remover->str;
	// liberando memória do primeiro nó
	free(*this);
	// o novo primeiro nó da Lista passa a ser o segundo nó
	*this = remover->prox;
	// retorna a string do nó removido
	return str_removida;
}

/**
 * lista_remove
 * Remove uma string da lista
 *
 * this { Lista ** } Endereço da lista, para poder alterar a Lista caso o nó removido seja o primeiro
 * str { char * } String a ser removida
 *
 * return { char * } string do nó removido
**/
char *lista__remove(Lista **this, char *str)
{
	// variável para iterar sobre a lista e chegar até a última posição
	Lista *it = *this;
	// variável para saber qual o nó que esta antes do nó a ser removido
	Lista *anterior = NULL;
	// variável para guardar o nó a ser removido
	Lista *remover = NULL;
	// variável para retornaro a string removida
	char *str_removida = NULL;
	
	// iterar enquanto a lista não acabar
	while (it != NULL)
	{
		// caso o iterador tenha a string a ser removida, parar o loop
		if (strcmp(it->str, str) == 0)
			break;
		// o anterior recebe o iterador antes do iterador receber o proximo nó da Lista
		anterior = it;
		it = it->prox;
	}
	
	// se o iterador for NULL, a string procurada não existe na lista
	if (it != NULL)
	{
		// definindo o nó a ser removido
		remover = it;
		// definindo a string a ser retornada
		str_removida = remover->str;
		// caso a palavra a ser removida seja do primeiro nó da Lista
		if (anterior == NULL)
			*this = (*this)->prox; // para remover o primeiro item, apenas definimos o segundo item como o novo primeiro
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
 * this { Lista ** } Endereço da lista, para poder alterar a Lista caso o nó removido seja o primeiro
 * posicao { char * } Posição do nó a ser removido
 *
 * return { char * } string do nó removido
**/
char *lista__remove_at(Lista **this, int posicao)
{
	// variável para iterar sobre a lista e chegar até a última posição
	Lista *it = *this;
	// variável para saber qual o nó que esta antes do nó a ser removido
	Lista *anterior = NULL;
	// variável para guardar o nó a ser removido
	Lista *remover = NULL;
	// variável para retornaro a string removida
	char *str_removida = NULL;
	// contador
	int i = 0;
	
	// caso lista já esteja vazia
	if(*this == NULL)
		return NULL;
	
	// iterar enquanto a lista não acabar
	while (it->prox != NULL && i < posicao)
	{
		// o anterior recebe o iterador antes do iterador receber o proximo nó da Lista
		anterior = it;
		it = it->prox;
	}
	
	// definindo o nó a ser removido
	remover = it;
	// definindo a string a ser retornada
	str_removida = remover->str;
	// caso a palavra a ser removida seja do primeiro nó da Lista
	if (anterior == NULL)
		*this = (*this)->prox; // para remover o primeiro item, apenas definimos o segundo item como o novo primeiro
	else
		anterior->prox = it->prox; // o nó anterior ao removido aponta para o nó apos o removido
	
	// liberamos o nó removido da memória
	free(remover);
	
	// retornamos a string encontrada
	return str_removida;
}

/**
 * lista__clear
 * Esvazia uma Lista Encadeada
 *
 * this { Lista ** } Endereço da Lista a ser esvaziada, no final se tornara NULL
**/
void lista__clear(Lista **this)
{
	// enquanto a Lista não estiver vazia, removemos o primeiro elemento
	while(*this != NULL)
		lista__unshift(this);
}

/**
 * lista__print
 * Mostra todos nós da Lista
 *
 * this { Lista * } Lista a ser mostrada
**/
void lista__print(Lista *this)
{
	// iterador para percorrer a Lista
	Lista *it = this;
	
	// enquanto a Lista não acabar
	while (it != NULL)
	{
		printf("'%s', ", it->str);
		it = it->prox;
	}
	
	printf("\n");
}

/**
 * lista__join
 * Imprime a Lista, separando os nós com um separador
 *
 * this { Lista * } Lista a ser mostrada
 * separador { char * } Separador entre os nós da Lista
**/
void lista__join(Lista *this, char *separador)
{
	// iterador para percorrer a lista
	Lista *it = this;
	
	// enquanto a Lista não acabar
	while (it != NULL)
	{
		printf("%s", it->str);
		// se o nó nao for o último, imprimir o separador
		if (it->prox != NULL)
			printf("%s", separador);
		it = it->prox;
	}
	
	printf("\n");
}

/**
 * lista__length
 * Informa a quantidade de nós na Lista
 *
 * this { Lista * } Lista a ter os nós contados
 *
 * returns { int } Quantidade de nós da Lista
**/
int lista__length(Lista *this)
{
	// iterador para percorrer a Lista
	Lista *it = this;
	// contador de nós da Lista
	int tamanho = 0;
	
	// percorrer a Lista e incrementar o tamanho para cada nó
	while (it != NULL)
	{
		tamanho++;
		it = it->prox;
	}
	
	// retornar a quantidade de nós
	return tamanho;
}

/**
 * lista__get
 * Retorna a string em determinada posição da Lista
 *
 * this { Lista * } Lista a ter a string procurada
 * posicao { int } Posição a ser procurada na Lista
**/
char *lista__get(Lista *this, int posicao)
{
	// iterador para percorrer a Lista
	Lista *it = this;
	// contador para saber a posição
	int i = 0;
	// string a ser retornada
	char *str_encontrada = NULL;
	
	// percorrer Lista até acabar ou chegar na posição definida
	while (it != NULL && i < posicao)
	{
		i++;
		it = it->prox;
	}
	
	// se encontrar a posição, definir a string a ser retornada
	if (it != NULL)
		str_encontrada = it->str;
	return str_encontrada;
}

/**
 * lista__sort
 * Ordena os elementos de uma Lista Encadeada
 *
 * this { Lista * } Lista a ser ordenada
**/
void lista__sort(Lista *this)
{
	// iteradores e auxiliar
	Lista *it_i;
	Lista *it_j;
	char *aux;
	
	// percorrendo lista ate o final
	for (it_i = this; it_i != NULL; it_i = it_i->prox)
	{
		for (it_j = it_i; it_j != NULL; it_j = it_j->prox)
		{
			// comparando e trocando as strings
			if (strcmp(it_j->str, it_i->str) < 0)
			{
				aux = it_i->str;
				it_i->str = it_j->str;
				it_j->str = aux;
			}
		}
	}
}

int main(int argc, char **argv)
{
	Lista *l = lista__new("Hello", NULL);
	lista__print(l);
	
	l = lista__push(l, "World");
	l = lista__insert(&l, "my dear", 1);
	
	lista__print(l);
	
	lista__pop(&l);
	lista__unshift(&l);
	lista__remove(&l, "my dear");
	
	lista__print(l);
	
	l = lista__shift(&l, "Wow");
	l = lista__push(l, "worked");
	l = lista__insert(&l, "this", 1);

	lista__join(l, " ");
	
	printf("A lista possui %d elementos.\n", lista__length(l));
	
	lista__clear(&l);
	
	printf("A lista possui %d elementos.\n", lista__length(l));
	
	l = lista__insert(&l, "teste0", 123);
	lista__print(l);
	lista__remove_at(&l, 54321);
	lista__print(l);
	
	l = lista__push(l, "teste1");
	lista__print(l);
	lista__pop(&l);
	lista__print(l);
	
	l = lista__shift(&l, "teste2");
	lista__print(l);
	lista__unshift(&l);
	lista__print(l);
	
	lista__clear(&l);
	l = lista__push(l, "b");
	l = lista__push(l, "c");
	l = lista__push(l, "e");
	l = lista__push(l, "d");
	l = lista__push(l, "f");
	l = lista__push(l, "a");
	l = lista__push(l, "g");
	
	lista__sort(l);
	lista__print(l);
	
	lista__clear(&l);
	
	l = lista__insert(&l, "agora", 0);
	l = lista__shift(&l, "ok,");
	l = lista__push(l, "acabou");
	
	for (int i = 0; i < lista__length(l); i++)
		printf("%s ", lista__get(l, i));
	
	return 0;
}