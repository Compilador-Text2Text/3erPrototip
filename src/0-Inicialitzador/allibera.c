#include "../1-Executor/descriptor.h"
#include "../9-Útils/bàsic.h"

void
alliberar_variables (struct variables *vs)
{
	struct variable *v;

	for (v = vs->punter; v < vs->punter +vs->mida; v++)
	{
		v->nom = basic_free (v->nom);
		if (v->descriptor.vegades_punter && v->inicialitzat)
			v->valor.punter = basic_free (v->valor.punter);
	}

	vs->mida = 0;
	vs->punter = basic_free (vs->punter);
}

void
alliberar_descriptors_funcio_globals (void)
{
	alliberar_variables (&variables_globals);
}
