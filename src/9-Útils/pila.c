#include <stdio.h>
#include <string.h>

#include "bàsic.h"
#include "pila.h"

/**
 * Funció pila per a qualsevol element,
 * llavors té molta importància indicar la mida d'aquests.
 * Tot i ser així, tots els elements han de ser igual de grans.
 * L'apartat d'incrementar la mida ha sigut gràcies al Guillermo Blasco
 * que em va fer descobrir que tenia accés al codi font de java (en concret ArrayList)
 */

/************************************************/
/*	Funcions privades			*/
/************************************************/
size_t
pila_total_byts (struct pila *p)
{
	return p->mida * p->byts;
}

// Pensat per afegir 1 element.
void
pila_incrementar_mida_pila_en_necessitat (struct pila *p)
{
	if ((p->us) < p->mida) return; // No cal fer res.

	// Extret de open source de ArrayList de Java.
	p->mida = (p->mida *3)/2 +1;

	p->punter = basic_realloc (p->punter, pila_total_byts (p));
}

void
pila_assegurar_memoria_minima (struct pila *p)
{
	if (!p->us) basic_error ("Vol treure un element de la pila quan aquesta està buida");
}

/************************************************/
/*	Inicialitzar i finalitzar la pila	*/
/************************************************/
struct pila
pila_inicialitzar (size_t mida, size_t byts)
{
	struct pila p;

	// Comprovació de poder emmagatzemar elements.
	if (!byts) basic_error ("Pila amb reserva de memòria buida");

	p.us		= 0;
	p.mida		= mida;
	p.byts		= byts;
	p.punter	= basic_malloc (pila_total_byts (&p));

	return p;
}

void
pila_alliberar (struct pila *p)
{
	// Evitant errors.
	if (p->mida) free (p->punter);

	// Actualitzant els valors.
	p->us		= 0;
	p->mida		= 0;
	p->punter	= NULL;
}

/************************************************/
/*	Funcions per una pila			*/
/************************************************/
void
pila_afegir (struct pila *p, void *q)
{
	// Incrementa la mida si és necessari.
	pila_incrementar_mida_pila_en_necessitat (p);

	// Guarda la informació.
	memcpy (p->punter + p->us++*p->byts, q, p->byts);
}

void *
pila_treure (struct pila *p)
{
	// Comprovem que tingui alguna cosa.
	pila_assegurar_memoria_minima (p);

	return p->punter+--p->us*p->byts;
}

void *
pila_mostra (struct pila *p)
{
	// Comprovem que tingui alguna cosa.
	pila_assegurar_memoria_minima (p);

	return p->punter + (p->us -1)*p->byts;
}
