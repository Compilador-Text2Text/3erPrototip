#include "sistema.h"
#include "inicialitza.h"

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
sistema_sizeof (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	if (e[0].descriptor.vegades_punter)
		e[0].valor.enter = sizeof (void *);
	else
		switch (e[0].descriptor.tipus)
		{
		case Tipus_char:
			e[0].valor.enter = sizeof (char);
			break;
		case Tipus_int:
			e[0].valor.enter = sizeof (int);
			break;
		case Tipus_float:
			e[0].valor.enter = sizeof (float);
			break;
		case Tipus_void:
		case Tipus_END:
			basic_error ("Tipus entrat al sizeof invàlid. El void(0e) no és vàlid");
		}
	return 1;
}

int
sistema_malloc (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.punter = malloc (e[0].valor.enter);
	return 1;
}

int
sistema_free (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	free (e[0].valor.punter);
	return 1;
}

int
sistema_obtenir_punter_de_punter (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.punter = *(void **)e[0].valor.punter;
	e[0].descriptor.vegades_punter--;
	e[0].punter = e[0].valor.punter;
	return 1;
}

int
sistema_obtenir_caracter_de_punter (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.caracter = *(char *)e[0].valor.punter;
	e[0].descriptor.vegades_punter = 0;
	e[0].descriptor.tipus = Tipus_char;
	e[0].punter = e[0].valor.punter;
	return 1;
}

// Perquè el valgrind es queixava al fer anar el obtenir caracter de punter `e[0].valor.caracter = *(char *)e[0].valor.punter;`
// Ja que aquest element no està inicialitzat.
int
sistema_obtenir_punter (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].punter = e[0].valor.punter;
	e[0].valor.caracter = ((char*)e[0].punter)[0];
	return 1;
}

int
sistema_atoi (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter = atoi (e[0].valor.punter);
	e[0].descriptor = (struct descriptor){.tipus = Tipus_int, .vegades_punter = 0};
	return 1;
}

int
sistema_canvi_int_char (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.caracter = e[0].valor.enter;
	return 1;
}

int
sistema_canvi_char_int (size_t n, struct element_execucio *e, struct pila *p, struct base_funcio *b)
{
	e[0].valor.enter = e[0].valor.caracter;
	return 1;
}

void
sistema_sistema_inicialitza_sistema (void)
{
	sistema_definir_funcio (Sistema_return, "return", sistema_retorn,
		sistema_definir_arguments (1,
			"retorn",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0}, CF_cert, (union valor){.enter = 0}
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_exit, "exit", sistema_exit,
		sistema_definir_arguments (1,
			"sortir",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_cert, (union valor){.enter = 0}
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_sizeof, "sizeof", sistema_sizeof,
		sistema_definir_arguments (1,
			"mida",		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_malloc, "malloc", sistema_malloc,
		sistema_definir_arguments (1,
			"reservar",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 1},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_free, "free", sistema_free,
		sistema_definir_arguments (1,
			"alliberar",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 1}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_obtenir_punter, "*p=", sistema_obtenir_punter,
		sistema_definir_arguments (1,
			"punter(2)",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 1}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_obtenir_punter_de_punter, "*pp", sistema_obtenir_punter_de_punter,
		sistema_definir_arguments (1,
			"punter(2)",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 2}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 1},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_obtenir_caracter_de_punter, "*caràcter", sistema_obtenir_caracter_de_punter,
		sistema_definir_arguments (1,
			"caràcter(1)",	(struct descriptor){.tipus = Tipus_char, .vegades_punter = 1}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_char, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_atoi, "atoi", sistema_atoi,
		sistema_definir_arguments (1,
			"convertir",	(struct descriptor){.tipus = Tipus_char, .vegades_punter = 1}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_canvi_int_char, "int2char", sistema_canvi_int_char,
		sistema_definir_arguments (1,
			"convertir",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_char, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_canvi_char_int, "char2int", sistema_canvi_char_int,
		sistema_definir_arguments (1,
			"convertir",	(struct descriptor){.tipus = Tipus_char, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);
}
