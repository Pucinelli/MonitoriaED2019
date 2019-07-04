#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *	Macro HASH_SIZE
 *	Tamanho máximo de um hash.
**/
#define HASH_SIZE 1024L

/**
 *	Struct Contato
 *	Contém o nome e o número de um contato.
**/
typedef struct Contato
{
	char nome[64];
	unsigned long numero;
} Contato;

/**
 *	Tipo Hash
 *	Array de ponteiros de Contato do tamanho de HASH_SIZE.
 *	Ex 1.
**/
typedef Contato *Hash[HASH_SIZE];

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
 *	Ex 3.
**/
void hash_put(Hash *self, Contato *contato)
{
	unsigned long pos = hash(contato->numero);
	while((*self)[pos] != NULL)
		pos = (pos + 1) % HASH_SIZE;
	(*self)[pos] = contato;
}

/**
 *	Insere um contato na tabela Hash
 *	Em caso de colisão, usa uma segunda função de hash para achar uma posição livre.
 *	Ex 4.
**/
void hash_put2(Hash *self, Contato *contato)
{
	unsigned long pos = hash(contato->numero);
	unsigned long pulo = hash2(contato->numero);
	while((*self)[pos] != NULL)
		pos = (pos + pulo) % HASH_SIZE;
	(*self)[pos] = contato;
}

/**
 *	Retorna um contato buscando pelo número.
 *	Caso haja um contato na posição encontrada, procura linearmente até achar o número correto.
 *	Ex 6.
**/
Contato *hash_get(Hash *self, unsigned long numero)
{
	unsigned long pos = hash(numero);
	unsigned long i = 0;
	do
	{
		if ((*self)[pos] != NULL)
			if ((*self)[pos]->numero == numero)
				return (*self)[pos];
		pos = (pos + 1) % HASH_SIZE;
		i++;
	} while (i < HASH_SIZE);
	return NULL;
}

/**
 *	Retorna um contato buscando pelo número.
 *	Caso haja um contato na posição encontrada, usa uma segunda função de hash até achar o número correto.
 *	Ex 6.
**/
Contato *hash_get2(Hash *self, unsigned long numero)
{
	unsigned long pos = hash(numero);
	unsigned long pulo = hash2(numero);
	unsigned long i = 0;
	do
	{
		if ((*self)[pos] != NULL)
			if ((*self)[pos]->numero == numero)
				return (*self)[pos];
		pos = (pos + pulo) % HASH_SIZE;
		i++;
	} while (i < HASH_SIZE);
	return NULL;
}

/**
 *	Retorna a posição de um contato na tabela hash.
 *	Realiza a verificação apenas pelo número. (Se quiser fazer pelo nome só incluir strcmp na comparação)
 *	Caso haja um contato na posição encontrada, procura linearmente até achar um contato com número igual ao inserido.
**/
unsigned long hash_get_pos(Hash *self, Contato *contato)
{
	unsigned long pos = hash(contato->numero);
	while ((*self)[pos] != NULL)
	{
		if ((*self)[pos]->numero == contato->numero)
			return pos;
		pos = (pos + 1) % HASH_SIZE;
	}
	return HASH_SIZE;
}

/**
 *	Retorna a posição de um contato na tabela hash.
 *	Realiza a verificação apenas pelo número. (Se quiser fazer pelo nome só incluir strcmp na comparação)
 *	Caso haja um contato na posição encontrada, usa uma segunda função de hash para percorrer o hash até achar um contato com número igual ao inserido.
**/
unsigned long hash_get_pos2(Hash *self, Contato *contato)
{
	unsigned long pos = hash(contato->numero);
	unsigned long pulo = hash2(contato->numero);
	while ((*self)[pos] != NULL)
	{
		if ((*self)[pos]->numero == contato->numero)
			return pos;
		pos = (pos + pulo) % HASH_SIZE;
	}
	return HASH_SIZE;
}

/**
 *	Remove um contato da tabela hash.
 *	Caso haja um contato na posição encontrada, procura linearmente até achar o número correto.
 *	Ex 5.
**/
Contato *hash_remove(Hash *self, unsigned long numero)
{
	unsigned long pos = hash(numero);
	Contato *removido = NULL;
	while ((*self)[pos] != NULL)
	{
		if ((*self)[pos]->numero == numero)
		{
			removido = (*self)[pos];
			(*self)[pos] = NULL;
			return removido;
		}
		pos = (pos + 1) % HASH_SIZE;
		if (pos == hash(numero))
			break;
	}
	return NULL;
}

/**
 *	Remove um contato da tabela hash.
 *	Caso haja um contato na posição encontrada, usa uma segunda função de hash até achar o número correto.
 *	Ex 5.
**/
Contato *hash_remove2(Hash *self, unsigned long numero)
{
	unsigned long pos = hash(numero);
	unsigned long pulo = hash2(numero);
	Contato *removido = NULL;
	while ((*self)[pos] != NULL)
	{
		if ((*self)[pos]->numero == numero)
		{
			removido = (*self)[pos];
			(*self)[pos] = NULL;
			return removido;
		}
		pos = (pos + pulo) % HASH_SIZE;
		if (pos == hash(numero))
			break;
	}
	return NULL;
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
			printf("Hash[%lu]{ nome: %s, numero: %lu }\n", i, (*self)[i]->nome, (*self)[i]->numero);
			possui++;
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
	Hash *prox_livre = hash_new();
	Hash *hash_sec = hash_new();

	
	hash_put(prox_livre, contato_new("Fulano", 1234));
	hash_put(prox_livre, contato_new("Ciclano", 1234 + HASH_SIZE));
	hash_put(prox_livre, contato_new("Beltrano", 1234 + (HASH_SIZE * 2)));
	hash_print(prox_livre);
	hash_remove(prox_livre, 1234 + HASH_SIZE);
	hash_print(prox_livre);
	printf("Encontrado: %s\n\n", hash_get(prox_livre, 1234)->nome);

	hash_put2(hash_sec, contato_new("Fulano", 1234));
	hash_put2(hash_sec, contato_new("Ciclano", 1234 + HASH_SIZE));
	hash_put2(hash_sec, contato_new("Beltrano", 1234 + (HASH_SIZE * 2)));
	hash_print(hash_sec);
	hash_remove2(hash_sec, 1234 + HASH_SIZE);
	hash_print(hash_sec);
	printf("Encontrado: %s\n", hash_get2(hash_sec, 1234)->nome);
	return 0;
}