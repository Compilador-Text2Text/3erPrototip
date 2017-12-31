#include "salts.h"
#include "inicialitza.h"

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

void
sistema_salts_inicialitza_sistema (void)
{
	sistema_definir_funcio (Sistema_goto, "goto", sistema_goto,
		sistema_definir_arguments (1,
			"línia salt",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_gotoZ, "gotoZ", sistema_gotoZ,
		sistema_definir_arguments (2,
			"línia salt",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"condició",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_gotoNZ, "gotoNZ", sistema_gotoNZ,
		sistema_definir_arguments (2,
			"línia salt",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"condició",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);
}
