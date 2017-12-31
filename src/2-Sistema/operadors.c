#include "operadors.h"
#include "inicialitza.h"

int
sistema_igual (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	((struct variable*)e[0].punter)->valor = e[1].valor;
	return 1;
}

int
sistema_suma (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter += e[1].valor.enter;
	return 1;
}

int
sistema_suma_punter_punters_amb_enter (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	void **pp;

	pp = e[0].valor.punter;
	pp += e[1].valor.enter;
	e[0].valor.punter = pp;

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
	((struct variable *)e[0].punter)->valor.enter--;
	return 1;
}

int
sistema_segon_resta (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	((struct variable *)e[0].punter)->valor.enter--;
	return 1;
}

void
sistema_operadors_inicialitza_sistema (void)
{
	sistema_definir_funcio (Sistema_igual, "=", sistema_igual,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_esquerra, 0, CF_cert);

	sistema_definir_funcio (Sistema_suma, "+", sistema_suma,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 2, CF_cert);

	sistema_definir_funcio (Sistema_resta, "-", sistema_resta,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 2, CF_cert);

	sistema_definir_funcio (Sistema_producte, "*", sistema_producte,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 3, CF_cert);

	sistema_definir_funcio (Sistema_divisio, "/", sistema_divisio,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 3, CF_cert);

	sistema_definir_funcio (Sistema_modul, "%", sistema_modul,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 3, CF_cert);

	sistema_definir_funcio (Sistema_potencia, "^", sistema_potencia,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_esquerra, 4, CF_cert);

	sistema_definir_funcio (Sistema_suma_punter_punters_amb_enter, "pp+e", sistema_suma_punter_punters_amb_enter,
		sistema_definir_arguments (2,
			"p",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 1}, CF_fals,
			"e",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 1},
		SYA_esquerra, 2, CF_cert);

	sistema_definir_funcio (Sistema_mes_petit_que, "<", sistema_mes_petit_que,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_primer_resta, "--v", sistema_primer_resta,
		sistema_definir_arguments (1,
			"v",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_segon_resta, "v--", sistema_segon_resta,
		sistema_definir_arguments (1,
			"v",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);
}
