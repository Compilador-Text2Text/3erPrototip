#include <stdio.h>

#include "mostra.h"
#include "inicialitza.h"

int
sistema_mostra_cadena_caracters (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	printf ("%s", (char *)e[0].valor.punter);
	return 1;
}

int
sistema_mostra_enter (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	printf ("%d", e[0].valor.enter);
	return 1;
}

void
sistema_mostra_inicialitza_sistema (void)
{
	sistema_definir_funcio (Sistema_mostra_cadena_caracters, "printChar1", sistema_mostra_cadena_caracters,
		sistema_definir_arguments (1,
			"i",	(struct descriptor){.tipus = Tipus_char, .vegades_punter = 1}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_mostra_enter, "printInt0", sistema_mostra_enter,
		sistema_definir_arguments (1,
			"i",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);
}
