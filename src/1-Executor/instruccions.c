#include <stdio.h>

#include "instruccions.h"

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

	f = pila_mostra (pf);
	p = instruccions_toquen_i_increment (f);
	e = instruccions_obtencio_element_execucio (f);

	switch (p.lloc.on)
	{
	case Localitzacio_codi:
		instruccions_codi_a_element_execucio (e, p);
		return 1;

	case Localitzacio_arguments:
		instruccions_variable_a_element_execucio (e, f->arguments.punter + p.lloc.relatiu);
		return 1;

	case Localitzacio_locals:
		instruccions_variable_a_element_execucio (e, f->locals.punter + p.lloc.relatiu);
		return 1;

	case Localitzacio_globals:
		instruccions_variable_a_element_execucio (e, variables_globals.punter + p.lloc.relatiu);
		return 1;
	}
	return 0;
}
