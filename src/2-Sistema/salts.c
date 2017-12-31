#include "salts.h"

int
sistema_goto (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	struct funcio_dinamica *f;

	f = pila_mostra (p);
	f->cp = 0;
	f->cf = e[0].valor.enter;
	return 1;
}

int
sistema_gotoZ (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	if (e[1].valor.enter == 0)
		sistema_goto (n, e, p, b);
	return 1;
}

int
sistema_gotoNZ (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	if (e[1].valor.enter != 0)
		sistema_goto (n, e, p, b);
	return 1;
}
