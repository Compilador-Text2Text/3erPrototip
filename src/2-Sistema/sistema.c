#include "sistema.h"

#include "../1-Executor/instruccions.h"

int private_sistema_retorn (size_t n, union valor *v, struct pila *p)
{
	struct funcio_dinamica *f;

	f = pila_treure (p);

	// Que retorna. (Per defecte res)
	if (n) f->retorn->valor = *v;

	// Alliberem les variables.
	if (f->memoria.mida)	f->memoria.punter	= basic_free (f->memoria.punter);
	if (f->arguments.mida)	f->arguments.punter	= basic_free (f->arguments.punter);
	if (f->locals.mida)	f->locals.punter	= basic_free (f->locals.punter);
	f->memoria.mida = f->arguments.mida = f->locals.mida = 0;

	// Finalitzar. (Allibero aquí per si se vol fer múltiples fills (threads))
	if (p->us) return 1;
	pila_alliberar (p);
	return 0;
}
/**
 * return;		→ no escriu cap resultat.
 * return (valor);	→ escriu el resultat del valor.
 * Allibera la memòria de la funció.
 * En cas d'acabar la pila de funcions dinàmiques, també ho allibera per si vols treballar amb threads.
 **/
int
sistema_retorn (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	return private_sistema_retorn (n, &e->valor, p);
}

int
sistema_exit (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	union valor v;

	v = e->valor;

	while (private_sistema_retorn (n, &v, p));
	return 0;
}

int
sistema_obtenir_punter_de_punter (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.punter = *(void **)e[0].valor.punter;
	e[0].descriptor.vegades_punter--;
	return 1;
}

int
sistema_atoi (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter = atoi (e[0].valor.punter);
	e[0].descriptor = (struct descriptor){.tipus = Tipus_int, .vegades_punter = 0};
	return 1;
}
