#include <stdio.h>

#include "../1-Executor/descriptor.h"
#include "../9-Útils/pila.h"

enum cert_fals verbos_semantic; // Per saber si continuem sent verbosos.

void
semantica_codi (int i, struct pila *a)
{
	int m = 0; // Màxim.
	struct descriptor_funcio *d;
	struct codi *c;
	struct frase *p;

if (verbos_semantic) printf ("A: Funció: %s.\n", funcions.punter[i].funcio.nom);
	d = &funcions.punter[i];
	c = &d->codi;

	for (p = c->punter; p < c->punter +c->mida; p++)
	; // TODO

	d->mida_memoria_execucio = m;
}

void
semantica (struct pila f, enum cert_fals verbos)
{
	int i;

	verbos_semantic = verbos;
if (verbos_semantic) printf ("A: Inicialitza la semàntica.\n");
	for (i = 0; i < funcions.mida; i++)
		semantica_codi (i, &f);

	pila_alliberar (&f);
}
