#include "operadors.h"

int
sistema_igual (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	*((union valor*)e[0].punter) = e[1].valor;
	return 1;
}

int
sistema_suma (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter += e[1].valor.enter;
	return 1;
}

int
sistema_resta (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter -= e[1].valor.enter;
	return 1;
}

int
sistema_producte (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter *= e[1].valor.enter;
	return 1;
}

int
sistema_divisio (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter /= e[1].valor.enter;
	return 1;
}

int
sistema_potencia (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	return 1;
}

int
sistema_mes_petit_que (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter = e[0].valor.enter < e[1].valor.enter;
	return 1;
}

int
sistema_modul (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter %= e[1].valor.enter;
	return 1;
}

int
sistema_primer_resta (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter--;
	((union valor *)e[0].punter)[0].enter--;
	return 1;
}
