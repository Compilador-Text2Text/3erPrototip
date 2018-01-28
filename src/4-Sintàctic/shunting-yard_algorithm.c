#include <stdio.h>

#include "shunting-yard_algorithm.h"

#include "../1-Executor/descriptor.h"
#include "../6-Depurador/depurador.h"

/**
 * Codi estructurat que treballa amb:
 * - Funcions
 *   - Codi
 *     - Frases
 *       - Paraula (ordenar)
 *
 * Ordena i estructura els elements per tal
 * que a l'hora d'executar el codi sigui més fàcil,
 * eliminant per exemple comes i parèntesis.
 * La sortida és amb notació polonesa inversa.
 */

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
shunting_yard_algorithm_base (struct paraula *p)
{
	switch (p->lloc.on)
	{
	case Localitzacio_funcions: return &funcions.punter[p->lloc.relatiu].funcio; break;
	case Localitzacio_sistema:  return &sistemes.punter[p->lloc.relatiu].funcio; break;
	default: return NULL;
	}
}

struct base_funcio *
shunting_yard_algorithm_base_funcio_si_es_operant (struct paraula *p)
{
	struct base_funcio *b = shunting_yard_algorithm_base (p);
	if (b) if (b->SYA == SYA_funcio) return NULL;
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
		basic_error ("Funcio o operant SYA, esperat un valor menor que: %d, entrat: %d", SYA_END, e);
	}
	p->auxiliar.enter = 2; // Un operador té 2 elements d'entrada.

	while (a->us)
	{
		if (!(o2 = shunting_yard_algorithm_base_funcio_si_es_operant (pila_mostra (a)))) break;
		if (b->precedencia + c> o2->precedencia) break;

		pila_afegir (o, pila_treure (a));
	}

	pila_afegir (a, p);
}

void
shunting_yard_algorithm_preexecucio (struct paraula *p, struct pila *o, struct pila *a)
{
	struct base_funcio *b;
	struct paraula *s;
	int i;

	switch ((i = (enum preexecucio)p->lloc.relatiu))
	{
	case Preexecucio_obert:
		arguments_parentesis = CF_cert;
		pila_afegir (a, p);
		break;

	case Preexecucio_coma:
		while (a->us)
		{
			s = pila_treure (a);

			if ((s->lloc.on == Localitzacio_preexecucio) && (s->lloc.relatiu == Preexecucio_obert))
			{
				s->auxiliar.enter++; a->us++;
				return;
			}
			else
				pila_afegir (o, s);

		}
		basic_error ("Esperavem un parètesis obert, llegit una coma");
		break;

	case Preexecucio_tancat:
		while (a->us)
		{
			s = pila_treure (a);

			if ((s->lloc.on == Localitzacio_preexecucio) && (s->lloc.relatiu == Preexecucio_obert))
			{ // Comprovem si l'anterior és una funció.
				i = s->auxiliar.enter;
				if (a->us)
				{
					s = pila_mostra (a);
					b = shunting_yard_algorithm_base (s);

					if (b)
						if (b->SYA == SYA_funcio)
						{
							s->auxiliar.enter = i;
							pila_afegir (o, pila_treure(a));
							return;
						}
				}

				if (i != 1)
					basic_error ("Esperavem un element entre parètesis ja que no és una funció, detectat: %d", i);

				return;
			} else
				pila_afegir (o, s);
		}
		basic_error ("Preexecució tancat SYA, esperat parèntesis obert");

	default:
		basic_error ("Preexecució SYA, esperat un valor menor que: %d, entrat: %d", Preexecucio_END, i);
	}
}

void
shunting_yard_algorithm_paraula (struct paraula *p, struct pila *o, struct pila *a, struct descriptor_funcio *d)
{
	int i;

	if (arguments_parentesis)
	{ // Cas especial dels parèntesis i arguments.
		arguments_parentesis = CF_fals;

		if (!((p->lloc.on == Localitzacio_preexecucio) && (p->lloc.relatiu == Preexecucio_tancat)))
			((struct paraula *) pila_mostra (a))->auxiliar.enter++;
	}

	switch ((i = p->lloc.on))
	{
	case Localitzacio_codi:
	case Localitzacio_arguments:
	case Localitzacio_locals:
	case Localitzacio_globals:
		pila_afegir (o, p);
		break;

	case Localitzacio_funcions:
		p->descriptor = funcions.punter[p->lloc.relatiu].funcio.retorn;
		shunting_yard_algorithm_funcio_o_operant (p, &funcions.punter[p->lloc.relatiu].funcio, o, a);
		break;

	case Localitzacio_sistema:
		shunting_yard_algorithm_funcio_o_operant (p, &sistemes.punter[p->lloc.relatiu].funcio, o, a);
		break;

	case Localitzacio_preexecucio:
		shunting_yard_algorithm_preexecucio (p, o, a);
		break;

	default:
		basic_error ("Paraula SYA, esperat un valor menor que: %d, entrat: %d", Localitzacio_END, i);
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
		shunting_yard_algorithm_paraula (p, &o, a, d);

	while (a->us)
	{
		p = pila_treure (a);
		if (p->lloc.on == Localitzacio_preexecucio)
			basic_error ("Per donar una frase executable, no podem deixar elements de preexecució: %s", string_preexecucio (p->lloc.relatiu));
		pila_afegir (&o, p);
	}

	e->punter = o.punter;
	e->mida = o.us;
if (verbos_sintactic) {printf("S: Frase2 %lde: ", e->mida); mostra_frase (e, d); printf ("\n");}
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

struct pila
shunting_yard_algorithm (int longitud_maxima_frase, enum cert_fals verbos)
{
	int i;
	struct pila f;

	verbos_sintactic = verbos;
if (verbos_sintactic) printf ("S: Shunting yard algorithm.\n");

	f = pila_inicialitzar (longitud_maxima_frase, sizeof(struct paraula));

	for (i = 0; i < funcions.mida; i++)
		shunting_yard_algorithm_codi (&funcions.punter[i], &f);

	f.us = 0; // Allibero l'espai.
	return f;
}
