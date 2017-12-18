#include <stdio.h>

#include "../1-Executor/descriptor.h"
#include "../6-Depurador/depurador.h"
#include "../9-Útils/pila.h"

enum cert_fals verbos_semantic; // Per saber si continuem sent verbosos.

void
semantica_funcions (struct pila *a, int mida, struct variables *vs)
{
	int i;

	for (i = 0; i < mida; i++)
	; // TODO i comprovar els que manquen!
}

void
semantica_paraula (struct paraula *p, struct pila *a, struct descriptor_funcio *d)
{
	int i;

	switch ((enum localitzacions)(i = p->lloc.on))
	{
	case Localitzacio_codi:
	case Localitzacio_arguments:
	case Localitzacio_locals:
	case Localitzacio_globals:
		pila_afegir (a, p);
		break;

	case Localitzacio_funcions:
		if (p->lloc.relatiu >= funcions.mida)
			basic_error ("Semàntic error, ja que hi ha %d funcions i s'està cridant el %d", funcions.mida, p->lloc.relatiu);
		semantica_funcions (a, p->auxiliar.enter, &funcions.punter[p->lloc.relatiu].funcio.arguments);
		break;
	}
}

int
semantica_frase (struct frase *f, struct pila *a, struct descriptor_funcio *d)
{
	int m = 0;
	struct paraula *p;

	for (p = f->punter; p < f->punter +f->mida; p++)
	{
		semantica_paraula (p, a, d);
		m = MAX (m, a->us);
	}
if (verbos_semantic) {printf("A: Frase màxim: %de: ", m); mostra_frase (f, d); printf ("\n");}

	return m;
}

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
	{
		i = semantica_frase (p, a, d);
		m = MAX (i, m);
	}

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
