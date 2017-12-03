#ifndef UTILS_PILA_H_
#define UTILS_PILA_H_

#include <stdlib.h>

struct
pila
{
	size_t us;
	size_t mida;
	size_t byts;
	void * punter;
};

struct pila pila_inicialitzar (size_t capacitat_inicial, size_t byts_per_element);
void pila_alliberar (struct pila *);

void  pila_afegir (struct pila *, void *);
void* pila_mostra (struct pila *);
void* pila_treure (struct pila *);

#endif // UTILS_PILA_H_
