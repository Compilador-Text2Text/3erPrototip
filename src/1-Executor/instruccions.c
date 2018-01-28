#include <stdio.h>
#include <string.h>

#include "instruccions.h"

#include "../6-Depurador/depurador.h"

/**
 * Són totes les funcions necessàries
 * per a poder executar totes les instruccions.
 *
 * És molt important saber que conté:
 * - l'estructura paraula i
 * - l'estructura element d'execució
 * i com estan aquests relacionats,
 * sinó entendre aquest apartat pot ser complex.
 */

enum cert_fals verbos_execucio; // Per saber si continuem sent verbosos.

void
instruccio_inicialitzada (enum cert_fals ve)
{
	verbos_execucio = ve;
if (verbos_execucio) printf ("E: Comença l'execució.\n");
}

void
instruccions_codi_a_element_execucio (struct element_execucio *e, struct paraula p)
{
	e->descriptor	= p.descriptor;
	e->valor	= p.auxiliar;
	e->punter	= NULL;
}

void
instruccions_variable_a_element_execucio (struct element_execucio *e, struct variable *v)
{
	e->descriptor	= v->descriptor;
	e->valor	= v->valor;
	e->punter	= v;
}

void
instruccions_element_execucio_a_variable (struct variable *v, struct element_execucio *e)
{ // El descriptor normalment s'ha comprovat a la semàntica.
	v->valor = e->valor;
}

void
instruccions_crear_nova_funcio_dinamica
(
 size_t n,			// Nombre d'arguments.
 struct element_execucio *e,	// On fa el retorn.
 size_t r,			// Funció relativa.
 struct pila *p			// On guardem el resultat.
)
{
	struct funcio_dinamica f = {.cf = 0, .cp = 0};
	struct descriptor_funcio *d;
	int i;

	// Execució.
	d = funcions.punter +r;
	f.descriptor = d;
	f.memoria.mida = d->mida_memoria_execucio;
	f.memoria.punter = basic_malloc (f.memoria.mida * sizeof(struct element_execucio));

	// Retorn.
	f.retorn = e;

	// Arguments.
	f.arguments = d->funcio.arguments;
	f.arguments.punter = basic_malloc (f.arguments.mida * sizeof(struct variable));
	memcpy (f.arguments.punter, d->funcio.arguments.punter, f.arguments.mida * sizeof (struct variable));
	for (i = 0; i < n; i++)
		instruccions_element_execucio_a_variable (f.arguments.punter +i, e +i);

	// Variables locals.
	f.locals = d->locals;
	f.locals.punter = basic_malloc (f.locals.mida * sizeof(struct variable));
	memcpy (f.locals.punter, d->locals.punter, f.locals.mida * sizeof(struct variable));

	// Guardem el resultat.
	pila_afegir (p, &f);
}

int
instruccions_crida_funcio_sistema (size_t r, size_t n, struct element_execucio *e, struct pila *p)
{
	return sistemes.punter[r].exec (n, e, p, &sistemes.punter[r].funcio);
}

// Funció que retorna el toquen que apunta la funció dinàmica
// i incrementa el punter a la següent posició.
struct paraula
instruccions_toquen_i_increment (struct funcio_dinamica *f)
{
	struct paraula p;

	if (f->descriptor->codi.mida == f->cf)
	{ // Forcem un error, ja que no hi ha més frases.
		p.lloc.on = Localitzacio_END;
		return p;
	}

	// Obtenim el toquen.
	p = f->descriptor->codi.punter[f->cf].punter[f->cp];

	// Alliberem la memòria d'execució.
	if (!f->cp) f->memoria.us = 0;

	// Incrementem.
	if (++f->cp == f->descriptor->codi.punter[f->cf].mida)
	{
		f->cp = 0;
		f->cf++;
	}

	return p;
}

struct element_execucio *
instruccions_obtencio_element_execucio (struct funcio_dinamica *f)
{ // Normalment no cal fer comprovacions gràcies a la semàntica.
	return f->memoria.punter + f->memoria.us++;
}

int
instruccio_execucio_paraula (struct pila *pf)
{
	struct funcio_dinamica *f;
	struct paraula p;
	struct element_execucio *e;
	int aux, i;

	f = pila_mostra (pf);
aux = f->cf;
if (verbos_execucio)
{
for (aux = 1; aux < pf->us; aux++)
	printf (" ");
printf ("E: lloc:%s:%ld:%ld:<%ld> ", f->descriptor->funcio.nom, f->cf, f->cp, f->memoria.us);
}
	p = instruccions_toquen_i_increment (f);
if (verbos_execucio) {mostra_paraula_simple (&p, f->descriptor); printf ("\n");}
	e = instruccions_obtencio_element_execucio (f);

	switch ((i = p.lloc.on))
	{
	case Localitzacio_codi:
		instruccions_codi_a_element_execucio (e, p);
		break;

	case Localitzacio_arguments:
		instruccions_variable_a_element_execucio (e, f->arguments.punter + p.lloc.relatiu);
		break;

	case Localitzacio_locals:
		instruccions_variable_a_element_execucio (e, f->locals.punter + p.lloc.relatiu);
		break;

	case Localitzacio_globals:
		instruccions_variable_a_element_execucio (e, variables_globals.punter + p.lloc.relatiu);
		break;

	case Localitzacio_funcions:
		aux = p.auxiliar.enter;
		f->memoria.us -= aux;
		e -= aux;
		instruccions_crear_nova_funcio_dinamica (aux, e, p.lloc.relatiu, pf);
		break;

	case Localitzacio_sistema:
		aux = p.auxiliar.enter;
		f->memoria.us -= aux;
		e -= aux;
		return instruccions_crida_funcio_sistema (p.lloc.relatiu, aux, e, pf);

	default:
		basic_error ("Execució: instrucció desconeguda, ha de ser menor que %d i ha entrat %d", Localitzacio_preexecucio, i);
	}

	return 1;
}
