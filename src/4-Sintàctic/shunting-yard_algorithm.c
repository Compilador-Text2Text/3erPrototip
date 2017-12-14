#include <stdio.h>

#include "shunting-yard_algorithm.h"

#include "../1-Executor/descriptor.h"
#include "../6-Depurador/depurador.h"

enum cert_fals verbos_sintactic; // Per saber si continuem sent verbosos.
enum cert_fals arguments_parentesis;

void
shunting_yard_algorithm_mostra_pila (struct pila *p, struct descriptor_funcio *d)
{
	struct paraula *a;

	printf ("\t|");
	for (a = p->punter; a < (struct paraula*)p->punter + p->us; a++)
		mostra_paraula_simple (a, d);
}

void
shunting_yard_algorithm_mostra (struct paraula *p, struct pila *o, struct pila *a, struct descriptor_funcio *d)
{
	printf ("S: ");
	mostra_paraula_simple (p, d);

	shunting_yard_algorithm_mostra_pila (o, d);
	shunting_yard_algorithm_mostra_pila (a, d);

	printf ("\n");
}

struct base_funcio *
shunting_yard_algorithm_base_funcio_si_es_operant (struct paraula *p)
{
	struct base_funcio *b;

	switch (p->lloc.on)
	{
	case Localitzacio_funcions: b = &funcions.punter[p->lloc.relatiu].funcio; break;
	case Localitzacio_sistema:  b = &sistemes.punter[p->lloc.relatiu].funcio; break;
	default: return NULL;
	}

	if (b->SYA == SYA_funcio) return NULL;
	return b;
}

void
shunting_yard_algorithm_funcio_o_operant (struct paraula *p, struct base_funcio *b, struct pila *o, struct pila *a)
{
	int c;
	enum SYA e;
	struct base_funcio *o2;

	switch ((e = b->SYA))
	{
	case SYA_funcio: pila_afegir (a, p); return;
	case SYA_esquerra:	c = 1; break; // >
	case SYA_dreta:		c = 0; break; // ≥

	default:
		basic_error ("funcio o operant SYA, esperat un valor menor que: %d, entrat: %d", SYA_END, e);
	}

	while (a->us)
	{
		if (!(o2 = shunting_yard_algorithm_base_funcio_si_es_operant (pila_mostra (a)))) break;
		if (b->precedencia + c> o2->precedencia) break;

		pila_afegir (o, pila_treure (a));
	}

	pila_afegir (a, p);
}

void
shunting_yard_algorithm_paraule (struct paraula *p, struct pila *o, struct pila *a, struct descriptor_funcio *d)
{
	if (arguments_parentesis)
	{ // Cas especial dels parèntesis i arguments.
		arguments_parentesis = CF_fals;

		if ((p->lloc.on != Localitzacio_preexecucio) && (p->lloc.relatiu != Preexecucio_tancat))
			((struct paraula *) pila_mostra (o))->auxiliar.enter = 1;
	}

	switch (p->lloc.on)
	{
	case Localitzacio_codi:
	case Localitzacio_arguments:
	case Localitzacio_locals:
	case Localitzacio_globals:
		pila_afegir (o, p);
		break;

	case Localitzacio_funcions:
		shunting_yard_algorithm_funcio_o_operant (p, &funcions.punter[p->lloc.relatiu].funcio, o, a);
		break;

	case Localitzacio_sistema:
		shunting_yard_algorithm_funcio_o_operant (p, &sistemes.punter[p->lloc.relatiu].funcio, o, a);
		break;
	}
if (verbos_sintactic) shunting_yard_algorithm_mostra (p, o, a, d);
}

void
shunting_yard_algorithm_frase (struct frase *e, struct pila *a, struct descriptor_funcio *d)
{
	struct paraula *p;
	struct pila o;
if (verbos_sintactic) {printf("S: Frase %lde: ", e->mida); mostra_frase (e, d); printf ("\n");}

	o = *a;
	o.mida		= e->mida;
	o.punter	= e->punter;
	o.us		= 0;

	arguments_parentesis = CF_fals; // Diem que l'anterior no és un parèntesis.
	for (p = e->punter; p < e->punter + e->mida; p++)
		shunting_yard_algorithm_paraule (p, &o, a, d);

}

void
shunting_yard_algorithm_codi (struct descriptor_funcio *d, struct pila *a)
{
	struct frase *p;
	struct codi *c = &d->codi;
if (verbos_sintactic) printf ("S: Funció: %s.\n", d->funcio.nom);

	for (p = c->punter; p < c->punter +c->mida; p++)
		shunting_yard_algorithm_frase (p, a, d);
}

void
shunting_yard_algorithm (int longitud_maxima_frase, enum cert_fals verbos)
{
	int i;
	struct pila f;

	verbos_sintactic = verbos;
if (verbos_sintactic) printf ("S: Shunting yard algorithm.\n");

	f = pila_inicialitzar (longitud_maxima_frase, sizeof(struct paraula));

	for (i = 0; i < funcions.mida; i++)
		shunting_yard_algorithm_codi (&funcions.punter[i], &f);

	pila_alliberar (&f);
}
