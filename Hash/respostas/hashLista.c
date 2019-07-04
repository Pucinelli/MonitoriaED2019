#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.c"

/**
 *	Macro HASH_SIZE
 *	Tamanho máximo de um hash.
**/
#define HASH_SIZE 1024L

/**
 *	Tipo Hash
 *	Array de ponteiros de Contato do tamanho de HASH_SIZE.
 *	Ex 1.
**/
typedef Lista *Hash[HASH_SIZE];

/**
 *	"Construtor" de Contato
**/
Contato *contato_new(const char *nome, unsigned long numero)
{
	Contato *self = (Contato *)malloc(sizeof(Contato));
	strncpy(self->nome, nome, 64 - 1); /* Garante que o buffer de nome não vai receber mais que 64 bytes */
	self->numero = numero;
	return self;
}

/**
 *	Gerador de hash para um número de um Contato
 *	Ex 2.
**/
unsigned long hash(unsigned long numero)
{
	return numero % HASH_SIZE;
}

/**
 *	Gerador de segunda função de hash para um número de um Contato
 *	Parte do Ex 4.
**/
unsigned long hash2(unsigned long numero)
{
	return numero - HASH_SIZE - 2 % (HASH_SIZE - 2);
}

/**
 *	"Construtor" de Hash
**/
Hash *hash_new()
{
	Hash *self = (Hash *)malloc(sizeof(Hash));
	unsigned long i;
	for (i = 0; i < HASH_SIZE; i++) /* Assegura que todas posições do Hash estão vazias */
		(*self)[i] = NULL;
	return self;
}

/**
 *	Insere um contato na tabela Hash
 *	Em caso de colisão, insere na primeira posição livre.
**/
void hash_put(Hash *self, Contato *contato)
{
	unsigned long pos = hash(contato->numero);
	if ((*self)[pos] == NULL)
		(*self)[pos] = lista__new(contato, NULL);
	else
		(*self)[pos] = lista__push((*self)[pos], contato);
}

/**
 *	Retorna um contato buscando pelo número.
 *	Caso haja um contato na posição encontrada, procura linearmente até achar o número correto.
**/
Contato *hash_get(Hash *self, unsigned long numero)
{
	unsigned long pos = hash(numero);
	return lista__get((*self)[pos], numero);
}

/**
 *	Remove um contato da tabela hash.
 *	Caso haja um contato na posição encontrada, procura linearmente até achar o número correto.
**/
Contato *hash_remove(Hash *self, unsigned long numero)
{
	unsigned long pos = hash(numero);
	return lista__remove(&(*self)[pos], numero);
}

/**
 *	Imprime todos contatos da tabela hash e depois informa quantos existem.
**/
unsigned long hash_print(Hash *self)
{
	unsigned long i;
	unsigned long possui = 0;
	for (i = 0; i < HASH_SIZE; i++)
	{
		if ((*self)[i] != NULL)
		{
			printf("Hash[%lu]{ \n  ", i);
			lista__print((*self)[i]);
			printf("}\n");
			possui += lista__length((*self)[i]);
		}
	}
	printf("O hash contem %lu contatos\n", possui);
	return possui;
}

/**
 *	Não é recomendado criar um hash que utiliza ambas funções 
 *	de próxima posição livre e de hash secundário.
**/

int main()
{
	Hash *h = hash_new();
	
	hash_put(h, contato_new("Fulano", 1234));
	hash_put(h, contato_new("Ciclano", 1234 + HASH_SIZE));
	hash_put(h, contato_new("Beltrano", 1234 + (HASH_SIZE * 2)));
	hash_put(h, contato_new("Fulaninho", 123));
	hash_put(h, contato_new("Ciclaninho", 12345));
	hash_put(h, contato_new("Beltraninho", 54321));
	hash_print(h);
	hash_remove(h, 1234 + HASH_SIZE);
	hash_print(h);
	printf("Encontrado: %s\n\n", hash_get(h, 1234)->nome);

	return 0;
}