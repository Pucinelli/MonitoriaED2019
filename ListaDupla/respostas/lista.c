#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Lista Duplamente Encadeda
 *
 * str { char * } String armazenada por cada nó
 * prox { struct ListaD * } Próximo nó da ListaD
 * ante { struct ListaD * } Nó anterior da ListaD
**/
typedef struct ListaD
{
	char *str;
	struct ListaD *prox;
	struct ListaD *ante;
} ListaD;

/**
 * listad__new
 * Cria um novo nó de uma Lista Duplamente Encadeda
 *
 * str { char * } String armazenada pelo nó
 * prox { ListaD * } Próximo nó da listad
 * ante { ListaD * } Nó anterior da listad
 *
 * returns { ListaD * } novo nó criado
**/
ListaD *listad__new(char *str, ListaD *prox, ListaD *ante)
{
	// criamos uma ListaD e alocamos espaço na memória para ela
	ListaD *this = malloc(sizeof(ListaD));
	
	// definimos as propriedades da listad criada com as passadas para a função
	this->str = str;
	this->prox = prox;
	this->ante = ante;
	
	// retornamos a listad criada
	return this;
}

/**
 * listad__push
 * Insere um novo nó no final da Lista Duplamente Encadeda
 *
 * this { ListaD * } ListaD a ter un novo no inserido
 * str { char * } Nova string a ser inserida
 *
 * returns { ListaD * } início da listad
**/
ListaD *listad__push(ListaD *this, char *str)
{
	// criamos uma variável para iterar sobre a listad e chegar até a última posição
	ListaD *it = this;
	
	// caso a ListaD passada seja NULL, retorna uma nova ListaD
	if (this == NULL)
		return listad__new(str, NULL, NULL);
	
	// iterando ate a última posição
	while (it->prox != NULL)
		it = it->prox;
	
	// inserimos o novo nó no final da ListaD
	it->prox = listad__new(str, NULL, it);
	
	// retornamos o início da ListaD
	return this;
}

/**
 * listad__shift
 * Insere um novo nó no início da ListaD
 *
 * this { ListaD ** } Endereço da ListaD, para alterar o primeiro nó da ListaD
 * str { char * } String a ser adicionada
 *
 * returns { ListaD * } novo primeiro nó da ListaD
**/
ListaD *listad__shift(ListaD **this, char *str)
{
	// defininos uma ListaD que recebe a string e o primeiro nó da ListaD
	ListaD *novo_inicio = listad__new(str, *this, NULL);
	// definimos que o anterior ao início aponta para o novo início
	if (*this != NULL)
		(*this)->ante = novo_inicio;
	// o primeiro nó da ListaD passa a ser o novo nó criado
	*this = novo_inicio;
	// retornamos o novo início
	return novo_inicio;
}

/**
 * listad__insert
 * Insere um novo nó na listad em uma posição definida
 *
 * this { ListaD ** } Endereço de uma listad, para o caso do novo nó ser inserido no começo
 * str { char * } String a ser inserida na ListaD
 * posicao { int } Posição a ter o novo nó inserido
 *
 * returns { ListaD * } primeiro nó da ListaD
**/
ListaD *listad__insert(ListaD **this, char *str, int posicao)
{
	// iterador para percorrer a ListaD
	ListaD *it = *this;
	// auxiliar para saber nó anterior ao iterador
	ListaD *anterior = NULL;
	// contador
	int i = 0;
	
	// enquanto não estiver no último nó da listad e não ter alcançado a posição para inserir
	while(it != NULL && i < posicao)
	{
		anterior = it;
		it = it->prox;
		i++;
	}
	
	if (i == 0)
	{
		// caso o novo nó seja o novo começo da ListaD
		*this = listad__new(str, it, NULL);
		// caso a lista não esteja vazia, o antigo começo deve apontar para o novo começo
		if (it != NULL)
			it->ante = *this;
	} else if (it == NULL) // caso novo nó seja o novo final da ListaD
		anterior->prox = listad__new(str, NULL, anterior);
	else
	{
		// o novo nó deve apontar para o próximo no da ListaD
		anterior->prox = listad__new(str, it, anterior);
		// o próximo nó deve apontar para seu novo anterior
		it->ante = anterior->prox;
	}
	
	// retornamos o primeiro nó
	return *this;
}

/**
 * listad__pop
 * Remove o último nó da listad
 *
 * this { ListaD ** } Endereço da listad, para o caso da ListaD conter apenas um nó
 *
 * returns { char * } string do nó removido
**/
char *listad__pop(ListaD **this)
{
	// iterador para percorrer a ListaD
	ListaD *it = *this;
	// auxiliar para saber qual o nó antes do nó a ser removido
	ListaD *anterior = NULL;
	// string do nó a ser removido
	char *str_removida = NULL;
	
	// caso listad já esteja vazia
	if(*this == NULL)
		return NULL;
	
	// enquanto não for o último nó da ListaD
	while(it->prox != NULL)
	{
		anterior = it;
		it = it->prox;
	}
	
	// caso a ListaD tenha apenas um nó
	if (anterior == NULL)
	{
		// a string removida recebe a string do nó a ser removido
		str_removida = it->str;
		// liberamos o nó da memória
		free(it);
		// a ListaD passa a ser NULL
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
 * listad__unshift
 * Remove o primeiro nó da ListaD
 *
 * this { ListaD ** } Endereço do primeiro nó da ListaD
 *
 * returns { char * } string do primeiro nó
**/
char *listad__unshift(ListaD **this)
{
	// nó a ser removido é o primeiro da ListaD
	ListaD *remover = *this;
	// string a ser removida é a string do primeiro nó
	char *str_removida = NULL;
	
	// caso listad já esteja vazia
	if(*this == NULL)
		return NULL;
	
	str_removida = remover->str;
	// liberando memória do primeiro nó
	free(*this);
	// o novo primeiro nó da ListaD passa a ser o segundo nó
	*this = remover->prox;
	// o novo começo não tem anterior
	if (*this != NULL)
		(*this)->ante = NULL;
	// retorna a string do nó removido
	return str_removida;
}

/**
 * lista_remove
 * Remove uma string da listad
 *
 * this { ListaD ** } Endereço da listad, para poder alterar a ListaD caso o nó removido seja o primeiro
 * str { char * } String a ser removida
 *
 * return { char * } string do nó removido
**/
char *listad__remove(ListaD **this, char *str)
{
	// variável para iterar sobre a listad e chegar até a última posição
	ListaD *it = *this;
	// variável para saber qual o nó que esta antes do nó a ser removido
	ListaD *anterior = NULL;
	// variável para guardar o nó a ser removido
	ListaD *remover = NULL;
	// variável para retornaro a string removida
	char *str_removida = NULL;
	
	// iterar enquanto a listad não acabar
	while (it != NULL)
	{
		// caso o iterador tenha a string a ser removida, parar o loop
		if (strcmp(it->str, str) == 0)
			break;
		// o anterior recebe o iterador antes do iterador receber o proximo nó da ListaD
		anterior = it;
		it = it->prox;
	}
	
	// se o iterador for NULL, a string procurada não existe na listad
	if (it != NULL)
	{
		// definindo o nó a ser removido
		remover = it;
		// definindo a string a ser retornada
		str_removida = remover->str;
		// caso a palavra a ser removida seja do primeiro nó da ListaD
		if (anterior == NULL)
		{
			// para remover o primeiro item, apenas definimos o segundo item como o novo primeiro
			*this = (*this)->prox;
			// o novo começo não tem anterior
			if(*this != NULL)
				(*this)->ante = NULL;
		} else
		{
			// o nó anterior ao removido aponta para o nó apos o removido
			anterior->prox = it->prox;
			// o anterior desse aponta para seu novo anterior
			if (it->prox != NULL)
				it->prox->ante = anterior->prox;
		}
	}
	
	// liberamos o nó removido da memória
	free(remover);
	
	// retornamos a string encontrada
	return str_removida;
}

/**
 * lista_remove_at
 * Remove um nó em uma dada posição da listad
 *
 * this { ListaD ** } Endereço da listad, para poder alterar a ListaD caso o nó removido seja o primeiro
 * posicao { char * } Posição do nó a ser removido
 *
 * return { char * } string do nó removido
**/
char *listad__remove_at(ListaD **this, int posicao)
{
	// variável para iterar sobre a listad e chegar até a última posição
	ListaD *it = *this;
	// variável para saber qual o nó que esta antes do nó a ser removido
	ListaD *anterior = NULL;
	// variável para guardar o nó a ser removido
	ListaD *remover = NULL;
	// variável para retornaro a string removida
	char *str_removida = NULL;
	// contador
	int i = 0;
	
	// caso listad já esteja vazia
	if(*this == NULL)
		return NULL;
	
	// iterar enquanto a listad não acabar
	while (it->prox != NULL && i < posicao)
	{
		// o anterior recebe o iterador antes do iterador receber o proximo nó da ListaD
		anterior = it;
		it = it->prox;
	}
	
	// definindo o nó a ser removido
	remover = it;
	// definindo a string a ser retornada
	str_removida = remover->str;
	// caso a palavra a ser removida seja do primeiro nó da ListaD
	if (anterior == NULL)
	{
		// para remover o primeiro item, apenas definimos o segundo item como o novo primeiro
		*this = (*this)->prox;
		// o novo começo não tem anterior
		if(*this != NULL)
			(*this)->ante = NULL;
	} else
	{
		// o nó anterior ao removido aponta para o nó apos o removido
		anterior->prox = it->prox;
		// o anterior desse aponta para seu novo anterior
		if (it->prox != NULL)
			it->prox->ante = anterior->prox;
	}
	
	// liberamos o nó removido da memória
	free(remover);
	
	// retornamos a string encontrada
	return str_removida;
}

/**
 * listad__clear
 * Esvazia uma Lista Duplamente Encadeda
 *
 * this { ListaD ** } Endereço da ListaD a ser esvaziada, no final se tornara NULL
**/
void listad__clear(ListaD **this)
{
	// enquanto a ListaD não estiver vazia, removemos o primeiro elemento
	while(*this != NULL)
		listad__unshift(this);
}

/**
 * listad__print
 * Mostra todos nós da ListaD
 *
 * this { ListaD * } ListaD a ser mostrada
**/
void listad__print(ListaD *this)
{
	// iterador para percorrer a ListaD
	ListaD *it = this;
	
	// enquanto a ListaD não acabar
	while (it != NULL)
	{
		printf("'%s', ", it->str);
		it = it->prox;
	}
	
	printf("\n");
}

/**
 * listad__rprint
 * Mostra todos nós da ListaD de trás para frente
 *
 * this { ListaD * } ListaD a ser mostrada
**/
void listad__rprint(ListaD *this)
{
	// iterador para percorrer a ListaD
	ListaD *it = this;
	
	if (it != NULL)
	{
		// chegando até o último nó
		while (it->prox != NULL)
			it = it->prox;
		
		// mostrando
		while (it != NULL)
		{
			printf("'%s', ", it->str);
			it = it->ante;
		}
	}

	printf("\n");
}

/**
 * listad__join
 * Imprime a ListaD, separando os nós com um separador
 *
 * this { ListaD * } ListaD a ser mostrada
 * separador { char * } Separador entre os nós da ListaD
**/
void listad__join(ListaD *this, char *separador)
{
	// iterador para percorrer a listad
	ListaD *it = this;
	
	// enquanto a ListaD não acabar
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
 * listad__length
 * Informa a quantidade de nós na ListaD
 *
 * this { ListaD * } ListaD a ter os nós contados
 *
 * returns { int } Quantidade de nós da ListaD
**/
int listad__length(ListaD *this)
{
	// iterador para percorrer a ListaD
	ListaD *it = this;
	// contador de nós da ListaD
	int tamanho = 0;
	
	// percorrer a ListaD e incrementar o tamanho para cada nó
	while (it != NULL)
	{
		tamanho++;
		it = it->prox;
	}
	
	// retornar a quantidade de nós
	return tamanho;
}

/**
 * listad__get
 * Retorna a string em determinada posição da ListaD
 *
 * this { ListaD * } ListaD a ter a string procurada
 * posicao { int } Posição a ser procurada na ListaD
**/
char *listad__get(ListaD *this, int posicao)
{
	// iterador para percorrer a ListaD
	ListaD *it = this;
	// contador para saber a posição
	int i = 0;
	// string a ser retornada
	char *str_encontrada = NULL;
	
	// percorrer ListaD até acabar ou chegar na posição definida
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
 * listad__sort
 * Ordena os elementos de uma Lista Duplamente Encadeda
 *
 * this { ListaD * } ListaD a ser ordenada
**/
void listad__sort(ListaD *this)
{
	// iteradores e auxiliar
	ListaD *it_i;
	ListaD *it_j;
	char *aux;
	
	// percorrendo listad ate o final
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
	ListaD *l = listad__new("Hello", NULL, NULL);
	listad__print(l);
	
	l = listad__push(l, "World");
	l = listad__insert(&l, "my dear", 1);
	
	listad__print(l);
	listad__rprint(l);
	
	listad__pop(&l);
	listad__unshift(&l);
	listad__remove(&l, "my dear");
	
	listad__print(l);
	listad__rprint(l);
	
	l = listad__shift(&l, "Wow");
	l = listad__push(l, "worked");
	l = listad__insert(&l, "this", 1);

	listad__join(l, "_");
	
	printf("A listad possui %d elementos.\n", listad__length(l));
	
	listad__clear(&l);

	printf("A listad possui %d elementos.\n", listad__length(l));
	
	l = listad__insert(&l, "teste0", 123);
	listad__print(l);
	listad__remove_at(&l, 54321);
	listad__print(l);
	
	l = listad__push(l, "teste1");
	listad__print(l);
	listad__pop(&l);
	listad__print(l);
	
	l = listad__shift(&l, "teste2");
	listad__print(l);
	listad__unshift(&l);
	listad__print(l);
	
	listad__clear(&l);
	l = listad__push(l, "b");
	l = listad__push(l, "c");
	l = listad__push(l, "e");
	l = listad__push(l, "d");
	l = listad__push(l, "f");
	l = listad__push(l, "a");
	l = listad__push(l, "g");
	
	listad__sort(l);
	listad__print(l);
	
	listad__clear(&l);
	
	l = listad__insert(&l, "agora", 0);
	l = listad__shift(&l, "ok,");
	l = listad__push(l, "acabou");
	
	for (int i = 0; i < listad__length(l); i++)
		printf("%s ", listad__get(l, i));
	
	return 0;
}