#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contato
{
	char nome[64];
	unsigned long numero;
} Contato;

typedef struct Lista
{
	Contato *contatos;
	struct Lista *prox;
} Lista;

Lista *lista__new(Contato *contato, Lista *prox)
{
	Lista *self = malloc(sizeof(Lista));
	self->contatos = contato;
	self->prox = prox;
	return self;
}

Lista *lista__push(Lista *self, Contato *contato)
{
	Lista *it = self;
	if (self == NULL)
		return lista__new(contato, NULL);
	while (it->prox != NULL)
		it = it->prox;
	it->prox = lista__new(contato, NULL);
	return self;
}

Contato *lista__remove(Lista **self, unsigned long numero)
{
	Lista *it = *self;
	Lista *anterior = NULL;
	Lista *remover = NULL;
	Contato *contato_removido = NULL;
	while (it != NULL)
	{
		if (it->contatos->numero == numero)
			break;
		anterior = it;
		it = it->prox;
	}
	if (it != NULL)
	{
		remover = it;
		contato_removido = remover->contatos;
		if (anterior == NULL)
			*self = (*self)->prox;
		else
			anterior->prox = it->prox;
	}
	free(remover);
	return contato_removido;
}

void lista__print(Lista *self)
{
	Lista *it = self;
	while (it != NULL)
	{
		printf("{ nome: %s, numero: %lu }, ", it->contatos->nome, it->contatos->numero);
		it = it->prox;
	}	
	printf("\n");
}

int lista__length(Lista *self)
{
	Lista *it = self;
	int tamanho = 0;
	while (it != NULL)
	{
		tamanho++;
		it = it->prox;
	}
	return tamanho;
}

Contato *lista__get(Lista *self, unsigned long numero)
{
	Lista *it = self;
	while (it != NULL)
	{
		if (it->contatos->numero == numero)
			return it->contatos;
		it = it->prox;
	}
	return NULL;
}