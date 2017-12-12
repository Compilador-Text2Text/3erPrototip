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
alliberar_frases (struct frase *f)
{
	struct paraula *p;

	// Si hem reservat memòria al codi <cadena de caràcters per exemple>
	// cal alliberar-ho.
	for (p = f->punter; p < f->punter +f->mida; p++)
		if ((p->lloc.on == Localitzacio_codi) && p->descriptor.vegades_punter)
			p->auxiliar.punter = basic_free (p->auxiliar.punter);

	f->punter = basic_free (f->punter);
	f->mida = 0;
}

void
alliberar_codi (struct codi *c)
{
	struct frase *f;

	for (f = c->punter; f < c->punter +c->mida; f++)
		alliberar_frases (f);

	c->punter = basic_free (c->punter);
	c->mida = 0;
}

void
alliberar_funcio (struct descriptor_funcio *f)
{
	f->funcio.nom = basic_free (f->funcio.nom);
	alliberar_variables (&f->funcio.arguments);
	alliberar_variables (&f->locals);
	alliberar_codi (&f->codi);
}

void
alliberar_funcions (void)
{
	struct descriptor_funcio *f;

	for (f = funcions.punter; f < funcions.punter +funcions.mida; f++)
		alliberar_funcio (f);

	funcions.mida = 0;
	funcions.punter = basic_free (funcions.punter);
}

void
alliberar_descriptors_funcio_globals (void)
{
	alliberar_variables (&variables_globals);
	alliberar_funcions ();
}
