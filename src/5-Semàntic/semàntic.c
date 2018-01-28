#include <stdio.h>

#include "../1-Executor/descriptor.h"
#include "../6-Depurador/depurador.h"
#include "../9-Útils/pila.h"

/**
 * Estructurat:
 * - Funcions, codi
 *   - Frases
 *     - Paraules
 *
 * Només vigila que els arguments coincideixin amb el tipus d'arguments desitjats.
 * Com a extra, no cal posar tots els arguments, ja que aquest és capaç d'entendre
 * quan un argument ja està inicialitzat o no.
 */

enum cert_fals verbos_semantic; // Per saber si continuem sent verbosos.

// Com a python, pots tenir variables inicialitzades.
// No he fet que puguis enviar més arguments dels que demanes.
void
semantica_funcions (struct pila *a, int mida, struct base_funcio *f, struct paraula *pf)
{
	int i;
	struct paraula *p;
	struct variables *vs;

	vs = &f->arguments;

	if (mida > a->us)
		basic_error ("Semàntic error, ja que hi ha una funció que demana %d arguments i n'hi ha %d", mida, a->us);

	// Tot això és perquè llegeix en línia, no del revés.
	for (i = 0; i < mida; i++)
		p = pila_treure (a);
	p--;
	for (i = 0; i < mida; i++)
	{
		if (i >= vs->mida)
			basic_error ("Semàntic: No està preparat per rebre més arguments dels que estan definits");
		p++;

		if ((vs->punter[i].descriptor.tipus == Tipus_void) || (p->descriptor.tipus == Tipus_void)) continue;
		if (!((p->descriptor.tipus == vs->punter[i].descriptor.tipus) && (p->descriptor.vegades_punter == vs->punter[i].descriptor.vegades_punter)))
		{
			printf ("Error:\nParaula: %s(%ld)\nArgument: %s(%ld)\n", string_tipu (p->descriptor.tipus), p->descriptor.vegades_punter, string_tipu (vs->punter[i].descriptor.tipus), vs->punter[i].descriptor.vegades_punter);
			basic_error ("Semàntic error, els tipus d'arguments i d'entrada no són compatibles.");
		}
	}

	for (i = mida; i < vs->mida; i++)
		if (!vs->punter[i].inicialitzat)
			basic_error ("Error semàntica. Falten arguments!\n");

	pila_afegir (a, pf);
}

void
semantica_paraula (struct paraula *p, struct pila *a, struct descriptor_funcio *d, int lloc)
{
	int i;
struct frase f = {.mida = a->us, .punter = a->punter};
if (verbos_semantic) {printf ("A:  Paraula: "); mostra_frase (&f, d); mostra_paraula (p, lloc);}

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
		semantica_funcions (a, p->auxiliar.enter, &funcions.punter[p->lloc.relatiu].funcio, p);
		break;

	case Localitzacio_sistema:
		if (p->lloc.relatiu >= sistemes.mida)
			basic_error ("Semàntic error, ja que hi ha %d funcions de sistema i s'està cridant el %d", sistemes.mida, p->lloc.relatiu);
		semantica_funcions (a, p->auxiliar.enter, &sistemes.punter[p->lloc.relatiu].funcio, p);
		break;

	default:
		basic_error ("Semàntic error, ha entrat un element imprevist");
	}
}

int
semantica_frase (struct frase *f, struct pila *a, struct descriptor_funcio *d, int lloc)
{
	int m = 0;
	struct paraula *p;
	a->us = 0; // Alliberem la memòria.

	for (p = f->punter; p < f->punter +f->mida; p++)
	{
		semantica_paraula (p, a, d, lloc);
		m = MAX (m, a->us);
	}
if (verbos_semantic) {printf("A: Frase màxim: %de: ", m); mostra_frase (f, d); printf ("\n");}

	return m;
}

void
semantica_codi (int i, struct pila *a)
{
	int m = 0, j; // Màxim.
	struct descriptor_funcio *d;
	struct codi *c;
	struct frase *p;

if (verbos_semantic) printf ("A: Funció: %s.\n", funcions.punter[i].funcio.nom);
	d = &funcions.punter[i];
	c = &d->codi;

	for (p = c->punter; p < c->punter +c->mida; p++)
	{
		j = semantica_frase (p, a, d, i);
		m = MAX (j, m);
	}

	d->mida_memoria_execucio = m;
if (verbos_semantic) printf ("A:%s: màxim: %d.\n", d->funcio.nom, m);
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
