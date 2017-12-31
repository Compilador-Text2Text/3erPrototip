#include <stdio.h>

#include "mostra.h"

int
sistema_mostra_cadena_caracters (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	printf ("%s", (char *)e[0].valor.punter);
	return 1;
}
